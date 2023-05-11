//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/page/b_plus_tree_leaf_page.cpp
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include <sstream>

#include "common/exception.h"
#include "common/rid.h"
#include "storage/page/b_plus_tree_leaf_page.h"
#include "storage/page/b_plus_tree_internal_page.h"

namespace bustub {

/**
 * �������ܣ�
 *  ��ʼ��thisҳ������page type,size,page id,parent id and max page size
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::Init(page_id_t page_id, page_id_t parent_id, int max_size) {
  SetPageType(IndexPageType::LEAF_PAGE);
  SetSize(0);
  SetPageId(page_id);
  SetParentPageId(parent_id);
  SetMaxSize(max_size);
  SetNextPageId(INVALID_PAGE_ID);
}

/**
 * �������ܣ�
 *  ��ȡ����Ҷ�ӽڵ��page_id
 * ���飺
 *  next_page_id_����
 */
INDEX_TEMPLATE_ARGUMENTS
page_id_t B_PLUS_TREE_LEAF_PAGE_TYPE::GetNextPageId() const { return next_page_id_; }
/**
 * �������ܣ�
 *  ��������Ҷ�ӽڵ��page_id
 * ���飺
 *  next_page_id_����
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::SetNextPageId(page_id_t next_page_id) { next_page_id_ = next_page_id; }

/**
 * �������ܣ�
 *  ��keyֵ�������е������У��ҵ��ض�keyֵ��Ӧ��index
 * ���飺
 *  1.�����ǰ�ڵ��в�����keyֵ(size==0)������Է����׽��
 *  2.���keyֵ�����ڣ�����Ӧ�����index��λ��
 * NOTE: This method is only used when generating index iterator
 */
INDEX_TEMPLATE_ARGUMENTS
int B_PLUS_TREE_LEAF_PAGE_TYPE::KeyIndex(const KeyType &key, const KeyComparator &comparator) const {
  //�����ǰ�ڵ��в�����keyֵ�������ֱ�Ӳ��뵽��һ�����
	if (GetSize() == 0) return 0;
  int low = 0;
  int high = GetSize() - 1;
  int mid;
  while(low <= high) {
    mid = (low + high) / 2;
    if (comparator(array_[mid].first, key) < 0)
      low = mid + 1;
    else if (comparator(array_[mid].first, key) > 0)
      high = mid - 1;
    else
      return mid;
  }
  return low;
}

/**
 * �������ܣ�
 *  ����index����keyֵ
 * ���飺
 *  1.������Ԫ��Ϊpair��firstΪkey��secondΪRID
 */
INDEX_TEMPLATE_ARGUMENTS
KeyType B_PLUS_TREE_LEAF_PAGE_TYPE::KeyAt(int index) const {
  // replace with your own code
  return array_[index].first;
}

/**
 * �������ܣ�
 *  ����index����Ԫ��
 * ���飺
 *  1.������Ԫ��Ϊpair��firstΪkey��secondΪRID
 */
INDEX_TEMPLATE_ARGUMENTS
const MappingType &B_PLUS_TREE_LEAF_PAGE_TYPE::GetItem(int index) {
  // replace with your own code
  return array_[index];
}

/*****************************************************************************
 *����
 *****************************************************************************/
/**
 * �������ܣ�
 *  �ڱ�֤���������²����µļ�ֵ��
 * ���飺
 *  1.Ԫ�������������账�������������ⲿ����
 *  2.��sizeΪ0ʱ���뵽����ͷ��
 *  3.����size�����ص�ǰsize��С
 */
INDEX_TEMPLATE_ARGUMENTS
int B_PLUS_TREE_LEAF_PAGE_TYPE::Insert(const KeyType &key, const ValueType &value, const KeyComparator &comparator) {
  int index = KeyIndex(key, comparator);
  IncreaseSize(1);
  int curSize = GetSize();
  for (int i = curSize - 1; i > index; i--) {
    array_[i].first = array_[i - 1].first;
    array_[i].second = array_[i - 1].second;
  }
  array_[index].first = key;
  array_[index].second = value;
  return curSize;
}

/*****************************************************************************
 * ����
 *****************************************************************************/
/**
 *�������ܣ�
 * �ƶ�this�����һ�루����ȡ������Ԫ�ص�һ�������ɵ�recipient�����
 *���飺
 *  1.����ʵ��CopyNFrom����
 *  2.���ڲ�����CopyNFrom����ʵ�ָù���
 *  3.����this����recipient����NextPageId����
 *  eg:
 *      this == r1,  recipient == r2
 *      r1->[<0, r0>, <1, r1>, <2, r2>, <3, r3>, <4, r4>] ----MoveHalfTo--> r2[]
 *      result: r1->[<0, r0>, <1, r1>] ---> r2[<2, r2>, <3, r3>, <4, r4>]
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::MoveHalfTo(BPlusTreeLeafPage *recipient,
                                            __attribute__((unused)) BufferPoolManager *buffer_pool_manager) {
  int size = GetSize();
  int remain_size = size / 2;
  recipient->CopyNFrom(array_ + remain_size, size - remain_size);
  SetSize(remain_size);
  recipient->SetNextPageId(GetNextPageId());
  SetNextPageId(recipient->GetPageId());
  // set size, is odd, bigger is last part
  return;
}

/**
 * �������ܣ���item����ʼ����ȡsize����ֵ�Բ��뵽����β��
 * ���飺
 *  1.����size��С
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::CopyNFrom(MappingType *items, int size) {
  int size_ = GetSize();
  for (int i = size_; i < size_ + size; i++) {
    array_[i] = *items++;
    IncreaseSize(1);
  }
}

/*****************************************************************************
 * LOOKUP
 *****************************************************************************/
/**
 * �������ܣ�
 *  ��keyֵ�������е������У��ҵ��ض�keyֵ��Ӧ��value
 * ���飺
 *  1.���Ե���KeyIndex()����
 *  2.���keyֵ���ڣ��洢key��Ӧ��valueֵ������true
 *  3.���keyֵ�����ڣ�ֱ�ӷ���false
 *  4.ʹ��comparator����keyֵ�ıȽ�
 */
INDEX_TEMPLATE_ARGUMENTS
bool B_PLUS_TREE_LEAF_PAGE_TYPE::Lookup(const KeyType &key, ValueType *value, const KeyComparator &comparator) const {
  int idx = KeyIndex(key, comparator);
  if (idx < GetSize() && comparator(array_[idx].first, key) == 0) {
    *value = array_[idx].second;
    return true;
  }
  return false;
}

/*****************************************************************************
 * �Ƴ�
 *****************************************************************************/
/**
 * �������ܣ�
 *  1.�Ƴ�this����е�indexԪ��
 * ���飺
 *  1.��key������ʱ��ֱ�ӷ��ص�ǰsize
 *  1.ע��Ԫ�ص��ƶ�
 *  2.���²�����size
 */
INDEX_TEMPLATE_ARGUMENTS
int B_PLUS_TREE_LEAF_PAGE_TYPE::RemoveAndDeleteRecord(const KeyType &key, const KeyComparator &comparator) {
  int index = KeyIndex(key, comparator);
  if (index >= GetSize() || comparator(key, KeyAt(index)) != 0) {
    return GetSize();
  }
  for (int i = index; i < GetSize() - 1; i++) {
    array_[i] = array_[i + 1];
  }
  IncreaseSize(-1);
  return GetSize();
}

/*****************************************************************************
 * �ϲ�
 *****************************************************************************/
/**
 * �������ܣ�
 *  �ϲ�this����Ԫ����recipient����У�����this����е�ȫ��Ԫ������recipient����β��
 * ���飺
 *  1.����recipient����NextPageId
 *  2.����size��С
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::MoveAllTo(BPlusTreeLeafPage *recipient, BufferPoolManager *buffer_pool_manager) { 
	int startIdx = recipient->GetSize(); 
  for (int i = 0; i < GetSize(); i++) {
    recipient->array_[startIdx + i].first = array_[i].first;
    recipient->array_[startIdx + i].second = array_[i].second;
  }
  recipient->SetNextPageId(GetNextPageId());
  recipient->IncreaseSize(GetSize());
  SetSize(0);
}

/*****************************************************************************
 * �ط���
 *****************************************************************************/
/**
 * �������ܣ�
 *  �ƶ�this������Ԫ����recipient����ĩβ
 * ���飺
 *  1.recipient����CopyLastFrom����ʵ�ֽڵ����
 *  2.this������size
 *  3.����this�����Ԫ�ط����仯����˸������this��������keyֵ��Ҫ����
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::MoveFirstToEndOf(BPlusTreeLeafPage *recipient,
                                                  BufferPoolManager *buffer_pool_manager) {

  MappingType pair = GetItem(0);
  memmove(array_, array_ + 1, static_cast<size_t> (sizeof(MappingType) * (GetSize() - 1)));
  IncreaseSize(-1);
  recipient->CopyLastFrom(pair);
  Page *page = buffer_pool_manager->FetchPage(GetParentPageId());
  B_PLUS_TREE_INTERNAL_PAGE *parent = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(page->GetData());
  parent->SetKeyAt(parent->ValueIndex(GetPageId()), array_[0].first);
  buffer_pool_manager->UnpinPage(GetParentPageId(), true);
}

/**
 * �������ܣ�
 *  ��pairԪ����ӵ�this����β��
 * ���飺
 *  1.����size
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::CopyLastFrom(const MappingType &item) {
  array_[GetSize()] = item;
  IncreaseSize(1);
}

/**
 * �������ܣ�
 *  �ƶ�this����β��Ԫ����recipient����ͷ��
 * ���飺
 *  1.recipient����CopyFirstFrom����ʵ�ֽڵ����
 *  2.this������size
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::MoveLastToFrontOf(BPlusTreeLeafPage *recipient,
                                                   BufferPoolManager *buffer_pool_manager) {
  MappingType pair = GetItem(GetSize() - 1);
  IncreaseSize(-1);
  recipient->CopyFirstFrom(pair,buffer_pool_manager);
}

/**
 * �������ܣ�
 *  �ƶ�pairԪ����recipient�����ײ�
 * ���飺
 *  1.���ڽ����Ԫ�ط����仯���������this��������keyֵ��Ҫ����
 *  2.����size
 */
INDEX_TEMPLATE_ARGUMENTS
void B_PLUS_TREE_LEAF_PAGE_TYPE::CopyFirstFrom(const MappingType &item,
                                                BufferPoolManager *buffer_pool_manager) {
  memmove(array_ + 1, array_, GetSize() * sizeof(MappingType));
  IncreaseSize(1);
  array_[0] = item;

  Page *page = buffer_pool_manager->FetchPage(GetParentPageId());
  B_PLUS_TREE_INTERNAL_PAGE *parent = reinterpret_cast<B_PLUS_TREE_INTERNAL_PAGE *>(page->GetData());
  parent->SetKeyAt(parent->ValueIndex(GetPageId()), array_[0].first);
  buffer_pool_manager->UnpinPage(GetParentPageId(), true);
}
INDEX_TEMPLATE_ARGUMENTS
std::string B_PLUS_TREE_LEAF_PAGE_TYPE::ToString(bool verbose) const {
  if (GetSize() == 0) {
    return "";
  }
  std::ostringstream stream;
  if (verbose) {
    stream << "[pageId: " << GetPageId() << " parentId: " << GetParentPageId() << "]<" << GetSize() << "> ";
  }
  int entry = 0;
  int end = GetSize();
  bool first = true;

  while (entry < end) {
    if (first) {
      first = false;
    } else {
      stream << " ";
    }
    stream << std::dec << array_[entry].first;
    if (verbose) {
      stream << "(" << array_[entry].second << ")";
    }
    ++entry;
  }
  return stream.str();
}
template class BPlusTreeLeafPage<GenericKey<4>, RID, GenericComparator<4>>;
template class BPlusTreeLeafPage<GenericKey<8>, RID, GenericComparator<8>>;
template class BPlusTreeLeafPage<GenericKey<16>, RID, GenericComparator<16>>;
template class BPlusTreeLeafPage<GenericKey<32>, RID, GenericComparator<32>>;
template class BPlusTreeLeafPage<GenericKey<64>, RID, GenericComparator<64>>;
}  // namespace bustub
