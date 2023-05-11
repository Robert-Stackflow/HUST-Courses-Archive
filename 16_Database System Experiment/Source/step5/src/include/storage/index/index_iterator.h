//===----------------------------------------------------------------------===//
//
//                         CMU-DB Project (15-445/645)
//                         ***DO NO SHARE PUBLICLY***
//
// Identification: src/include/index/index_iterator.h
//
// Copyright (c) 2018, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//
/**
 * index_iterator.h
 * For range scan of b+ tree
 */
#pragma once
#include "storage/page/b_plus_tree_leaf_page.h"

namespace bustub {

#define INDEXITERATOR_TYPE IndexIterator<KeyType, ValueType, KeyComparator>

INDEX_TEMPLATE_ARGUMENTS
class IndexIterator {
 public:
  // you may define your own constructor based on your member variables
  IndexIterator();
  ~IndexIterator();
  IndexIterator(B_PLUS_TREE_LEAF_PAGE_TYPE *leaf, int index, BufferPoolManager *bufferPoolManager);
  bool IsEnd();

  const MappingType &operator*();

  IndexIterator &operator++();

  bool operator==(const IndexIterator &itr) const { 
		if (itr.leaf_ == leaf_ &&itr.index_ == index_) return true;
    else return false;
	}

  bool operator!=(const IndexIterator &itr) const {
    if (itr.leaf_ != leaf_ || itr.index_ != index_)
      return true;
    else
      return false;
	}

 private:
  int index_;
  B_PLUS_TREE_LEAF_PAGE_TYPE *leaf_;
  BufferPoolManager *bufferPoolManager_;
};

}  // namespace bustub
