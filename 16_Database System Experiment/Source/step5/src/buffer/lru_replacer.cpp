//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// lru_replacer.cpp
//
// Identification: src/buffer/lru_replacer.cpp
//
// Copyright (c) 2015-2019, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "buffer/lru_replacer.h"

namespace bustub {

LRUReplacer::LRUReplacer(size_t num_pages) { capacity = num_pages; }

LRUReplacer::~LRUReplacer() = default;

bool LRUReplacer::Victim(frame_id_t *frame_id) {
  latch.lock();
  if (lruMap.empty()) {
    latch.unlock();
    return false;
  }

  // 选择列表尾部 也就是最少使用的frame
  frame_id_t lru_frame = lru_list.back();
  lruMap.erase(lru_frame);
  // 列表删除
  lru_list.pop_back();
  *frame_id = lru_frame;
  latch.unlock();
  return true;
}

void LRUReplacer::Pin(frame_id_t frame_id) {
  // 被引用的frame 不能出现在lru list中
  latch.lock();

  if (lruMap.count(frame_id) != 0) {
    lru_list.erase(lruMap[frame_id]);
    lruMap.erase(frame_id);
  }

  latch.unlock();
}

void LRUReplacer::Unpin(frame_id_t frame_id) {
  latch.lock();
  if (lruMap.count(frame_id) != 0) {
    latch.unlock();
    return;
  }
  // if list size >= capacity
  // while {delete front}
  while ((int)Size() >= capacity) {
    frame_id_t need_del = lru_list.front();
    lru_list.pop_front();
    lruMap.erase(need_del);
  }
  // insert
  lru_list.push_front(frame_id);
  lruMap[frame_id] = lru_list.begin();
  latch.unlock();
}

size_t LRUReplacer::Size() { return lru_list.size(); }

}  // namespace bustub
