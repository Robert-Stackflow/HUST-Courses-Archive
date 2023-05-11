//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/index/b_plus_tree.cpp
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <string>
#include <iostream>
#include "common/exception.h"
#include "common/rid.h"
#include "storage/index/b_plus_tree.h"
#include "storage/page/header_page.h"

namespace bustub {
INDEX_TEMPLATE_ARGUMENTS
BPLUSTREE_TYPE::BPlusTree(std::string name, BufferPoolManager *buffer_pool_manager, const KeyComparator &comparator,
                          int leaf_max_size, int internal_max_size)
    : index_name_(std::move(name)),
      root_page_id_(INVALID_PAGE_ID),
      buffer_pool_manager_(buffer_pool_manager),
      comparator_(comparator),
      leaf_max_size_(leaf_max_size),
      internal_max_size_(internal_max_size) {}

/*
 * Helper function to decide whether current b+tree is empty
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::IsEmpty() const {
  //之前的page类型均为结点，现在该类型表示整个B+树
  return root_page_id_ == INVALID_PAGE_ID;
}
/*****************************************************************************
 * SEARCH
 *****************************************************************************/
/*
 * Return the only value that associated with input key
 * This method is used for point query
 * @return : true means key exists
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::GetValue(const KeyType &key, std::vector<ValueType> *result, Transaction *transaction) {
  std::lock_guard<std::mutex> lock(latch_);
  Page *page = FindLeafPage(key);
  if (page == nullptr) return false;
  B_PLUS_TREE_LEAF_PAGE_TYPE *leafPage = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page->GetData());
  ValueType v;
  if (leafPage->Lookup(key, &v, comparator_)) {
    result->push_back(v);
    buffer_pool_manager_->UnpinPage(leafPage->GetPageId(), false);
    return true;
  }
  buffer_pool_manager_->UnpinPage(leafPage->GetPageId(), false);
  return false;
}

/*****************************************************************************
 * INSERTION
 *****************************************************************************/
/*
 * Insert constant key & value pair into b+ tree
 * if current tree is empty, start new tree, update root page id and insert
 * entry, otherwise insert into leaf page.
 * @return: since we only support unique key, if user try to insert duplicate
 * keys return false, otherwise return true.
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::Insert(const KeyType &key, const ValueType &value, Transaction *transaction) {
  // Page::WLatch();
  std::lock_guard<std::mutex> lock(latch_);
  if (IsEmpty()) {
    printf("new tree start\n");
    StartNewTree(key, value);
    // Page::WUnlatch();
    return true;
  }
  // Page::WUnlatch();
  bool res = InsertIntoLeaf(key, value, transaction);
  return res;
}
/*
 * Insert constant key & value pair into an empty tree
 * User needs to first ask for new page from buffer pool manager(NOTICE: throw
 * an "out of memory" exception if returned value is nullptr), then update b+
 * tree's root page id and insert entry directly into leaf page.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::StartNewTree(const KeyType &key, const ValueType &value) {
  page_id_t pageId;
  Page *rootPage = buffer_pool_manager_->NewPage(&pageId);
  assert(rootPage != nullptr);
  B_PLUS_TREE_LEAF_PAGE_TYPE *root = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(rootPage->GetData());

  root->Init(pageId, INVALID_PAGE_ID);
  printf("start %d \n", pageId);
  //更新当前B+树的根页ID
  root_page_id_ = pageId;
  UpdateRootPageId(pageId);
  root->Insert(key, value, comparator_);
  printf("new root size:%d\n", root->GetSize());
  buffer_pool_manager_->UnpinPage(pageId, true);
  return;
}

/*
 * Insert constant key & value pair into leaf page
 * User needs to first find the right leaf page as insertion target, then look
 * through leaf page to see whether insert key exist or not. If exist, return
 * immdiately, otherwise insert entry. Remember to deal with split if necessary.
 * @return: since we only support unique key, if user try to insert duplicate
 * keys return false, otherwise return true.
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::InsertIntoLeaf(const KeyType &key, const ValueType &value, Transaction *transaction) {
  Page *pPage = FindLeafPage(key);
  if (pPage == nullptr) {
    return false;
  }
  printf("FindLeafPage successfully:");
  B_PLUS_TREE_LEAF_PAGE_TYPE *page = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(pPage->GetData());
  printf("before insert size:%d\n", page->GetSize());
  ValueType v;
  if (page->Lookup(key, &v, comparator_)) {
    printf("insert key already existed \n");
    buffer_pool_manager_->UnpinPage(page->GetPageId(), false);
    return false;
  }
  printf("insert key:%ld to page:%d \n", key.ToString(), page->GetPageId());
  page->Insert(key, value, comparator_);
  printf("%s\n", this->ToString(true).c_str());
  this->ToString(true);
  int size = page->GetSize();
  //每次插入之后进行判断，是否已经超过最大值，选择直接进行分裂
  //由于MAXSIZE后还留有一个空白结点，这样可以保证插入结点而不会导致数据越界
  //这样就可以先插入，再分裂节点，避免了需要先分裂腾出空间，再插入其中一个的复杂操作
  if (size > page->GetMaxSize()) {
    printf("---------start to split,new page------------- \n");
    B_PLUS_TREE_LEAF_PAGE_TYPE *newLeafPage = Split(page);
    InsertIntoParent(page, newLeafPage->KeyAt(0), newLeafPage, transaction);
    printf("%s\n", this->ToString(true).c_str());
  }
  // InsertIntoParent函数内部会unpin新节点，故只需unpin旧结点即可
  buffer_pool_manager_->UnpinPage(page->GetPageId(), false);
  return true;
}

/*
 * Split input page and return newly created page.
 * Using template N to represent either internal page or leaf page.
 * User needs to first ask for new page from buffer pool manager(NOTICE: throw
 * an "out of memory" exception if returned value is nullptr), then move half
 * of key & value pairs from input page to newly created page
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
N *BPLUSTREE_TYPE::Split(N *node) {
  page_id_t newPageId;
  Page *newPage = buffer_pool_manager_->NewPage(&newPageId);
  assert(newPage != nullptr);
  N *newNode = reinterpret_cast<N *>(newPage->GetData());
  //不同类型的结点均存在初始化以及分裂
  newNode->Init(newPageId, node->GetParentPageId());
  node->MoveHalfTo(newNode, buffer_pool_manager_);
  return newNode;
}

/*
 * Insert key & value pair into internal page after split
 * @param   old_node      input page from split() method
 * @param   key
 * @param   new_node      returned page from split() method
 * User needs to first find the parent page of old_node, parent node must be
 * adjusted to take info of new_node into account. Remember to deal with split
 * recursively if necessary.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::InsertIntoParent(BPlusTreePage *old_node, const KeyType &key, BPlusTreePage *new_node,
                                      Transaction *transaction) {
  page_id_t parentId = old_node->GetParentPageId();
  if (parentId == INVALID_PAGE_ID) {
    //此时说明是根结点，无父节点存在，需重新生成根结点
    Page *const newPage = buffer_pool_manager_->NewPage(&root_page_id_);
    B_PLUS_TREE_INTERNAL_PAGE *newRoot = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(newPage->GetData());
    newRoot->Init(root_page_id_, INVALID_PAGE_ID);
    newRoot->PopulateNewRoot(old_node->GetPageId(), key, new_node->GetPageId());
    old_node->SetParentPageId(root_page_id_);
    new_node->SetParentPageId(root_page_id_);
    UpdateRootPageId();
    // fetch page and new page need to unpin page
    buffer_pool_manager_->UnpinPage(new_node->GetPageId(), true);
    buffer_pool_manager_->UnpinPage(newRoot->GetPageId(), true);
    return;
  } else {
    Page *page = buffer_pool_manager_->FetchPage(parentId);
    B_PLUS_TREE_INTERNAL_PAGE *parentPage = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(page->GetData());
    //由于该新节点需要插入到父节点内部，所以其父节点需要进行更新
    new_node->SetParentPageId(parentId);
    parentPage->InsertNodeAfter(old_node->GetPageId(), key, new_node->GetPageId());
    if (parentPage->GetSize() > parentPage->GetMaxSize()) {
      B_PLUS_TREE_INTERNAL_PAGE *newLeafPage = Split(parentPage);
      InsertIntoParent(parentPage, newLeafPage->KeyAt(0), newLeafPage, transaction);
    }
    // unpin函数内部打开的父节点以及传入的新节点
    buffer_pool_manager_->UnpinPage(parentPage->GetPageId(), true);
    buffer_pool_manager_->UnpinPage(new_node->GetPageId(), true);
    return;
  }
}

/*****************************************************************************
 * REMOVE
 *****************************************************************************/
/*
 * Delete key & value pair associated with input key
 * If current tree is empty, return immdiately.
 * If not, User needs to first find the right leaf page as deletion target, then
 * delete entry from leaf page. Remember to deal with redistribute or merge if
 * necessary.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::Remove(const KeyType &key, Transaction *transaction) {
  std::lock_guard<std::mutex> lock(latch_);
  if (IsEmpty()) return;
  Page *page = FindLeafPage(key);
  assert(page != nullptr);
  B_PLUS_TREE_LEAF_PAGE_TYPE *leaf = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page->GetData());
  printf("Remove key:%ld\n", key.ToString());
  int size = leaf->RemoveAndDeleteRecord(key, comparator_);
  if (size < leaf->GetMinSize()) CoalesceOrRedistribute(leaf, transaction);
  printf("%s\n", this->ToString(true).c_str());
  buffer_pool_manager_->UnpinPage(page->GetPageId(),true);
  return;
}

/*
 * User needs to first find the sibling of input page. If sibling's size + input
 * page's size > page's max size, then redistribute. Otherwise, merge.
 * Using template N to represent either internal page or leaf page.
 * @return: true means target leaf page should be deleted, false means no
 * deletion happens
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
bool BPLUSTREE_TYPE::CoalesceOrRedistribute(N *node, Transaction *transaction) {
  //如果可以合并：进行页的选择和合并
  //如果无法合并，则选择从其他页抽取一个结点，先找兄弟FindSibling
  if (node->IsRootPage()) {
		//该函数可能递归调用至根结点，故需要对根结点进行特殊处理
    return AdjustRoot(node);
  }
  N *sibling;
  // result 为true代表此时node为父页的首节点
  bool result = FindSibling(node, sibling);
  Page *parent = buffer_pool_manager_->FetchPage(node->GetParentPageId());
  B_PLUS_TREE_INTERNAL_PAGE *parentPage = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(parent->GetData());
  if (node->GetSize() + sibling->GetSize() <= node->GetMaxSize()) {
    //进行融合
    int removedIndex;
		//进行if判断，保证在父页删除的key为父页的非首节点
    if (result) {
      //此时需要把后继页合并到首节点上
      removedIndex = parentPage->ValueIndex(sibling->GetPageId());
      Coalesce(&node, &sibling, &parentPage, removedIndex, transaction);
    } else {
      //当前节点合并到前驱结点上
      removedIndex = parentPage->ValueIndex(node->GetPageId());
      Coalesce(&sibling, &node, &parentPage, removedIndex, transaction);
    }

    buffer_pool_manager_->UnpinPage(parentPage->GetPageId(), true);
    return true;
  }
  int nodeIndex = parentPage->ValueIndex(node->GetPageId());
  Redistribute(sibling, node, nodeIndex);  // unpin node,node2
  buffer_pool_manager_->UnpinPage(parentPage->GetPageId(), false);
  return false;
}

INDEX_TEMPLATE_ARGUMENTS
template <typename N>
bool BPLUSTREE_TYPE::FindSibling(N *node, N *&sibling) {
  Page *page = buffer_pool_manager_->FetchPage(node->GetParentPageId());
  B_PLUS_TREE_INTERNAL_PAGE *parent = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(page->GetData());
  int index = parent->ValueIndex(node->GetPageId());
  int siblingIndex = index - 1;
  //如果是该页的结点是父页的首节点，则从后继页抽一个，如果不是，则从前驱页抽一个。这样可以保证影响范围都是在同一个父页内，操作简单
  if (index == 0) {
    siblingIndex = index + 1;
  }
  page = buffer_pool_manager_->FetchPage(parent->ValueAt(siblingIndex));
  sibling = reinterpret_cast<N *>(page->GetData());
  buffer_pool_manager_->UnpinPage(parent->GetPageId(), false);
  return index == 0;
}
/*
 * Move all the key & value pairs from one page to its sibling page, and notify
 * buffer pool manager to delete this page. Parent page must be adjusted to
 * take info of deletion into account. Remember to deal with coalesce or
 * redistribute recursively if necessary.
 * Using template N to represent either internal page or leaf page.
 * @param   neighbor_node      sibling page of input "node"
 * @param   node               input from method coalesceOrRedistribute()
 * @param   parent             parent page of input "node"
 * @return  true means parent node should be deleted, false means no deletion
 * happend
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
bool BPLUSTREE_TYPE::Coalesce(N **neighbor_node, N **node,
                              BPlusTreeInternalPage<KeyType, page_id_t, KeyComparator> **parent, int index,
                              Transaction *transaction) {
  assert((*node)->GetSize() + (*neighbor_node)->GetSize() <= (*node)->GetMaxSize());
  (*node)->MoveAllTo(*neighbor_node,buffer_pool_manager_);
  page_id_t pId = (*node)->GetPageId();
  buffer_pool_manager_->UnpinPage(pId, true);
  buffer_pool_manager_->DeletePage(pId);
  buffer_pool_manager_->UnpinPage((*neighbor_node)->GetPageId(), true);
  (*parent)->Remove(index);
	//当内部页中size过小时或者仅剩余一个有效结点时，递归触发CoalesceOrRedistribute函数，对当前结点进行处理
  if ((*parent)->GetSize() < (*parent)->GetMinSize() || (*parent)->GetSize() == 2) {
    return CoalesceOrRedistribute(*parent, transaction);
  }
  return false;
}

/*
 * Redistribute key & value pairs from one page to its sibling page. If index ==
 * 0, move sibling page's first key & value pair into end of input "node",
 * otherwise move sibling page's last key & value pair into head of input
 * "node".
 * Using template N to represent either internal page or leaf page.
 * @param   neighbor_node      sibling page of input "node"
 * @param   node               input from method coalesceOrRedistribute()
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
void BPLUSTREE_TYPE::Redistribute(N *neighbor_node, N *node, int index) {
  if (index == 0) {
    neighbor_node->MoveFirstToEndOf(node, buffer_pool_manager_);
  } else {
    neighbor_node->MoveLastToFrontOf(node, buffer_pool_manager_);
  }
  buffer_pool_manager_->UnpinPage(node->GetPageId(), true);
  buffer_pool_manager_->UnpinPage(neighbor_node->GetPageId(), true);
}
/*
 * Update root page if necessary
 * NOTE: size of root page can be less than min size and this method is only
 * called within coalesceOrRedistribute() method
 * case 1: when you delete the last element in root page, but root page still
 * has one last child
 * case 2: when you delete the last element in whole b+ tree
 * @return : true means root page should be deleted, false means no deletion
 * happend
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::AdjustRoot(BPlusTreePage *old_root_node) {
  if (old_root_node->IsLeafPage()) {
		//此时root中size为0，且树中只有root，故直接删除结点，更新相关数据即可
    buffer_pool_manager_->UnpinPage(old_root_node->GetPageId(), false);
    buffer_pool_manager_->DeletePage(old_root_node->GetPageId());
    root_page_id_ = INVALID_PAGE_ID;
    UpdateRootPageId();
    return true;
  }
  if (old_root_node->GetSize() == 1) {
    //此时root中size为1，即根结点只有一个子页，原根结点可以被替代，故进行根结点的更新（根页作为内部页时最少需2个结点）
    B_PLUS_TREE_INTERNAL_PAGE *root = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(old_root_node);
    const page_id_t newRootId = root->RemoveAndReturnOnlyChild();
    root_page_id_ = newRootId;
    UpdateRootPageId();
    Page *page = buffer_pool_manager_->FetchPage(root_page_id_);
    assert(page != nullptr);
    B_PLUS_TREE_INTERNAL_PAGE *newRoot = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(page->GetData());
    newRoot->SetParentPageId(INVALID_PAGE_ID);
    buffer_pool_manager_->UnpinPage(root_page_id_, true);
    buffer_pool_manager_->UnpinPage(old_root_node->GetPageId(), false);
    buffer_pool_manager_->DeletePage(old_root_node->GetPageId());
  }
  return false;
}

/*****************************************************************************
 * INDEX ITERATOR
 *****************************************************************************/
/*
 * Input parameter is void, find the leaftmost leaf page first, then construct
 * index iterator
 * @return : index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE BPLUSTREE_TYPE::Begin() {
  KeyType _;
  Page *page = FindLeafPage(_, true);
  B_PLUS_TREE_LEAF_PAGE_TYPE *start_leaf = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page->GetData());
  return INDEXITERATOR_TYPE(start_leaf, 0, buffer_pool_manager_);
}

/*
 * Input parameter is low key, find the leaf page that contains the input key
 * first, then construct index iterator
 * @return : index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE BPLUSTREE_TYPE::Begin(const KeyType &key) {
  Page *page = FindLeafPage(key, false);
  B_PLUS_TREE_LEAF_PAGE_TYPE *start_leaf = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page->GetData());
  if (page == nullptr) {
    return INDEXITERATOR_TYPE(start_leaf, 0, buffer_pool_manager_);
  }
  int idx = start_leaf->KeyIndex(key, comparator_);
  return INDEXITERATOR_TYPE(start_leaf, idx, buffer_pool_manager_);
}

/*
 * Input parameter is void, construct an index iterator representing the end
 * of the key/value pair in the leaf node
 * @return : index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE BPLUSTREE_TYPE::End() { return INDEXITERATOR_TYPE(nullptr, 0, buffer_pool_manager_); }

/*****************************************************************************
 * UTILITIES AND DEBUG
 *****************************************************************************/
/*
 * Find leaf page containing particular key, if leftMost flag == true, find
 * the left most leaf page
 */
INDEX_TEMPLATE_ARGUMENTS
Page *BPLUSTREE_TYPE::FindLeafPage(const KeyType &key, bool leftMost) {
  if (IsEmpty()) return nullptr;
  Page *page = buffer_pool_manager_->FetchPage(root_page_id_);
  BPlusTreePage *pointer = reinterpret_cast<BPlusTreePage *>(page->GetData());
  if (pointer == nullptr) {
    printf("FindLeafPage get root false");
  }
  page_id_t next;
  for (page_id_t cur = root_page_id_; !pointer->IsLeafPage();) {
    B_PLUS_TREE_INTERNAL_PAGE *internalPage = static_cast<B_PLUS_TREE_INTERNAL_PAGE *>(pointer);
    if (leftMost) {
      //这里出现问题： cannot convert 'bustub::RID' to 'bustub::page_id_t {aka int}' in assignment
      //这是因为B_PLUS_TREE_INTERNAL_PAGE_TYPE的宏定义中类型不明确，ValueType未指明类型
      //故在这里ValueAt返回ValueType的类型不明确
      //解决方法：重新宏定义一组类型，将ValueType说明为page_id_t，则编译时该函数的ValueType被认为是page_id_t,而不是bustub::RID
      next = internalPage->ValueAt(0);
    } else {
      next = internalPage->Lookup(key, comparator_);
    }
    buffer_pool_manager_->UnpinPage(cur, false);
    cur = next;
    page = buffer_pool_manager_->FetchPage(cur);
    pointer = reinterpret_cast<BPlusTreePage *>(page->GetData());
  }
  return page;
}

/*
 * Update/Insert root page id in header page(where page_id = 0, header_page is
 * defined under include/page/header_page.h)
 * Call this method everytime root page id is changed.
 * @parameter: insert_record      defualt value is false. When set to true,
 * insert a record <index_name, root_page_id> into header page instead of
 * updating it.
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::UpdateRootPageId(int insert_record) {
  HeaderPage *header_page = static_cast<HeaderPage *>(buffer_pool_manager_->FetchPage(HEADER_PAGE_ID));
  if (insert_record != 0) {
    // create a new record<index_name + root_page_id> in header_page
    header_page->InsertRecord(index_name_, root_page_id_);
  } else {
    // update root_page_id in header_page
    header_page->UpdateRecord(index_name_, root_page_id_);
  }
  buffer_pool_manager_->UnpinPage(HEADER_PAGE_ID, true);
}

/*
 * This method is used for test only
 * Read data from file and insert one by one
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::InsertFromFile(const std::string &file_name, Transaction *transaction) {
  int64_t key;
  std::ifstream input(file_name);
  while (input) {
    input >> key;

    KeyType index_key;
    index_key.SetFromInteger(key);
    RID rid(key);
    Insert(index_key, rid, transaction);
  }
}
/*
 * This method is used for test only
 * Read data from file and remove one by one
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::RemoveFromFile(const std::string &file_name, Transaction *transaction) {
  int64_t key;
  std::ifstream input(file_name);
  while (input) {
    input >> key;
    KeyType index_key;
    index_key.SetFromInteger(key);
    Remove(index_key, transaction);
  }
}

/**
 * This method is used for debug only, You don't  need to modify
 * @tparam KeyType
 * @tparam ValueType
 * @tparam KeyComparator
 * @param page
 * @param bpm
 * @param out
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::ToGraph(BPlusTreePage *page, BufferPoolManager *bpm, std::ofstream &out) const {
  std::string leaf_prefix("LEAF_");
  std::string internal_prefix("INT_");
  if (page->IsLeafPage()) {
    LeafPage *leaf = reinterpret_cast<LeafPage *>(page);
    // Print node name
    out << leaf_prefix << leaf->GetPageId();
    // Print node properties
    out << "[shape=plain color=green ";
    // Print data of the node
    out << "label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
    // Print data
    out << "<TR><TD COLSPAN=\"" << leaf->GetSize() << "\">P=" << leaf->GetPageId() << "</TD></TR>\n";
    out << "<TR><TD COLSPAN=\"" << leaf->GetSize() << "\">"
        << "max_size=" << leaf->GetMaxSize() << ",min_size=" << leaf->GetMinSize() << "</TD></TR>\n";
    out << "<TR>";
    for (int i = 0; i < leaf->GetSize(); i++) {
      out << "<TD>" << leaf->KeyAt(i) << "</TD>\n";
    }
    out << "</TR>";
    // Print table end
    out << "</TABLE>>];\n";
    // Print Leaf node link if there is a next page
    if (leaf->GetNextPageId() != INVALID_PAGE_ID) {
      out << leaf_prefix << leaf->GetPageId() << " -> " << leaf_prefix << leaf->GetNextPageId() << ";\n";
      out << "{rank=same " << leaf_prefix << leaf->GetPageId() << " " << leaf_prefix << leaf->GetNextPageId() << "};\n";
    }

    // Print parent links if there is a parent
    if (leaf->GetParentPageId() != INVALID_PAGE_ID) {
      out << internal_prefix << leaf->GetParentPageId() << ":p" << leaf->GetPageId() << " -> " << leaf_prefix
          << leaf->GetPageId() << ";\n";
    }
  } else {
    InternalPage *inner = reinterpret_cast<InternalPage *>(page);
    // Print node name
    out << internal_prefix << inner->GetPageId();
    // Print node properties
    out << "[shape=plain color=pink ";  // why not?
    // Print data of the node
    out << "label=<<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\" CELLPADDING=\"4\">\n";
    // Print data
    out << "<TR><TD COLSPAN=\"" << inner->GetSize() << "\">P=" << inner->GetPageId() << "</TD></TR>\n";
    out << "<TR><TD COLSPAN=\"" << inner->GetSize() << "\">"
        << "max_size=" << inner->GetMaxSize() << ",min_size=" << inner->GetMinSize() << "</TD></TR>\n";
    out << "<TR>";
    for (int i = 0; i < inner->GetSize(); i++) {
      out << "<TD PORT=\"p" << inner->ValueAt(i) << "\">";
      if (i > 0) {
        out << inner->KeyAt(i);
      } else {
        out << " ";
      }
      out << "</TD>\n";
    }
    out << "</TR>";
    // Print table end
    out << "</TABLE>>];\n";
    // Print Parent link
    if (inner->GetParentPageId() != INVALID_PAGE_ID) {
      out << internal_prefix << inner->GetParentPageId() << ":p" << inner->GetPageId() << " -> " << internal_prefix
          << inner->GetPageId() << ";\n";
    }
    // Print leaves
    for (int i = 0; i < inner->GetSize(); i++) {
      auto child_page = reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(inner->ValueAt(i))->GetData());
      ToGraph(child_page, bpm, out);
      if (i > 0) {
        auto sibling_page = reinterpret_cast<BPlusTreePage *>(bpm->FetchPage(inner->ValueAt(i - 1))->GetData());
        if (!sibling_page->IsLeafPage() && !child_page->IsLeafPage()) {
          out << "{rank=same " << internal_prefix << sibling_page->GetPageId() << " " << internal_prefix
              << child_page->GetPageId() << "};\n";
        }
        bpm->UnpinPage(sibling_page->GetPageId(), false);
      }
    }
  }
  bpm->UnpinPage(page->GetPageId(), false);
}

/**
 * This function is for debug only, you don't need to modify
 * @tparam KeyType
 * @tparam ValueType
 * @tparam KeyComparator
 * @param page
 * @param bpm
 */
INDEX_TEMPLATE_ARGUMENTS
std::string BPLUSTREE_TYPE::ToString(bool verbose) {
  if (IsEmpty()) {
    return "Empty tree";
  }
  std::queue<BPlusTreePage *> todo, tmp;
  std::stringstream tree;
  BPlusTreePage *node = reinterpret_cast<BPlusTreePage *>(buffer_pool_manager_->FetchPage(root_page_id_));
  if (node == nullptr) {
    return "all page are pinned while printing";
  }
  todo.push(node);
  bool first = true;
  while (!todo.empty()) {
    node = todo.front();
    if (first) {
      first = false;
      tree << "| ";
    }
    // leaf page, print all key-value pairs
    if (node->IsLeafPage()) {
      B_PLUS_TREE_LEAF_PAGE_TYPE* page = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(node);
      tree << page->ToString(verbose) <<"| ";
    } else {
      B_PLUS_TREE_INTERNAL_PAGE* page = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(node);
      tree << page->ToString(verbose) <<"| ";
      for (int i = 0; i < page->GetSize(); i++) {
        Page *sonPage = buffer_pool_manager_->FetchPage(page->ValueAt(i));
        if (sonPage == nullptr) printf("all page are pinned while printing");
        BPlusTreePage *node = reinterpret_cast<BPlusTreePage *>(sonPage->GetData());
        tmp.push(node);
      }
    }
    todo.pop();
    if (todo.empty() && !tmp.empty()) {
      todo.swap(tmp);
      tree << '\n';
      first = true;
    }
    
    buffer_pool_manager_->UnpinPage(node->GetPageId(), false);
  }
  return tree.str();
}

template class BPlusTree<GenericKey<4>, RID, GenericComparator<4>>;
template class BPlusTree<GenericKey<8>, RID, GenericComparator<8>>;
template class BPlusTree<GenericKey<16>, RID, GenericComparator<16>>;
template class BPlusTree<GenericKey<32>, RID, GenericComparator<32>>;
template class BPlusTree<GenericKey<64>, RID, GenericComparator<64>>;

}  // namespace bustub
