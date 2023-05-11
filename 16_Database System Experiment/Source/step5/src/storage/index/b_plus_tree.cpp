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
 * �������ܣ�
 *  �ж�B+���Ƿ�Ϊ��
 * ���飺
 *  B+����ʼ����root_page_id_ΪINVALID_PAGE_ID
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::IsEmpty() const {
    //֮ǰ��page���;�Ϊ��㣬���ڸ����ͱ�ʾ����B+��
    return root_page_id_ == INVALID_PAGE_ID;
}
/*****************************************************************************
 * ����
 *****************************************************************************/
/*
 * �������ܣ�
 *  ��B+���У�����keyֵ��Ӧ�ļ�¼
 *  ��������򷵻�true��������¼push��result��
 *  ����������򷵻�false
 * ���飺
 *  1.ͨ������FindLeafPage(key)����Ѱ��keyֵ����Ҷ���
 *  2.��ǰҶ�ӽ���в����ڸ�keyֵ������false
 *  3.��Ҷ�ӽ�㲻��ʹ�ú���Ҫ��ʱunpin�ͷţ����⻺�����ڴ�й¶
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::GetValue(const KeyType &key, std::vector<ValueType> *result) {
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

/*
 * �������ܣ�
 *  ��B+���У�����keyֵӦ�ڵ�Ҷ���
 *  ��leftMostΪtrueʱ��ֱ�ӷ�������Ҷ��㣨���ڱ������������¼��
 * ���飺
 *  1.��B+����ʱֱ�ӷ��ؿ�ָ��
 *  2.ͨ��buffer_pool_manager_->FetchPage(page_id)�Ӵ����ж����ض�Page
 *  3.���ض�page������Ҫʱ����buffer_pool_manager_->UnpinPage(page_id, is_dirty)����page������ռ�û�����
 *  3.��������������ֱ��Ŀ��Ҷ�ӽ��
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
            //����������⣺ cannot convert 'bustub::RID' to 'bustub::page_id_t {aka int}' in assignment
            //������ΪB_PLUS_TREE_INTERNAL_PAGE_TYPE�ĺ궨�������Ͳ���ȷ��ValueTypeδָ������
            //��������ValueAt����ValueType�����Ͳ���ȷ
            //������������º궨��һ�����ͣ���ValueType˵��Ϊpage_id_t�������ʱ�ú�����ValueType����Ϊ��page_id_t,������bustub::RID
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

/*****************************************************************************
 * ����
 *****************************************************************************/
/*
 * �������ܣ�
 *  ��B+���в���key�Լ���Ӧ��value���ɹ�����true��ʧ���򷵻�false
 * ���飺
 *  1.�ж�B+���Ƿ�Ϊ�գ�Ϊ��ʱ����StartNewTree��������
 *  2.���ǿգ������InsertIntoLeaf�������������¼
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::Insert(const KeyType &key, const ValueType &value) {
  std::lock_guard<std::mutex> lock(latch_);
  if (IsEmpty()) {
    //printf("new tree start\n");
    StartNewTree(key, value);
    return true;
  }
  bool res = InsertIntoLeaf(key, value);
  return res;
}
/*
 * �������ܣ�
 *  ��B+��Ϊ��ʱ�����¼ʱ���ú�����������һ����B+������ʼ���������
 * ���飺
 *  1.������ʱӦΪҶ���
 *  2.����UpdateRootPageId(rootPageID)����ͷ�ļ��еĸ�����¼ //UpdateRootPageId����ʵ��
 *  3.��ʱunpin����ʹ�õ�page�����⻺�����ڴ�й©��ע���Ƿ�Ϊ��ҳ
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::StartNewTree(const KeyType &key, const ValueType &value) {
  page_id_t pageId;
  Page *rootPage = buffer_pool_manager_->NewPage(&pageId);
  assert(rootPage != nullptr);
  B_PLUS_TREE_LEAF_PAGE_TYPE *root = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(rootPage->GetData());

  root->Init(pageId, INVALID_PAGE_ID, leaf_max_size_);
  //printf("start %d \n", pageId);
  //���µ�ǰB+���ĸ�ҳID
  root_page_id_ = pageId;
  UpdateRootPageId(pageId);
  root->Insert(key, value, comparator_);
  //printf("new root size:%d\n", root->GetSize());
  buffer_pool_manager_->UnpinPage(pageId, true);
  return;
}

/*
 * �������ܣ�
 *  ����ȷ��Ҷ������key�Լ���Ӧ��value���ɹ�����true��ʧ�ܷ���false
 * ���飺
 *  1.�ҵ�keyֵӦ�ڵ�Ҷ���
 *  2.keyֵ���Ѵ��ڣ�ֱ�ӷ���false(Ϊ�˱���ʵ�֣���ǰ��֧��unique key)
 *  3.��������жϽ��Ԫ���Ƿ񳬹�max_size,������Split()��InsertIntoParent()���к�������
 *  4.ע��unpinPage�����⻺�����ڴ�й¶
 */
INDEX_TEMPLATE_ARGUMENTS
bool BPLUSTREE_TYPE::InsertIntoLeaf(const KeyType &key, const ValueType &value) {
  Page *pPage = FindLeafPage(key);
  if (pPage == nullptr) {
    return false;
  }
  //printf("FindLeafPage successfully:");
  B_PLUS_TREE_LEAF_PAGE_TYPE *page = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(pPage->GetData());
  //printf("before insert size:%d\n", page->GetSize());
  ValueType v;
  if (page->Lookup(key, &v, comparator_)) {
    //printf("insert key already existed \n");
    buffer_pool_manager_->UnpinPage(page->GetPageId(), false);
    return false;
  }
  //printf("insert key:%ld to page:%d \n", key.ToString(), page->GetPageId());
  page->Insert(key, value, comparator_);
  //printf("%s\n", this->ToString(true).c_str());
  int size = page->GetSize();
  //ÿ�β���֮������жϣ��Ƿ��Ѿ��������ֵ��ѡ��ֱ�ӽ��з���
  //����MAXSIZE������һ���հ׽�㣬�������Ա�֤����������ᵼ������Խ��
  //�����Ϳ����Ȳ��룬�ٷ��ѽ�㣬��������Ҫ�ȷ����ڳ��ռ䣬�ٲ�������һ���ĸ��Ӳ���
  if (size > page->GetMaxSize()) {
    //printf("---------start to split,new page------------- \n");
    B_PLUS_TREE_LEAF_PAGE_TYPE *newLeafPage = Split(page);
    InsertIntoParent(page, newLeafPage->KeyAt(0), newLeafPage);
    //printf("%s\n", this->ToString(true).c_str());
  }
  // InsertIntoParent�����ڲ���unpin�½�㣬��ֻ��unpin�ɽ�㼴��
  buffer_pool_manager_->UnpinPage(page->GetPageId(), false);
  return true;
}
/*
 * �������ܣ�
 *  ��������Ľ��(Ҷ���or�ڲ����)�����������ɵĽ��
 * ���飺
 *  1.������ͬ���͵��½�㲢��ʼ��
 *  2.����MoveHalfTo()���н��ķ���
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
N *BPLUSTREE_TYPE::Split(N *node) {
  page_id_t newPageId;
  Page *newPage = buffer_pool_manager_->NewPage(&newPageId);
  N *newNode = reinterpret_cast<N *>(newPage->GetData());
  //��ͬ���͵Ľ������ڳ�ʼ���Լ�����
  if(node->IsLeafPage())   newNode->Init(newPageId, node->GetParentPageId(),leaf_max_size_);
  else newNode->Init(newPageId, node->GetParentPageId(),internal_max_size_);
  node->MoveHalfTo(newNode, buffer_pool_manager_);
  return newNode;
}


/*
 * �������ܣ�
 *  �������½������丸����в�����ȷ������
 *  @param   old_node      ���ѹ���ԭ���
 *  @param   key      ��������keyֵ
 *  @param   new_node      ���Ѻ����ɵ��½��
 * ���飺
 *  1.��Ϊ�������ѣ��������ڸ���ʱ��Ӧ�����¸���㣬������PopulateNewRoot������Ӷ�ԭ����㼰���ѽ�������
 *  2.����UpdateRootPageId����rootPageID
 *  3.��Ϊ�ڲ������ѣ��ڸ��ڵ��в�����Ԫ�غ�������max_size,����Split()��InsertIntoParent()����
 *  4.����ParentPageId
 *  5.ע��unpinPage�����⻺�����ڴ�й¶
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::InsertIntoParent(BPlusTreePage *old_node, const KeyType &key, BPlusTreePage *new_node) {
  page_id_t parentId = old_node->GetParentPageId();
  if (parentId == INVALID_PAGE_ID) {
    //��ʱ˵���Ǹ���㣬�޸������ڣ����������ɸ����
    Page *const newPage = buffer_pool_manager_->NewPage(&root_page_id_);
    B_PLUS_TREE_INTERNAL_PAGE *newRoot = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(newPage->GetData());
    newRoot->Init(root_page_id_, INVALID_PAGE_ID,internal_max_size_);
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
    //���ڸ��½����Ҫ���뵽������ڲ��������丸�����Ҫ���и���
    new_node->SetParentPageId(parentId);
    parentPage->InsertNodeAfter(old_node->GetPageId(), key, new_node->GetPageId());
    if (parentPage->GetSize() > parentPage->GetMaxSize()) {
      B_PLUS_TREE_INTERNAL_PAGE *newLeafPage = Split(parentPage);
      InsertIntoParent(parentPage, newLeafPage->KeyAt(0), newLeafPage);
    }
    // unpin�����ڲ��򿪵ĸ�����Լ�������½��
    buffer_pool_manager_->UnpinPage(parentPage->GetPageId(), true);
    buffer_pool_manager_->UnpinPage(new_node->GetPageId(), true);
    return;
  }
}

/*
 * �������ܣ�
 *  ����ָ��B+���׸���¼�ĵ�����
 * ���飺
 *  1.����ʵ��index_iterator.cpp�ļ�
 *  2.����FindLeafPage�����ҵ�����Ҷ�ӽ�㣬������ָ��B+���׸���¼
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE BPLUSTREE_TYPE::Begin() {
  KeyType _;
  Page *page = FindLeafPage(_, true);
  B_PLUS_TREE_LEAF_PAGE_TYPE *start_leaf = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page->GetData());
  return INDEXITERATOR_TYPE(start_leaf, 0, buffer_pool_manager_);
}

/*
 * �������ܣ�
 *  ����ָ��B+���ض�keyֵ��¼�ĵ�����
 * ���飺
 *  1.����ʵ��index_iterator.cpp�ļ�
 *  2.����FindLeafPage�����ҵ�keyֵ����Ҷ�ӽ�㣬������ָ��ü�¼(�������¼)
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
 * �������ܣ�
 *  ����IsEnd״̬��B+����¼������
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE BPLUSTREE_TYPE::End() { return INDEXITERATOR_TYPE(nullptr, 0, buffer_pool_manager_); }

template class BPlusTree<GenericKey<4>, RID, GenericComparator<4>>;
template class BPlusTree<GenericKey<8>, RID, GenericComparator<8>>;
template class BPlusTree<GenericKey<16>, RID, GenericComparator<16>>;
template class BPlusTree<GenericKey<32>, RID, GenericComparator<32>>;
template class BPlusTree<GenericKey<64>, RID, GenericComparator<64>>;

}  // namespace bustub
