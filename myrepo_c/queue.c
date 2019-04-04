/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：
*   使用说明    ：
******************************************************************/
#include "pch.h"
#include "queue.h"

/******************************************************************
@brief   : 判断队列是否为满
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : STACK_LIMIT使能生效
******************************************************************/
#if QUEUE_LIMIT
static char is_full(Queue *queue_obj)
{
    return queue_obj->queue_private.length >= queue_obj->queue_private.max_len;
}
#endif

/******************************************************************
@brief   : 设置队列最大长度
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : STACK_LIMIT使能生效
******************************************************************/
#if QUEUE_LIMIT
static void set_length(Queue * queue_obj, unsigned int value)
{
    queue_obj->queue_private.max_len = value;
}
#endif

/******************************************************************
@brief   : 判断队列是否为空
@author  : xiaoqinxing
@input   ：none
@output  ：1 - empty
@detail  : none
******************************************************************/
static char is_empty(Queue *queue_obj) {
    return queue_obj->front_node == NULL;
}

/******************************************************************
@brief   : enqueue
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : 值得注意的是对一个空队列进行操作的时候：
           需要将front_node和rear_node都指向new_node；之后只需要将
           rear_node的指针指向new_node，而front_node不需要动了。
******************************************************************/
static void enqueue(Queue *queue_obj, QUEUE_TYPE value) {
    QueueNode *new_node;
#if QUEUE_LIMIT
    if (is_full(queue_obj)) {
        LOGE("queue is full,enqueue is error");
        return;
    }
#endif
    new_node = MALLOC(1, QueueNode);
    new_node->value = value;
    new_node->next = NULL;
    if(queue_obj->rear_node == NULL)
        queue_obj->front_node = new_node;
    else
        queue_obj->rear_node->next = new_node;
    queue_obj->rear_node = new_node;
#if QUEUE_LIMIT
    queue_obj->queue_private.length++;
#endif
}

/******************************************************************
@brief   : dequeue
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
static QUEUE_TYPE dequeue(Queue *queue_obj) {
    QueueNode *first_node = queue_obj->front_node;
    if (is_empty(queue_obj)) {
        LOGE("queue is empty,dequeue is error");
        return -1;
    }
    QUEUE_TYPE rc = first_node->value;
    queue_obj->front_node = queue_obj->front_node->next;
    FREE(first_node);
    //由于这里的free把会把指针清空，不利于下面的判断
    //因此需要重新定义一个指针变量first_node
    if (queue_obj->front_node == NULL)
        queue_obj->rear_node = NULL;
#if QUEUE_LIMIT
    queue_obj->queue_private.length--;
#endif
    return rc;
}

/******************************************************************
@brief   : 队列的第一个值
@author  : xiaoqinxing
@input   ：none
@output  ：返回堆栈栈顶的值
@detail  : none
******************************************************************/
static QUEUE_TYPE first(Queue *queue_obj) {
    if (is_empty(queue_obj)) {
        LOGE("stack is empty,top is null");
        return -1;
    }
    else
        return queue_obj->front_node->value;
}

/******************************************************************
@brief   : 创建队列对象
@author  : xiaoqinxing
@input   ：void
@output  ：返回指向Stack的指针
@detail  : none
******************************************************************/
Queue* create_queue(void) {
    Queue *queue_obj = MALLOC(1, Queue);
    queue_obj->front_node = NULL;
    queue_obj->rear_node = NULL;
#if QUEUE_LIMIT
    queue_obj->queue_private.length = 0;
    queue_obj->queue_private.max_len = QUEUE_LIMIT_DEFAULT_LENTH;
    queue_obj->set_length = set_length;
    queue_obj->is_full = is_full;
#endif
    queue_obj->enqueue = enqueue;
    queue_obj->dequeue = dequeue;
    queue_obj->first = first;
    queue_obj->is_empty = is_empty;
    return queue_obj;
}

/******************************************************************
@brief   : 销毁队列，并释放所有内存
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
void destroy_queue(Queue *queue_obj) {
    while (!is_empty(queue_obj)) {
        dequeue(queue_obj);
    }
    FREE(queue_obj);
}