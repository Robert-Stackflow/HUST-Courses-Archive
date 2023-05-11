//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/page/b_plus_tree_page.cpp
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "storage/page/b_plus_tree_page.h"

namespace bustub {

/*
 * Helper methods to get/set page type
 * Page type enum class is defined in b_plus_tree_page.h
 */
bool BPlusTreePage::IsLeafPage() const {
  return page_type_ == IndexPageType::LEAF_PAGE;
}
bool BPlusTreePage::IsRootPage() const {
  return parent_page_id_ == INVALID_PAGE_ID;
}
void BPlusTreePage::SetPageType(IndexPageType page_type) { page_type_ = page_type; }

/*
 * Helper methods to get/set size (number of key/value pairs stored in that
 * page)
 */
int BPlusTreePage::GetSize() const { return size_; }
void BPlusTreePage::SetSize(int size) {
  size_ = size;
  return;
}
void BPlusTreePage::IncreaseSize(int amount) {
  size_ += amount;
}

/*
 * Helper methods to get/set max size (capacity) of the page
 */
int BPlusTreePage::GetMaxSize() const { return max_size_; }
void BPlusTreePage::SetMaxSize(int size) {
  max_size_ = size;
}

/*
 * Helper method to get min page size
 * Generally, min page size == max page size / 2
 * 特殊情况
 * 如果此时为根节点：根节点极可能是内部节点也可能是叶子节点
 * 内部节点：此时至少有一个数值用来区分左右子树，故有 1.空key+左指针 2.数值+指针
 * 叶子节点：没有存储数据。此时为空 即空key+左指针
 * 其余正常处理
 */
int BPlusTreePage::GetMinSize() const {
  if (IsRootPage()) {
    return IsLeafPage() ? 1 : 2 ;
  }
  return (max_size_ + 1 )/ 2;
}

/*
 * Helper methods to get/set parent page id
 */
page_id_t BPlusTreePage::GetParentPageId() const { return parent_page_id_; }
void BPlusTreePage::SetParentPageId(page_id_t parent_page_id) { parent_page_id_ = parent_page_id; }

/*
 * Helper methods to get/set self page id
 */
page_id_t BPlusTreePage::GetPageId() const { return page_id_; }
void BPlusTreePage::SetPageId(page_id_t page_id) { page_id_ = page_id; }

/*
 * Helper methods to set lsn
 */
void BPlusTreePage::SetLSN(lsn_t lsn) { lsn_ = lsn; }

}  // namespace bustub
