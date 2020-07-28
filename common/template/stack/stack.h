/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    ��������ʵ�ֵĶ�̬��ջ
*   ʹ��˵��    ��
******************************************************************/
#ifndef  __STACK_H_
#define __STACK_H_

#ifdef __cplusplus
extern "C" {
#endif
//����洢�������ͣ����Զ���Ϊָ�룩
#define STACK_TYPE int

//�Ƿ����ƶ�ջ����
#define STACK_LIMIT 1

//��ջĬ�ϳ��ȣ�����STACK_LIMIT����Ч
#define STACK_LIMIT_DEFAULT_LENTH 10

typedef struct STACK_NODE {
        STACK_TYPE value;
        struct STACK_NODE *next;
}StackNode;

typedef struct STACK_PRIVATE{
    unsigned int length;
    unsigned int max_len;
}STACK_PRIVATE;
//�ṹ������ĺ���ָ�� �����а����ṹ��ʱһ��Ҫ��struct������ᱨ��
//����c�ļ�������Բ��ӣ�������Stack��û�ж������ʹ����
#if 0
//��һ��д��
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
//�ڶ���д��
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
