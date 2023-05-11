#include "storage/page/b_plus_tree_page.h"

namespace bustub {

/*
 * 函数功能：
 *  判断页类型是否为叶子结点
 * 建议：
 *  enum class IndexPageType { INVALID_INDEX_PAGE = 0, LEAF_PAGE, INTERNAL_PAGE }
 *  （定义于b_plus_tree_page.h头文件中）
 */
bool BPlusTreePage::IsLeafPage() const {

}
/*
 * 函数功能：
 *  判断页类型是否为根结点
 * 建议：
 *  static constexpr int INVALID_PAGE_ID = -1;// invalid page id（定义与config.h中）
 *  父节点pageId为INVALID_PAGE_ID时即为根结点
 */
bool BPlusTreePage::IsRootPage() const {
  
}
/*
 * 函数功能：
 *    设置索引页类型
 */
void BPlusTreePage::SetPageType(IndexPageType page_type) {  }

/*
 * 函数功能：
 *  get/set size (size：当前结点中存放的元素（键值对）个数)
 *  IncreaseSize 增加结点元素大小
 */
int BPlusTreePage::GetSize() const { }
void BPlusTreePage::SetSize(int size) {
  size_ = size;
  return;
}
void BPlusTreePage::IncreaseSize(int amount) {
  size_ += amount;
}

/*
 * 函数功能：
 *  get/set max size
 */
int BPlusTreePage::GetMaxSize() const {  }
void BPlusTreePage::SetMaxSize(int size) {
  
}

/*
 * 函数功能：
 *  获取当前结点允许的最少元素个数
 * 建议：
 *  1.如果此时为根节点：根节点可能是内部节点也可能是叶子节点
 *  内部节点：此时至少存在两个索引
 *  叶子节点：此时至少存在一条记录
 *  2.非根结点正常处理，至少要求是半满以上
 *    如果是叶结点，[(max_size_-1)/2]=(max_size_-1+1)/2
 *    如果是内部结点，第一个key是不使用的，(max_size_-1-1+1)/2+1
 */
int BPlusTreePage::GetMinSize() const {
  
}

/*
 *函数功能：
 *  get/set parent page id
 * 提示：
 *  1.设置结点的父节点方法只能通过SetParentPageId来实现 
 */
page_id_t BPlusTreePage::GetParentPageId() const {  }
void BPlusTreePage::SetParentPageId(page_id_t parent_page_id) {  }

/*
 *函数功能：
 *  get/set self page id
 */
page_id_t BPlusTreePage::GetPageId() const {  }
void BPlusTreePage::SetPageId(page_id_t page_id) {  }

/*
 *函数功能：
 * set lsn
 */
void BPlusTreePage::SetLSN(lsn_t lsn) {  lsn_ = lsn;  }

}