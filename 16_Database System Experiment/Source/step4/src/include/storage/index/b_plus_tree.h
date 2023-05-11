#pragma once

#include <queue>
#include <string>
#include <vector>

#include "concurrency/transaction.h"
#include "storage/index/index_iterator.h"
#include "storage/page/b_plus_tree_internal_page.h"
#include "storage/page/b_plus_tree_leaf_page.h"

namespace bustub {

#define BPLUSTREE_TYPE BPlusTree<KeyType, ValueType, KeyComparator>

/**
 * Main class providing the API for the Interactive B+ Tree.
 *
 * Implementation of simple b+ tree data structure where internal pages direct
 * the search and leaf pages contain actual data.
 * (1) We only support unique key
 * (2) support insert & remove
 * (3) The structure should shrink and grow dynamically
 * (4) Implement index iterator for range scan
 */
INDEX_TEMPLATE_ARGUMENTS
class BPlusTree {
  using InternalPage = BPlusTreeInternalPage<KeyType, page_id_t, KeyComparator>;
  using LeafPage = BPlusTreeLeafPage<KeyType, ValueType, KeyComparator>;

 public:

  explicit BPlusTree(std::string name, BufferPoolManager *buffer_pool_manager, const KeyComparator &comparator,
                     int leaf_max_size = LEAF_PAGE_SIZE, int internal_max_size = INTERNAL_PAGE_SIZE);

  // Returns true if this B+ tree has no keys and values.
  bool IsEmpty() const;

  // Insert a key-value pair into this B+ tree.
  bool Insert(const KeyType &key, const ValueType &value);

  void Print(BufferPoolManager *bpm) {
      printf("%s\n",ToString(true).c_str());
  }

  // return the value associated with a given key
  bool GetValue(const KeyType &key, std::vector<ValueType> *result);

  // index iterator
  INDEXITERATOR_TYPE Begin();
  INDEXITERATOR_TYPE Begin(const KeyType &key);
  INDEXITERATOR_TYPE End();


  // read data from file and insert one by one
  void InsertFromFile(const std::string &file_name);

  // read data from file and remove one by one
  void RemoveFromFile(const std::string &file_name);
  // expose for test purpose
  Page *FindLeafPage(const KeyType &key, bool leftMost = false);

  //输出当前B+树状态
  std::string ToString(bool verbose){
      if (IsEmpty()) {
          return "Empty tree";
      }
      //双队列，tode为正在用于B+树输出的队列，只存储同一层的结点，tmp用于暂时存储B+下一层的结点
      std::queue<page_id_t> todo, tmp;
      std::stringstream tree;
      BPlusTreePage *node;
      page_id_t pageID;
      todo.push(root_page_id_);
      bool first = true;
      while (!todo.empty()) {
          pageID = todo.front();
          node = reinterpret_cast<BPlusTreePage *>(buffer_pool_manager_->FetchPage(pageID)->GetData());
          if (node == nullptr) {
              return "all page are pinned while printing";
          }
          if (first) {
              first = false;
              tree << "| ";
          }
          if (node->IsLeafPage()) {
              B_PLUS_TREE_LEAF_PAGE_TYPE* page = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(node);
              tree << page->ToString(verbose) <<"| ";
          } else {
              B_PLUS_TREE_INTERNAL_PAGE* page = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(node);
              tree << page->ToString(verbose) <<"| ";
              for (int i = 0; i < page->GetSize(); i++) {
                  //此处会先pin大量子页，直到子页出队列才会unpin，故可能因大量子页等待而导致缓冲区占满，导致出现BUG
                  //优化：仅向队列存入pageID，只有使用的时候才会fetch
                  tmp.push(page->ValueAt(i));
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

 private:
  void StartNewTree(const KeyType &key, const ValueType &value);

  bool InsertIntoLeaf(const KeyType &key, const ValueType &value);

  void InsertIntoParent(BPlusTreePage *old_node, const KeyType &key, BPlusTreePage *new_node);

  template <typename N>
  N *Split(N *node);

  void UpdateRootPageId(int insert_record = 0);


    // member variable
  std::string index_name_;
  page_id_t root_page_id_;
  BufferPoolManager *buffer_pool_manager_;
  KeyComparator comparator_;
  int leaf_max_size_;
  int internal_max_size_;
  std::mutex latch_;
};

}  // namespace bustub
