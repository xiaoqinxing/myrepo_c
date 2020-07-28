/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：
*   使用说明    ：
******************************************************************/
#include "stack.h"
#include "common.h"
#include "alloc.h"
/******************************************************************
@brief   : 判断堆栈是否为满
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : STACK_LIMIT使能生效
******************************************************************/
#if STACK_LIMIT
char is_stack_full(Stack * stack_obj)
{
    return stack_obj->stack_private.length >= stack_obj->stack_private.max_len;
}
#endif

/******************************************************************
@brief   : 设置堆栈最大长度
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : STACK_LIMIT使能生效
******************************************************************/
#if STACK_LIMIT
void set_stack_length(Stack * stack_obj, unsigned int value)
{
    stack_obj->stack_private.max_len = value;
}
#endif

/******************************************************************
@brief   : 判断堆栈是否为空
@author  : xiaoqinxing
@input   ：none
@output  ：1 - empty
@detail  : none
******************************************************************/
char is_stack_empty(Stack *stack_obj) {
    return stack_obj->node == NULL;
}

/******************************************************************
@brief   : push
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
void push(Stack *stack_obj, STACK_TYPE value){
    StackNode *new_node;
#if STACK_LIMIT
    if (is_stack_full(stack_obj)) {
        ALOGE("stack is full,push is error");
        return;
    }
#endif
    new_node = MALLOC(1, StackNode);
    new_node->value = value;
    new_node->next = stack_obj->node;
    stack_obj->node = new_node;
#if STACK_LIMIT
    stack_obj->stack_private.length++;
#endif
}

/******************************************************************
@brief   : pop
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
STACK_TYPE pop(Stack *stack_obj) {
    StackNode *first_node = stack_obj->node;
    if (is_stack_empty(stack_obj)) {
        ALOGE("stack is empty,pop is error");
        return -1;
    }
    STACK_TYPE rc = first_node->value;
    stack_obj->node = stack_obj->node->next;
    FREE(first_node);
#if STACK_LIMIT
    stack_obj->stack_private.length--;
#endif
    return rc;
}

/******************************************************************
@brief   : 堆栈栈顶的值
@author  : xiaoqinxing
@input   ：none
@output  ：返回堆栈栈顶的值
@detail  : none
******************************************************************/
STACK_TYPE top(Stack *stack_obj) {
    if (is_stack_empty(stack_obj)) {
        ALOGE("stack is empty,top is null");
        return -1;
    }
    else
        return stack_obj->node->value;
}

/******************************************************************
@brief   : 创建堆栈对象
@author  : xiaoqinxing
@input   ：void
@output  ：返回指向Stack的指针
@detail  : none
******************************************************************/
Stack* create_stack(void) {
    Stack *stack_obj=MALLOC(1,Stack);
    stack_obj->node = NULL;
#if STACK_LIMIT
    stack_obj->stack_private.length = 0;
    stack_obj->stack_private.max_len = STACK_LIMIT_DEFAULT_LENTH;
    stack_obj->set_length = set_stack_length;
    stack_obj->is_full = is_stack_full;
#endif
    stack_obj->push = push;
    stack_obj->pop  = pop;
    stack_obj->top = top;
    stack_obj->is_empty = is_stack_empty;
    return stack_obj;
}

/******************************************************************
@brief   : 销毁堆栈，并释放所有内存
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
void destroy_stack(Stack *stack_obj){
    while (!is_stack_empty(stack_obj)) {
        pop(stack_obj);
    }
    FREE(stack_obj);
}