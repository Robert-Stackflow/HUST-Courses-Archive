## 1.BPlusTreePage的设计

### 任务描述

本关任务：作为B+树索引结点类型的数据结构设计的第一部分：实现BPlusTreePage类，该类是B+树叶结点类型和内部结点类型的父类，提供B+树结点的基本功能。

### 相关知识

为了完成本关任务，你需要了解：B+树基础知识

#### BPlusTreePage 结构简述

BPlusTreePage作为BPlusTreeInternalPage与BPlusTreeInternalPage父类，包含了B+树结点的基本信息和功能，比如结点类型，包含元素存储最大值以及现存元素个数，父结点id，当前结点id。

### 相关变量声明

```
//B+树结点类型定义，定义在b_plus_tree_page.cpp中
enum class IndexPageType { INVALID_INDEX_PAGE = 0, LEAF_PAGE, INTERNAL_PAGE };//无效结点，定义在config.h中，可直接使用该常量static constexpr int INVALID_PAGE_ID = -1;                                    // invalid page id//B+树中页的唯一标识page_id_t page_id_;
```

### 关卡内容

请在b_plus_tree_page.cpp文件中实现下列函数：

```
#pragma once
#include <cassert>
#include <climits>
#include <cstdlib>
#include <string>

#include "buffer/buffer_pool_manager.h"
#include "storage/index/generic_key.h"

namespace bustub {

#define MappingType std::pair<KeyType, ValueType>

#define INDEX_TEMPLATE_ARGUMENTS template <typename KeyType, typename ValueType, typename KeyComparator>

/* 定义索引类型
*/
enum class IndexPageType { INVALID_INDEX_PAGE = 0, LEAF_PAGE, INTERNAL_PAGE };

/**
 * 内部结点和叶结点均继承自该结点
 *
 * BPlusTreePage存储在Page类的data中，处于Page的首部
 */
class BPlusTreePage {
 public:
  
  bool IsLeafPage() const;
  bool IsRootPage() const;
  void SetPageType(IndexPageType page_type);

  int GetSize() const;
  void SetSize(int size);
  void IncreaseSize(int amount);

  int GetMaxSize() const;
  void SetMaxSize(int max_size);
  int GetMinSize() const;

  page_id_t GetParentPageId() const;
  void SetParentPageId(page_id_t parent_page_id);

  page_id_t GetPageId() const;
  void SetPageId(page_id_t page_id);

  void SetLSN(lsn_t lsn = INVALID_LSN);

 private:
  //页的类型,取值enum IndexPageType
  IndexPageType page_type_ __attribute__((__unused__));
  //日志序列号，用于并发索引
  lsn_t lsn_ __attribute__((__unused__));
  //一个页里的键值对数量
  int size_ __attribute__((__unused__));
  //一个页里的键值对最大数量
  int max_size_ __attribute__((__unused__));
  //父结点的页ID，根节点是没有父节点，可以定义根节点的parent_page_id_=INVALID_PAGE_ID
  //定义于config.h,static constexpr int INVALID_PAGE_ID = -1;
  page_id_t parent_page_id_ __attribute__((__unused__));
  //本结点的id
  page_id_t page_id_ __attribute__((__unused__));
};

}
```

## 2.BPlusTreeInternalPage的设计

### 任务描述

本关任务：作为B+树索引结点类型的数据结构设计的第二部分：实现BPlusTreeInternalPage类，该类作为B+树的内部结点类型，提供B+树内部结点的功能。

### 相关知识

为了完成本关任务，你需要了解：B+树内部结点结构与功能

#### BPlusTreeInternalPage 结构简述

内部页不存储任何实际数据，而是存储有序的m个键条目和m + 1个指针（也称为page_id）。 由于指针的数量不等于键的数量，因此将第一个键设置为无效，并且查找方法应始终从第二个键开始。 任何时候，每个内部页面至少有一半已满。 在删除期间，可以将两个半满页面合并为合法页面，或者可以将其重新分配以避免合并，而在插入期间，可以将一个完整页面分为两部分。 内部结点成员在BPlusTreePage的基础上额外增加一个数组，用于存储索引信息。 一个Max_size为n的内部结点，有n-1个索引键和n个子结点索引（由于二者数量不相同，一般第一个索引键为无效键），即该数组有如下结构：

| INVALID_KEY+PAGE_ID(0) | KEY(1)+PAGE_ID(1) | ...  | KEY(n)+PAGE_ID(n) |
| ---------------------- | ----------------- | ---- | ----------------- |
|                        |                   |      |                   |

键在数组中维持有序排列。

### 相关变量声明

```
//BPlusTreeInternalPage中的索引数组
MappingType array_[0];
//索引键值对，内部结点中为<Key,page_id_t> //
using page_id_t = int32_t
MappingType std::pair<KeyType, ValueType>
//缓冲区对象，负责特定页的获取
BufferPoolManager *buffer_pool_manager
//比较器，负责键的比较
KeyComparator &comparator
```

### 关卡内容

请在b_plus_tree_internal_page.cpp文件中实现下列函数：

函数功能详细介绍请参照文件内函数注释

### 帮助与提醒

#### 关于KeyComparator类的使用：

KeyComparator类用于进行Key值的比较，使用方法如下：

```
KeyType key1,key2;
comparator(key1, key2) > 0 //key1 > key2
comparator(key1, key2) = 0 //key1 = key2
comparator(key1, key2) < 0 //key1 < key2
```

#### 关于BufferPoolManager类的使用与注意事项：

BufferPoolManager类用于对缓冲区进行操作，比如通过page_id获得对应页，Pin操作防止该页被移出缓冲区，new创建页，delete删除页。

```
//页的获取，释放，创建，删除操作
Page *page = buffer_pool_manager->FetchPage(page_id);
B_PLUS_TREE_INTERNAL_PAGE *bPage = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(page->GetData());
B_PLUS_TREE_LEAF_PAGE_TYPE *bPage = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page->GetData());
//true表明当前页为脏页，需要写入磁盘，false则直接解锁
buffer_pool_manager->UnpinPage(page_id，true);
//创建页，且Pin该页
page_id_t pageId;
Page *rootPage = buffer_pool_manager_->NewPage(&pageId);
//删除页，删除前请保证页以Unpin解锁
buffer_pool_manager_->DeletePage(page_id);
```

```
#pragma once

#include <queue>

#include "storage/page/b_plus_tree_page.h"

namespace bustub {

#define B_PLUS_TREE_INTERNAL_PAGE_TYPE BPlusTreeInternalPage<KeyType, ValueType, KeyComparator>
#define B_PLUS_TREE_INTERNAL_PAGE BPlusTreeInternalPage<KeyType, page_id_t, KeyComparator>
#define INTERNAL_PAGE_HEADER_SIZE 24
//缺省时内部结点的Max_size
#define INTERNAL_PAGE_SIZE ((PAGE_SIZE - INTERNAL_PAGE_HEADER_SIZE) / (sizeof(MappingType))) - 1

INDEX_TEMPLATE_ARGUMENTS
class BPlusTreeInternalPage : public BPlusTreePage {
 public:
  void Init(page_id_t page_id, page_id_t parent_id = INVALID_PAGE_ID, int max_size = INTERNAL_PAGE_SIZE);

  KeyType KeyAt(int index) const;
  void SetKeyAt(int index, const KeyType &key);
  int ValueIndex(const ValueType &value) const;
  ValueType ValueAt(int index) const;

  ValueType Lookup(const KeyType &key, const KeyComparator &comparator) const;
  void PopulateNewRoot(const ValueType &old_value, const KeyType &new_key, const ValueType &new_value);
  int InsertNodeAfter(const ValueType &old_value, const KeyType &new_key, const ValueType &new_value);
  void Remove(int index);
  ValueType RemoveAndReturnOnlyChild();

  void MoveAllTo(BPlusTreeInternalPage *recipient,BufferPoolManager *buffer_pool_manager);
  void MoveHalfTo(BPlusTreeInternalPage *recipient, BufferPoolManager *buffer_pool_manager);
  void MoveFirstToEndOf(BPlusTreeInternalPage *recipient,
                        BufferPoolManager *buffer_pool_manager);
  void MoveLastToFrontOf(BPlusTreeInternalPage *recipient, 
                         BufferPoolManager *buffer_pool_manager);

 private:
  void CopyNFrom(MappingType *items, int size, BufferPoolManager *buffer_pool_manager);
  void CopyLastFrom(const MappingType &pair, BufferPoolManager *buffer_pool_manager);
  void CopyFirstFrom(const MappingType &pair, BufferPoolManager *buffer_pool_manager);
  MappingType array_[0];
};
}
```

## 3.BPlusTreeLeafPage的设计

### 任务描述

本关任务：作为B+树索引结点类型的数据结构设计的第三部分：实现BPlusTreeLeafPage类，该类作为B+树的叶子结点类型，提供B+树叶结点的功能。

### 相关知识

为了完成本关任务，你需要了解：B+树叶结点结构与功能

#### BPlusTreeLeafPage 结构简述

叶子页存储有序的m个键条目(key)和m个值条目(value)。 在实现中，值通常只能是用于定位实际元组存储位置的64位record_id。 叶子页与内部页在键/值对的数量上具有相同的限制，并且应该遵循相同的合并，重新分配和拆分操作。叶结点成员将在BPlusTreePage的基础上额外增加一个数组，用于存储记录信息以及next_page_id_存储相邻叶结点的索引。 一个Max_size为n的叶结点，可以存储n条记录，即该数组有如下结构：

| KEY(0)+RecordID_ID(0) | KEY(1)+Record_ID(1) | ...  | KEY(n)+RecordID_ID(n) |
| --------------------- | ------------------- | ---- | --------------------- |
|                       |                     |      |                       |

键在数组中维持有序排列。 参看BPlusTreeLeafPage的数据结构，注意 next_page_id_的位置

### 相关变量声明

```
//BPlusTreeLeafPage中的记录数组MappingType array_[0];//索引键值对，叶子结点中为<Key,RID>，RID存储记录信息MappingType std::pair<KeyType, ValueType>//缓冲区对象，负责特定页的获取BufferPoolManager *buffer_pool_manager//比较器，负责键的比较KeyComparator &comparator
```

### 关卡内容

请在b_plus_tree_leaf_page.cpp文件中实现下列函数：

```
  void Init(page_id_t page_id, page_id_t parent_id = INVALID_PAGE_ID, int max_size = LEAF_PAGE_SIZE);  page_id_t GetNextPageId() const;  void SetNextPageId(page_id_t next_page_id);  KeyType KeyAt(int index) const;  int KeyIndex(const KeyType &key, const KeyComparator &comparator) const;  const MappingType &GetItem(int index);  int Insert(const KeyType &key, const ValueType &value, const KeyComparator &comparator);  bool Lookup(const KeyType &key, ValueType *value, const KeyComparator &comparator) const;  int RemoveAndDeleteRecord(const KeyType &key, const KeyComparator &comparator);  void MoveHalfTo(BPlusTreeLeafPage *recipient, __attribute__((unused)) BufferPoolManager *buffer_pool_manager);  void MoveAllTo(BPlusTreeLeafPage *recipient, BufferPoolManager *buffer_pool_manager);  void MoveFirstToEndOf(BPlusTreeLeafPage *recipient, BufferPoolManager *buffer_pool_manager);  void MoveLastToFrontOf(BPlusTreeLeafPage *recipient, BufferPoolManager *buffer_pool_manager);  void CopyNFrom(MappingType *items, int size);  void CopyLastFrom(const MappingType &item);  void CopyFirstFrom(const MappingType &item,BufferPoolManager *buffer_pool_manager);
```

函数功能详细介绍请参照文件内函数注释

### 帮助与提醒

#### 关于KeyComparator类的使用：

KeyComparator类用于进行Key值的比较，使用方法如下：

```
KeyType key1,key2;comparator(key1, key2) > 0 //key1 > key2comparator(key1, key2) = 0 //key1 = key2comparator(key1, key2) < 0 //key1 < key2
```

#### 关于BufferPoolManager类的使用与注意事项：

BufferPoolManager类用于对缓冲区进行操作，比如通过page_id获得对应页，Pin操作防止该页被移出缓冲区，new创建页，delete删除页。

```
//页的获取，释放，创建，删除操作Page *page = buffer_pool_manager->FetchPage(page_id);B_PLUS_TREE_INTERNAL_PAGE *bPage = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(page->GetData());orB_PLUS_TREE_LEAF_PAGE_TYPE *bPage = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page->GetData());............//true表明当前页为脏页，需要写入磁盘，false则直接解锁buffer_pool_manager->UnpinPage(page_id，true);//创建页，且Pin该页page_id_t pageId;Page *rootPage = buffer_pool_manager_->NewPage(&pageId);//删除页，删除前请保证页以Unpin解锁buffer_pool_manager_->DeletePage(page_id);
```

```
#pragma once

#include <utility>
#include <vector>

#include "storage/page/b_plus_tree_page.h"

namespace bustub {

#define B_PLUS_TREE_LEAF_PAGE_TYPE BPlusTreeLeafPage<KeyType, ValueType, KeyComparator>
#define LEAF_PAGE_HEADER_SIZE 28
#define LEAF_PAGE_SIZE ((PAGE_SIZE - LEAF_PAGE_HEADER_SIZE) / (sizeof(MappingType))) - 1

INDEX_TEMPLATE_ARGUMENTS
class BPlusTreeLeafPage : public BPlusTreePage {
 public:

  void Init(page_id_t page_id, page_id_t parent_id = INVALID_PAGE_ID, int max_size = LEAF_PAGE_SIZE);
  page_id_t GetNextPageId() const;
  void SetNextPageId(page_id_t next_page_id);
  KeyType KeyAt(int index) const;
  int KeyIndex(const KeyType &key, const KeyComparator &comparator) const;
  const MappingType &GetItem(int index);

  int Insert(const KeyType &key, const ValueType &value, const KeyComparator &comparator);
  bool Lookup(const KeyType &key, ValueType *value, const KeyComparator &comparator) const;
  int RemoveAndDeleteRecord(const KeyType &key, const KeyComparator &comparator);

  void MoveHalfTo(BPlusTreeLeafPage *recipient, __attribute__((unused)) BufferPoolManager *buffer_pool_manager);
  void MoveAllTo(BPlusTreeLeafPage *recipient, BufferPoolManager *buffer_pool_manager);
  void MoveFirstToEndOf(BPlusTreeLeafPage *recipient, BufferPoolManager *buffer_pool_manager);
  void MoveLastToFrontOf(BPlusTreeLeafPage *recipient, BufferPoolManager *buffer_pool_manager);
 private:
  void CopyNFrom(MappingType *items, int size);
  void CopyLastFrom(const MappingType &item);
  void CopyFirstFrom(const MappingType &item,BufferPoolManager *buffer_pool_manager);
  //B+树叶结点依序访问，最后一个叶结点的next_page_id_是INVALID_PAGE_ID
  page_id_t next_page_id_;
  MappingType array_[0];
};
}

```

```
#include <sstream>

#include "common/exception.h"
#include "common/rid.h"
#include "storage/page/b_plus_tree_leaf_page.h"
#include "storage/page/b_plus_tree_internal_page.h"

namespace bustub {

/**
 * 函数功能：
 *  初始化this页，包括page type,size,page id,parent id and max page size
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::Init(page_id_t page_id, page_id_t parent_id, int max_size) {


}

/**
 * 函数功能：
 *  获取相邻叶子节点的page_id
 * 建议：
 *  next_page_id_属性
 */
INDEX_TEMPLATE_ARGUMENTS
page_id_t B_PLUS_TREE_LEAF_PAGE_TYPE::GetNextPageId() const {         }
/**
 * 函数功能：
 *  设置相邻叶子节点的page_id
 * 建议：
 *  next_page_id_属性
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::SetNextPageId(page_id_t next_page_id) { 


 }

/**
 * 函数功能：
 *  在key值有序排列的数组中，找到特定key值对应的index
 * 建议：
 *  1.如果当前节点尚不存在key值(size==0)，则可以返回首结点
 *  2.如果key值不存在，返回应插入的index的位置
 */
INDEX_TEMPLATE_ARGUMENTS
int B_PLUS_TREE_LEAF_PAGE_TYPE::KeyIndex(const KeyType &key, const KeyComparator &comparator) const {
  //如果当前节点尚不存在key值，则可以直接插入到第一个结点
	if (GetSize() == 0) return 0;
  
  
  
  
  
}

/**
 * 函数功能：
 *  返回index处的key值
 * 建议：
 *  1.数组中元素为pair，first为key，second为RID
 */
INDEX_TEMPLATE_ARGUMENTS
KeyType B_PLUS_TREE_LEAF_PAGE_TYPE::KeyAt(int index) const {
  // replace with your own code
  return array_[index].first;
}


/**
 * 函数功能：
 *  返回index处的元素
 * 建议：
 *  1.数组中元素为pair，first为key，second为RID
 */
INDEX_TEMPLATE_ARGUMENTS
const MappingType &B_PLUS_TREE_LEAF_PAGE_TYPE::GetItem(int index) {
  // replace with your own code
  return array_[index];
}

/*****************************************************************************
 *插入
 *****************************************************************************/
/**
 * 函数功能：
 *  在保证有序地情况下插入新的键值对
 * 建议：
 *  1.元素溢出的情况无需处理，后续可以在外部处理
 *  2.当size为0时插入到数组头部
 *  3.更新size并返回当前size大小
 */
INDEX_TEMPLATE_ARGUMENTS
int B_PLUS_TREE_LEAF_PAGE_TYPE::Insert(const KeyType &key, const ValueType &value, const KeyComparator &comparator) {








}

/*****************************************************************************
 * 分裂
 *****************************************************************************/
/**
 *函数功能：
 * 移动this结点中一半（向上取整）的元素到一个新生成的recipient结点中
 *建议：
 *  1.优先实现CopyNFrom函数
 *  2.在内部调用CopyNFrom函数实现该功能
 *  3.更新this结点和recipient结点的NextPageId属性，注意recipient结点显然是this结点后继结点
 *  eg:
 *      this == r1,  recipient == r2
 *      r1->[<0, r0>, <1, r1>, <2, r2>, <3, r3>, <4, r4>] ----MoveHalfTo--> r2[]
 *      result: r1->[<0, r0>, <1, r1>] ---> r2[<2, r2>, <3, r3>, <4, r4>]
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::MoveHalfTo(BPlusTreeLeafPage *recipient,
                                            __attribute__((unused)) BufferPoolManager *buffer_pool_manager) {







}

/**
 * 函数功能：从item处开始，截取size个键值对并入到结点的尾部
 * 建议：
 *  1.更新size大小
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::CopyNFrom(MappingType *items, int size) {





}

/*****************************************************************************
 * 查找
 *****************************************************************************/
/**
 * 函数功能：
 *  在key值有序排列的数组中，找到特定key值对应的value
 * 建议：
 *  1.可以调用KeyIndex()函数
 *  2.如果key值存在，存储key对应的value值，返回true
 *  3.如果key值不存在，直接返回false
 *  4.使用comparator进行key值的比较
 */
INDEX_TEMPLATE_ARGUMENTS
bool B_PLUS_TREE_LEAF_PAGE_TYPE::Lookup(const KeyType &key, ValueType *value, const KeyComparator &comparator) const {




}

/*****************************************************************************
 * 移除
 *****************************************************************************/
/**
 * 函数功能：
 *  1.移除this结点中的index元素
 * 建议：
 *  1.当key不存在时，直接返回当前size
 *  1.注意元素的移动
 *  2.更新并返回size
 */
INDEX_TEMPLATE_ARGUMENTS
int B_PLUS_TREE_LEAF_PAGE_TYPE::RemoveAndDeleteRecord(const KeyType &key, const KeyComparator &comparator) {





}

/*****************************************************************************
 * 合并
 *****************************************************************************/
/**
 * 函数功能：
 *  合并this结点的元素至recipient结点中，即将this结点中的全部元素移至recipient结点的尾部
 * 建议：
 *  1.this结点显然是recipient结点后继叶结点，因此需要更新recipient结点的NextPageId为this
 *     结点的nextPageId。
 *  2.更新size大小
 *  3.this结点内容全部移动至sibling recipient结点，而this结点的父节点内容需要删除，但不用
 *    在本函数中实现。
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::MoveAllTo(BPlusTreeLeafPage *recipient, BufferPoolManager *buffer_pool_manager) { 





}

/*****************************************************************************
 * 重分配
 *****************************************************************************/
/**
 * 函数功能：
 *  移动this结点的首元素至recipient结点的末尾
 * 建议：
 *  1.recipient调用CopyLastFrom函数实现节点更新
 *  2.this结点更新size
 *  3.由于this结点首元素发生变化，因此父结点中this结点的索引key值需要更新
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::MoveFirstToEndOf(BPlusTreeLeafPage *recipient,
                                                  BufferPoolManager *buffer_pool_manager) {








}

/**
 * 函数功能：
 *  将pair元素添加到this结点的尾部
 * 建议：
 *  1.更新size
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::CopyLastFrom(const MappingType &item) {



}

/**
 * 函数功能：
 *  移动this结点的尾部元素至recipient结点的头部
 * 建议：
 *  1.recipient调用CopyFirstFrom函数实现节点更新
 *  2.this结点更新size
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::MoveLastToFrontOf(BPlusTreeLeafPage *recipient,
                                                   BufferPoolManager *buffer_pool_manager) {



}

/**
 * 函数功能：
 *  移动pair元素至recipient结点的首部
 * 建议：
 *  1.由于结点首元素发生变化，父结点中this结点的索引key值需要更新
 *  2.更新size
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::CopyFirstFrom(const MappingType &item,
                                                BufferPoolManager *buffer_pool_manager) {



}

template class BPlusTreeLeafPage<GenericKey<4>, RID, GenericComparator<4>>;
template class BPlusTreeLeafPage<GenericKey<8>, RID, GenericComparator<8>>;
template class BPlusTreeLeafPage<GenericKey<16>, RID, GenericComparator<16>>;
template class BPlusTreeLeafPage<GenericKey<32>, RID, GenericComparator<32>>;
template class BPlusTreeLeafPage<GenericKey<64>, RID, GenericComparator<64>>;
}  // namespace bustub

```

## 4.B+树索引：Insert

### 任务描述

本关任务： 1.在完成B+树相关数据结构的设计后，请完成B+树索引的插入功能。 2.实现B+树迭代器。

### 相关知识

为了完成本关任务，你需要了解： 1.B+树的基本特性，对记录插入时B+树结构的变化过程和细节有所了解。 2.B+树迭代器的基本功能。

#### BPlusTree简述

出于难度考虑，目前B+树索引仅存在Unique Key，即索引中存储的key值不重复。 一颗完整的B+树由内部结点和叶结点组成，随着记录的插入，结点不断分裂增加，但仍需保持B+树的完整性和一致性。

#### IndexIterator简述

作为BPlusTree的迭代器，需要实现对B+树存储记录的有序遍历，即自增，末尾判断等功能。

#### 任务和测试说明

  在完成B+树相关数据结构的设计后，可以开始B+树类的整体功能实现，这一关卡，需要完成B+树索引的查找以及插入功能，并实现B+树记录迭代器。  BPlusTree即B+树类，一颗完整的B+树从最初的空树，随着记录的插入，叶子节点不断分裂增加并产生用于索引的内部节点，逐渐生成一个完整的B+树，但在整个过程中需保持B+树的完整性和一致性。  在本关卡中，B+树仅对外暴露Insert以及GetValue接口，即向B+树中插入记录和定位记录。当有记录插入时，从根节点进入B+树，定位叶子节点并插入该记录。插入后判断内部记录是否超过最大值，如果超过，对叶子节点进行分裂，内部记录对半分离，产生新叶子节点，插入到叶子节点链表中。同时，在父节点中插入新叶子节点索引，即进行递归插入，直至不再有分裂。在充分理解B+树的插入过程后，根据流程自上而下定义多个私有函数承载不同的子功能，并将待实现函数的功能以及整个流程中的函数调用关系和条件做明确注释说明，引导学生思考并完成局部功能，最后整合为插入功能。  在插入功能完成后，已经可以实现B+树的生长。因此，对B+树存储信息的查找和迭代也是不可缺少的，查找功能即B+树的记录的定位，从根节点进入，通过内部节点的索引信息不断向下遍历，直至对应的叶子节点，即可查找特定的记录信息。同时，结合查找功能，B+树需要生成自身记录的迭代器，迭代器由当前叶子节点指针和元素下表组成，通过实现对++运算符的重载，完成迭代器在叶子节点链表中的遍历，并实现末尾判定函数以结束遍历。  针对上述功能，设计测试流程以判断BPlusTree的插入功能是否达到预期结果。在该关卡中，BPlusTree可以作为一个功能完备的类，可以独立进行测试，为了复现插入功能中可能出现的各种情况，并全面覆盖评测功能函数中不同条件下应有的逻辑处理路径，需要设置针对性的测试数据和测试流程，以观察对象实例的变化过程是否符合预期。  测试流程分为三个阶段，代表了B+树生长过程中的三个阶段，三个阶段均验证插入功能和查找功能，同时穿插B+树迭代器遍历数据进行数据完整性验证。 B+树由无到有，深度为1。B+树初始化，指定缓冲区管理器以及当前阶数，从而方便后续进行树结构正确性验证，进入第一阶段，此时B+树为空，在插入数据后观察根节点是否如期生成，数据是否完整，同时迭代器可否正常工作。   B+树第一次分裂，根节点更新，深度由1到2。插入数据使B+树进入分裂状态节点，生成2层B+树，由于阶数与插入数据均确定，此时B+树的内部结构和数据应符合预期要求。在这里实现B+树的打印功能以辅助评测流程的进行，将此时的树打印出来，与预期结果对比进行验证。  B+树开始不断插入数据，以大量数据覆盖插入过程中功能函数的所有路径，验证插入功能的健壮性。在这个阶段，不仅需要校验功能的完整性、数据的准确性，还会对内存管理进行验证，由于大量数据的插入，必然会出现缓冲区满和页面替换的情况，如果没有处理好页的获取与释放，就会导致缓冲区内存溢出，程序出错，因此也需要注意对缓冲区处理的评测。

### 部分变量声明

```
//内部结点,叶结点,迭代器定义时可直接使用以下类型声明#define B_PLUS_TREE_LEAF_PAGE_TYPE BPlusTreeLeafPage<KeyType, ValueType, KeyComparator>#define B_PLUS_TREE_INTERNAL_PAGE BPlusTreeInternalPage<KeyType, page_id_t, KeyComparator>#define INDEXITERATOR_TYPE IndexIterator<KeyType, ValueType, KeyComparator>//头页，用于存储metadata，比如记录索引根结点，表信息等等HeaderPage *header_page//缓冲区对象，负责特定页的获取BufferPoolManager *buffer_pool_manager
```

### 关卡内容

请在b_plus_tree.cpp文件中实现下列函数：

```
bool IsEmpty() const;bool Insert(const KeyType &key, const ValueType &value);bool GetValue(const KeyType &key, std::vector<ValueType> *result);Page *FindLeafPage(const KeyType &key, bool leftMost = false);void StartNewTree(const KeyType &key, const ValueType &value);bool InsertIntoLeaf(const KeyType &key, const ValueType &value);void InsertIntoParent(BPlusTreePage *old_node, const KeyType &key, BPlusTreePage *new_node);template <typename N>  N *Split(N *node);void UpdateRootPageId(int insert_record = 0);//index_iteratorINDEXITERATOR_TYPE Begin();INDEXITERATOR_TYPE Begin(const KeyType &key);INDEXITERATOR_TYPE End();
```

函数功能详细介绍请参照文件内函数注释

请在index_iterator.cpp文件中实现下列函数：

```
bool IsEnd();const MappingType &operator*();IndexIterator &operator++();
```

函数功能详细介绍请参照文件内函数注释

### 帮助与提醒

#### 关于BufferPoolManager类的使用与注意事项：

BufferPoolManager类用于对缓冲区进行操作，比如通过page_id获得对应页，Pin操作防止该页被移出缓冲区，new创建页，delete删除页。

```
//页的获取，释放，创建，删除操作Page *page = buffer_pool_manager->FetchPage(page_id);B_PLUS_TREE_INTERNAL_PAGE *bPage = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(page->GetData());orB_PLUS_TREE_LEAF_PAGE_TYPE *bPage = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page->GetData());............//true表明当前页为脏页，需要写入磁盘，false则直接解锁buffer_pool_manager->UnpinPage(page_id，true);//创建页，且Pin该页page_id_t pageId;Page *rootPage = buffer_pool_manager_->NewPage(&pageId);//删除页，删除前请保证页以Unpin解锁buffer_pool_manager_->DeletePage(page_id);
```

## 5.B+树索引：Remove

### 任务描述

本关任务： 在成功实现B+树索引的插入功能后，请完成B+树索引的删除功能。

### 相关知识

为了完成本关任务，你需要了解： 1.B+树的基本特性，对记录删除时B+树结构的变化过程和细节有所了解。 一颗完整的B+树由内部结点和叶结点组成，随着记录的删除，结点不断合并减少，但仍需保持B+树的完整性和一致性。

### 任务和测试说明

  在成功实现B+树索引的插入功能后，请完成B+树索引的删除功能，这也是索引B+树的最后一个功能模块。  一颗完整的B+树由内部节点和叶子节点组成，随着记录的删除，节点不断合并减少，但仍需保持B+树的完整性和一致性。在本关卡中，B+树仅对外暴露Remove接口，即向B+树中删除特定记录。当删除特定记录时，首先从根节点进入B+树，通过内部节点的索引信息不断向下遍历，直至对应的叶子节点，之后删除该记录，删除后判断内部记录是否已小于最小值，是则开始进行树的调整。首先判断是否可以与相邻兄弟节点合并，如果可以合并兄弟节点，则合并后删除其在父节点中的索引，即递归进行元素删除操作，直至不再有合并发生；否则可以进行元素的调动，移动兄弟节点中一个元素补充到叶子节点中，并维持B+树的索引正确。在充分理解B+树的删除过程后，自上而下定义多个函数承载不同的子功能，并将待实现函数的功能以及整个流程中的函数调用关系和条件做明确注释说明，最后整合为删除功能，实现B+树的删减操作。  针对上述功能，设计测试流程以判断BPlusTree的删除功能是否达到预期结果。在该关卡中，删除的测试流程与插入的测试流程设计思路和整体结构相似，测试流程分为三个阶段，代表了B+树删减过程中的三个阶段，三个阶段均进行删除功能的验证，同时穿插B+树迭代器遍历数据进行数据完整性验证。 B+树当前仅包含根节点存储记录信息，深度为1。首先B+树初始化，指定缓冲区管理器以及当前阶数，并生成符合条件的B+树，从而方便后续进行删除操作，树结构正确性验证。进入第一阶段，在多次删除数据后观察根节点数据是否正常，并观察在删除全部数据后B+树是否置空。  B+树第一次合并，根节点更新，深度由2到1。生成符合条件的2层B+树，当前B+树叶子节点即将进入合并状态，并替换根节点，由于阶数与插入数据均确定，此时B+树的内部结构和数据应符合预期要求，将此时的树打印出来，与预期结果对比进行验证。  B+树包含大量记录，并开始不断删除记录，以大量数据覆盖删除过程中功能函数的所有路径，验证删除功能的健壮性。在这个阶段，不仅需要校验功能的完整性、数据的准确性，还会对内存管理进行验证，由于大量数据的删除，必然会出现缓冲区满和页面替换的情况，如果没有处理好页的获取与释放，就会导致缓冲区内存溢出，程序出错，因此也需要注意对缓冲区处理的评测。

### 相关变量声明

```
//内部结点,叶结点,迭代器定义时可直接使用以下类型声明#define B_PLUS_TREE_LEAF_PAGE_TYPE BPlusTreeLeafPage<KeyType, ValueType, KeyComparator>#define B_PLUS_TREE_INTERNAL_PAGE BPlusTreeInternalPage<KeyType, page_id_t, KeyComparator>#define INDEXITERATOR_TYPE IndexIterator<KeyType, ValueType, KeyComparator>//头页，用于存储metadata，比如记录索引根结点，表信息等等HeaderPage *header_page//缓冲区对象，负责特定页的获取BufferPoolManager *buffer_pool_manager
```

### 关卡内容

请在b_plus_tree_delete.cpp文件中实现下列函数：

```
bool IsEmpty() const;void Remove(const KeyType &key, Transaction *transaction = nullptr);template <typename N>bool CoalesceOrRedistribute(N *node, Transaction *transaction = nullptr);template <typename N>  bool FindSibling(N *node, N *&sibling);template <typename N>bool Coalesce(N **neighbor_node, N **node, BPlusTreeInternalPage<KeyType, page_id_t, KeyComparator> **parent,int index, Transaction *transaction = nullptr);template <typename N>  void Redistribute(N *neighbor_node, N *node, int index);bool AdjustRoot(BPlusTreePage *node);void UpdateRootPageId(int insert_record = 0);
```

函数功能详细介绍请参照文件内函数注释

### 帮助与提醒

#### 关于BufferPoolManager类的使用与注意事项：

BufferPoolManager类用于对缓冲区进行操作，比如通过page_id获得对应页，Pin操作防止该页被移出缓冲区，new创建页，delete删除页。

```
//页的获取，释放，创建，删除操作Page *page = buffer_pool_manager->FetchPage(page_id);B_PLUS_TREE_INTERNAL_PAGE *bPage = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(page->GetData());orB_PLUS_TREE_LEAF_PAGE_TYPE *bPage = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page->GetData());............//true表明当前页为脏页，需要写入磁盘，false则直接解锁buffer_pool_manager->UnpinPage(page_id，true);//创建页，且Pin该页page_id_t pageId;Page *rootPage = buffer_pool_manager_->NewPage(&pageId);//删除页，删除前请保证页以Unpin解锁buffer_pool_manager_->DeletePage(page_id);
```

```
/**
 * 该头文件修改无效，仅供阅读参考，不要修改
 */
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
 * B+树类声明
 * (1) key不重复，主键唯一
 * (2) 支持插入和删除功能(该关卡仅实现删除,仅展示删除所需函数)
 * (4) 请实现B+树index_iterator类，供B+树遍历使用
 */
INDEX_TEMPLATE_ARGUMENTS
class BPlusTree {

 public:
  explicit BPlusTree(std::string name, BufferPoolManager *buffer_pool_manager, const KeyComparator &comparator,
                     int leaf_max_size = LEAF_PAGE_SIZE, int internal_max_size = INTERNAL_PAGE_SIZE);

  bool IsEmpty() const;

  // Remove a key and its value from this B+ tree.
  void Remove(const KeyType &key, Transaction *transaction = nullptr);

 private:

  template <typename N>
  bool CoalesceOrRedistribute(N *node, Transaction *transaction = nullptr);

  template <typename N>
  bool FindSibling(N *node, N *&sibling);

  template <typename N>
  bool Coalesce(N **neighbor_node, N **node, BPlusTreeInternalPage<KeyType, page_id_t, KeyComparator> **parent,
                int index, Transaction *transaction = nullptr);

  template <typename N>
  void Redistribute(N *neighbor_node, N *node, int index);

  bool AdjustRoot(BPlusTreePage *node);

  void UpdateRootPageId(int insert_record = 0);

  std::string index_name_;
  page_id_t root_page_id_;
  BufferPoolManager *buffer_pool_manager_;
  KeyComparator comparator_;
  int leaf_max_size_;
  int internal_max_size_;
  std::mutex latch_;
};

}  // namespace bustub

```

```
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


/*****************************************************************************
 * 删除
 *****************************************************************************/
/*
 * 函数功能：
 *  在B+树中删除key对应的记录
 * 建议：
 *  1.若B+树为空直接返回
 *  2.通过上一个关卡实现的FindLeafPage(key)查找key值所在页并删除记录
 *  3.删除后需判断结点元素是否小于min_size,并调用CoalesceOrRedistribute()进行后续处理
 *  4.注意unpinPage，避免缓冲区内存泄露
 */
INDEX_TEMPLATE_ARGUMENTS
void BPLUSTREE_TYPE::Remove(const KeyType &key) {
  //并发索引，本实验暂不考虑
  std::lock_guard<std::mutex> lock(latch_);
  
  
  
  }

/*
 * 函数功能：
 *  对元素个数小于Min_size的结点进行处理
 *      @param N *node 表示内部结点或叶结点
 *      @return: 若有结点合并，返回true，否则返回false
 * 建议：
 *  1.当node为根结点时，需要调用AdjustRoot()进行调整
 *  2.首先要通过调用FindSibling()找到兄弟结点
 *  3.如果两个结点的元素可以合并，则调用Coalesce()进行合并
 *  4.如果元素过多，无法合并，则调用Redistribute()进行结点元素的调整
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
bool BPLUSTREE_TYPE::CoalesceOrRedistribute(N *node) {
  //如果可以合并：进行页的选择和合并
  //如果无法合并，则选择从其他页抽取一个结点，先找兄弟FindSibling
  if (node->IsRootPage()) {
		//该函数可能递归调用至根结点，故需要对根结点进行特殊处理
    return AdjustRoot(node);
  }
  //Hint:	//进行if判断，保证在父页删除的key为父页的非首结点
      //根据node的位置，如果node处于首结点，则此时需要把后继页sibling合并到node中
      //否则，把node合并到sibling（前驱页）中
  

}

/*
 * 函数功能：
 *  对元素个数小于Min_size的根结点进行更新
 *      @return: 若有结点被删除，返回true，否则返回false
 * 建议：
 *  1.根结点可能是叶结点，也可能是内部结点，分开处理
 *  2.当根结点中最后一个元素被删除，此时B+树为空，调用UpdateRootPageId()更新根结点page_id
 *  3.当根结点中仅剩余一个元素，替换更新B+树的根结点
 *  4.注意unpinPage和deletePage
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

/*
 * 函数功能：
 *  寻找node结点的兄弟结点sibling
 *      @return: 若兄弟结点为右结点，则返回true，左结点则为false
 * 建议：
 *  1.兄弟结点最好是索引在同一父节点内的结点
 *  2.注意unpinPage，避免缓冲区内存泄露
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
bool BPLUSTREE_TYPE::FindSibling(N *node, N *&sibling) {
  //如果是node是父页的首结点，则从后继页抽一个，如果不是，则从前驱页抽一个。这样可以保证影响范围都是在同一个父页内，操作简单


}
/*
 * 函数功能：
 *  将node中的元素全部合并到neighbor_node中
 *      @param   neighbor_node      幸存结点
 *      @param   node               待合并结点
 *      @param   parent             二者的父结点
 *      @param   index              待合并结点在父结点中的索引
 *      @return: 若有结点被删除，返回true，否则返回false
 * 建议：
 *  1.node合并后需对父结点进行相关调整
 *  2.父结点元素被删除后，若小于Min_size则调用CoalesceOrRedistribute处理
 *  3.注意unpinPage和deletePage
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
bool BPLUSTREE_TYPE::Coalesce(N **neighbor_node, N **node,
                              BPlusTreeInternalPage<KeyType, page_id_t, KeyComparator> **parent, int index) {
  assert((*node)->GetSize() + (*neighbor_node)->GetSize() <= (*node)->GetMaxSize());
  //注意：当内部页中size过小时或者仅剩余一个有效结点时，递归触发CoalesceOrRedistribute函数，对当前结点进行处理
  }

/*
 * 函数功能：
 *  将node中的元素移动到neighbor_node中
 * 建议：
 *  1.若index为0，将neighbor_node首元素移动到node尾部
 *  否则将neighbor_node的尾元素移动到node首部
 *  2.注意unpinPage，避免缓冲区内存泄露
 */
INDEX_TEMPLATE_ARGUMENTS
template <typename N>
void BPLUSTREE_TYPE::Redistribute(N *neighbor_node, N *node, int index) {
  
  
  }

/*
 * 函数功能：
 *  当B+树根结点发生变化时，调用该函数在header_page中对根结点ID进行更新
 *      @param insert_record 缺省时insert_record为0
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

template class BPlusTree<GenericKey<4>, RID, GenericComparator<4>>;
template class BPlusTree<GenericKey<8>, RID, GenericComparator<8>>;
template class BPlusTree<GenericKey<16>, RID, GenericComparator<16>>;
template class BPlusTree<GenericKey<32>, RID, GenericComparator<32>>;
template class BPlusTree<GenericKey<64>, RID, GenericComparator<64>>;

}  // namespace bustub

```

