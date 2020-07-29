#ifndef __CAMLIST_H
#define __CAMLIST_H

#include <stddef.h>
// System dependency
#include <stdlib.h>

#define member_of(ptr, type, member) ({ \
  const typeof(((type *)0)->member) *__mptr = (ptr); \
  (type *)((char *)__mptr - offsetof(type,member));})

struct list_utils {
  struct list_utils *next, *prev;
};

/**
 * 这是一个环形list，list_init指定了队列开始的地方
 */
static inline void list_init(struct list_utils *ptr)
{
  ptr->next = ptr;
  ptr->prev = ptr;
}

/**
 * 在list的末尾增加一个新的节点item
 * head是原来list的尾部，一般为空
 */
static inline void list_add_tail_node(struct list_utils *item,
  struct list_utils *head)
{
  struct list_utils *prev = head->prev;

  head->prev = item;
  item->next = head;
  item->prev = prev;
  prev->next = item;
}

/**
 * 在一个节点之前增加一个新的节点item
 * node是任意一个节点
 */
static inline void list_insert_before_node(struct list_utils *item,
  struct list_utils *node)
{
  item->next = node;
  item->prev = node->prev;
  item->prev->next = item;
  node->prev = item;
}

/**
 * 删除一个节点，由于这是一个环形链表，不需要对链表的前后是否为空进行判断
 */
static inline void list_del_node(struct list_utils *ptr)
{
  struct list_utils *prev = ptr->prev;
  struct list_utils *next = ptr->next;

  next->prev = ptr->prev;
  prev->next = ptr->next;
  ptr->next = ptr;
  ptr->prev = ptr;
}

#endif /* __CAMLIST_H */
