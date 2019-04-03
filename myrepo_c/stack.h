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

#define STACK_TYPE int
typedef struct STACK_NODE {
        STACK_TYPE value;
        struct STACK_NODE *next;
}StackNode;

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
typedef struct Stack {
    StackNode *node;
    char(*is_empty)(struct Stack *stack_obj);
    void(*push)(struct Stack *stack_obj, STACK_TYPE value);
    void(*pop)(struct Stack *stack_obj);
    STACK_TYPE(*top)(struct Stack *stack_obj);
}Stack;
#endif

char is_empty(Stack * stack_obj);
void push(Stack * stack_obj, STACK_TYPE value);
void pop(Stack * stack_obj);
STACK_TYPE top(Stack * stack_obj);
Stack* create_stack(void);
void destroy_stack(Stack *stack_obj);



#ifdef __cplusplus
}
#endif

#endif
