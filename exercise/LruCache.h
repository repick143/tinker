//
// Created by ccx on 2024/3/6.
//

#ifndef TINKER_EXERCISE_LRUCACHE_H_
#define TINKER_EXERCISE_LRUCACHE_H_

#include <cstdint>
#include <unordered_map>

struct DLinkedListNode {
  DLinkedListNode() = default;
  DLinkedListNode(int64_t key, int64_t val) : key(key), val(val) {}

  DLinkedListNode *prev{nullptr};
  DLinkedListNode *next{nullptr};
  int64_t key{0};
  int64_t val{0};
};

namespace tinker {
class LruCache {
 public:
  explicit LruCache(int32_t capacity) : capacity_(capacity) {
    head_ = new DLinkedListNode();
    tail_ = new DLinkedListNode();
    head_->next = tail_;
    tail_->prev = head_;
  }
  int64_t get(int64_t k) {
    auto it = kv_.find(k);
    if (it != kv_.end()) {
      move_to_head(it->second);
      return it->second->val;
    }
    return -1;
  }
  void put(int64_t k, int64_t v) {
    auto it = kv_.find(k);
    if (it == kv_.end()) {
      auto node = new DLinkedListNode(k, v);
      add_to_head(node);
    }
  }
 private:
  void move_to_head(DLinkedListNode *node);
  void add_to_head(DLinkedListNode *node);
  void del_tail();
 private:
  int capacity_{0};
  int32_t size_{0};
  DLinkedListNode *head_{nullptr};
  DLinkedListNode *tail_{nullptr};
  std::unordered_map<int64_t, DLinkedListNode *> kv_{};
};
}

#endif //TINKER_EXERCISE_LRUCACHE_H_
