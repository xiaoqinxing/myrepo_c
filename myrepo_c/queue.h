/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：
*   使用说明    ：
******************************************************************/
#ifndef  __QUEUE_H_
#define  __QUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#define QUEUE_TYPE int

//是否限制队列长度
#define QUEUE_LIMIT 1

//队列默认长度，开启STACK_LIMIT后生效
#define QUEUE_LIMIT_DEFAULT_LENTH 10

//注意结构体里面的成员最好按照空间从大到小排列，节省空间
typedef struct QUEUE_NODE {
    QUEUE_TYPE value;
    struct QUEUE_NODE *next;
}QueueNode;

typedef struct {
    unsigned int length;
    unsigned int max_len;
}QUEUE_PRIVATE;

typedef struct Queue {
    QueueNode *front_node;  //front
    QueueNode *rear_node;   //rear
#if QUEUE_LIMIT
    QUEUE_PRIVATE queue_private;
    char (*is_full)(struct Queue *queue_obj);
    void (*set_length)(struct Queue * queue_obj, unsigned int value);
#endif
    char (*is_empty)(struct Queue *queue_obj);
    void (*enqueue)(struct Queue *queue_obj, QUEUE_TYPE value);
    QUEUE_TYPE (*dequeue)(struct Queue *queue_obj);
    QUEUE_TYPE (*first)(struct Queue *queue_obj);
}Queue;

char is_queue_full(Queue *queue_obj);
void set_queue_length(Queue * queue_obj, unsigned int value);
char is_queue_empty(Queue * queue_obj);
void enqueue(Queue * queue_obj, QUEUE_TYPE value);
QUEUE_TYPE dequeue(Queue *queue_obj);
QUEUE_TYPE first(Queue * queue_obj);
Queue* create_queue(void);
void destroy_queue(Queue *queue_obj);


#ifdef __cplusplus
}
#endif

#endif
