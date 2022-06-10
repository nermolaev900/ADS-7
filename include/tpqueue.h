// Copyright 2022 Nikita Ermolaev
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template <typename T>
class TPQueue {
 private:
  struct ITEM {
    T val;
    ITEM* next;
    ITEM* prev;
  };
  TPQueue::ITEM* create(const T& val) {
    ITEM* item = new ITEM;
    item->val = val;
    item->next = item->prev = nullptr;
    return item;
  }
  ITEM* tail;
  ITEM* head;

 public:
  TPQueue() : head(nullptr), tail(nullptr) {}
  void push(const T& val) {
    ITEM* cur = head;
    ITEM* item = create(val);
    while (cur && cur->val.prior >= val.prior)
      cur = cur->next;
    if (!cur && head) {
      tail->next = item;
      item->prev = tail;
      tail = item;
      return;
    } else if (!cur && !head) {
      head = tail = item;
    } else if (!cur->prev) {
      head->prev = item;
      item->next = head;
      head = item;
    } else {
      cur->prev->next = item;
      item->prev = cur->prev;
      item->next = cur;
      cur->prev = item;
    }
  }
  T pop() {
    if (!head || !tail) throw "Empty";
    ITEM* temp = head->next;
    if (temp) temp->prev = nullptr;
    T val = head->val;
    delete head;
    head = temp;
    if (!head) tail = nullptr;
    return val;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
