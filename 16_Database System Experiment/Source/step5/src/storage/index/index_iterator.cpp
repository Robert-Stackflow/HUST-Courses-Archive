/**
 * index_iterator.cpp
 */
#include <cassert>

#include "storage/index/index_iterator.h"

namespace bustub {

/*
 * NOTE: you can change the destructor/constructor method here
 * set your own input parameters
 */
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE::IndexIterator(B_PLUS_TREE_LEAF_PAGE_TYPE *leaf, int index, BufferPoolManager *bufferPoolManager)
    : index_(index), leaf_(leaf), bufferPoolManager_(bufferPoolManager) {}
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE::IndexIterator() = default;
INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE::~IndexIterator(){
	if (leaf_ != nullptr) {
    bufferPoolManager_->UnpinPage(leaf_->GetPageId(),false);
  }
}
INDEX_TEMPLATE_ARGUMENTS
bool INDEXITERATOR_TYPE::IsEnd() { 
	//有可能处于末尾，也有可能是空
	return (leaf_ == nullptr) || (index_ >= leaf_->GetSize());
}

INDEX_TEMPLATE_ARGUMENTS
const MappingType &INDEXITERATOR_TYPE::operator*() { 
	return leaf_->GetItem(index_);
}

INDEX_TEMPLATE_ARGUMENTS
INDEXITERATOR_TYPE &INDEXITERATOR_TYPE::operator++() {
	//该迭代器是叶子节点的迭代器，B+树的叶子节点之间相互连接，以实现顺序遍历的特性
	//故此迭代器应该可以在不同的结点间移动
  if ((index_ + 1) >= leaf_->GetSize()) {
    page_id_t next = leaf_->GetNextPageId();
    if (next == INVALID_PAGE_ID) {
      bufferPoolManager_->UnpinPage(leaf_->GetPageId(), false);
      leaf_ = nullptr;
      index_ = 0;
      return *this;
    } else {
      bufferPoolManager_->UnpinPage(leaf_->GetPageId(), false);
      Page *page = bufferPoolManager_->FetchPage(next);
      leaf_ = reinterpret_cast<B_PLUS_TREE_LEAF_PAGE_TYPE *>(page);
      index_ = 0;
      return *this;
    }
  } else {
    index_++;
    return *this;
  }
}

template class IndexIterator<GenericKey<4>, RID, GenericComparator<4>>;

template class IndexIterator<GenericKey<8>, RID, GenericComparator<8>>;

template class IndexIterator<GenericKey<16>, RID, GenericComparator<16>>;

template class IndexIterator<GenericKey<32>, RID, GenericComparator<32>>;

template class IndexIterator<GenericKey<64>, RID, GenericComparator<64>>;

}  // namespace bustub
