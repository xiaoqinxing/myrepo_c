/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    ��
*   ʹ��˵��    ��
******************************************************************/
#include "pch.h"
#include "queue.h"

/******************************************************************
@brief   : �ж϶����Ƿ�Ϊ��
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : STACK_LIMITʹ����Ч
******************************************************************/
#if QUEUE_LIMIT
static char is_full(Queue *queue_obj)
{
    return queue_obj->queue_private.length >= queue_obj->queue_private.max_len;
}
#endif

/******************************************************************
@brief   : ���ö�����󳤶�
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : STACK_LIMITʹ����Ч
******************************************************************/
#if QUEUE_LIMIT
static void set_length(Queue * queue_obj, unsigned int value)
{
    queue_obj->queue_private.max_len = value;
}
#endif

/******************************************************************
@brief   : �ж϶����Ƿ�Ϊ��
@author  : xiaoqinxing
@input   ��none
@output  ��1 - empty
@detail  : none
******************************************************************/
static char is_empty(Queue *queue_obj) {
    return queue_obj->front_node == NULL;
}

/******************************************************************
@brief   : enqueue
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : ֵ��ע����Ƕ�һ���ն��н��в�����ʱ��
           ��Ҫ��front_node��rear_node��ָ��new_node��֮��ֻ��Ҫ��
           rear_node��ָ��ָ��new_node����front_node����Ҫ���ˡ�
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
@input   ��none
@output  ��none
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
    //���������free�ѻ��ָ����գ�������������ж�
    //�����Ҫ���¶���һ��ָ�����first_node
    if (queue_obj->front_node == NULL)
        queue_obj->rear_node = NULL;
#if QUEUE_LIMIT
    queue_obj->queue_private.length--;
#endif
    return rc;
}

/******************************************************************
@brief   : ���еĵ�һ��ֵ
@author  : xiaoqinxing
@input   ��none
@output  �����ض�ջջ����ֵ
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
@brief   : �������ж���
@author  : xiaoqinxing
@input   ��void
@output  ������ָ��Stack��ָ��
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
@brief   : ���ٶ��У����ͷ������ڴ�
@author  : xiaoqinxing
@input   ��none
@output  ��none
@detail  : none
******************************************************************/
void destroy_queue(Queue *queue_obj) {
    while (!is_empty(queue_obj)) {
        dequeue(queue_obj);
    }
    FREE(queue_obj);
}