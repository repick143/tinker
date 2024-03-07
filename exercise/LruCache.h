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
      mov_to_head(it->second);
      return it->second->val;
    }
    return -1;
  }
  void put(int64_t k, int64_t v) {
    auto it = kv_.find(k);
    if (it == kv_.end()) {
      auto node = new DLinkedListNode(k, v);
      kv_[k] = node;
      add_to_head(node);
      if (++size_ > capacity_) {
        auto key = del_tail();
        kv_.erase(key);
      }
    } else {
      it->second->val = v;
      mov_to_head(it->second);
    }
  }
 private:
  void mov_to_head(DLinkedListNode *node) {
    auto pnode = node->prev;
    pnode->next = node->next;
    pnode->next->prev = pnode;
    add_to_head(node);
  }
  void add_to_head(DLinkedListNode *node) {
    auto nnode = head_->next;
    head_->next = node;
    node->prev = head_;
    node->next = nnode;
    if (nnode != nullptr) {
      nnode->prev = node;
    }
  }
  int64_t del_tail() {
    auto last_node = tail_->prev;
    auto last_two = last_node->prev;
    if (last_two == nullptr) return -1;
    last_two->next = tail_;
    tail_->prev = last_two;
    auto key = last_node->key;
    delete last_node;
    return key;
  }
 private:
  int capacity_{0};
  int32_t size_{0};
  DLinkedListNode *head_{nullptr};
  DLinkedListNode *tail_{nullptr};
  std::unordered_map<int64_t, DLinkedListNode *> kv_{};
};
}

#endif //TINKER_EXERCISE_LRUCACHE_H_
