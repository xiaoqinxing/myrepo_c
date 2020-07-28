/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：单链表实现的动态堆栈
*   使用说明    ：
******************************************************************/
#ifndef  __STACK_H_
#define __STACK_H_

#ifdef __cplusplus
extern "C" {
#endif
//定义存储数据类型（可以定义为指针）
#define STACK_TYPE int

//是否限制堆栈长度
#define STACK_LIMIT 1

//堆栈默认长度，开启STACK_LIMIT后生效
#define STACK_LIMIT_DEFAULT_LENTH 10

typedef struct STACK_NODE {
        STACK_TYPE value;
        struct STACK_NODE *next;
}StackNode;

typedef struct STACK_PRIVATE{
    unsigned int length;
    unsigned int max_len;
}STACK_PRIVATE;
//结构体里面的函数指针 参数中包含结构体时一定要加struct，否则会报错，
//但是c文件里面可以不加；可能是Stack还没有定义完就使用了
#if 0
//第一种写法
typedef char (*is_empty_func)(struct Stack *stack_obj);
typedef void (*push_func)(struct Stack *stack_obj, STACK_TYPE value);
typedef void (*pop_func)(struct Stack *stack_obj);
typedef STACK_TYPE(*top_func)(struct Stack *stack_obj);

typedef struct Stack {
    StackNode *node;
    is_empty_func is_empty;
    push_func push;
    pop_func pop;
    top_func top;
}Stack;
#else
//第二种写法
typedef struct Stack {
    StackNode *node;
#if STACK_LIMIT
    STACK_PRIVATE stack_private;
    char(*is_full)(struct Stack *stack_obj);
    void(*set_length)(struct Stack *stack_obj, unsigned int value);
#endif
    char(*is_empty)(struct Stack *stack_obj);
    void(*push)(struct Stack *stack_obj, STACK_TYPE value);
    STACK_TYPE(*pop)(struct Stack *stack_obj);
    STACK_TYPE(*top)(struct Stack *stack_obj);
}Stack;
#endif

// char is_stack_full(struct Stack *stack_obj);
// void set_stack_length(struct Stack *stack_obj, unsigned int value);
// char is_stack_empty(Stack * stack_obj);
// void push(Stack * stack_obj, STACK_TYPE value);
// STACK_TYPE pop(Stack * stack_obj);
// STACK_TYPE top(Stack * stack_obj);
Stack* create_stack(void);
void destroy_stack(Stack *stack_obj);



#ifdef __cplusplus
}
#endif

#endif
