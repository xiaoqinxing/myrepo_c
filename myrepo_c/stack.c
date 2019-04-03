/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：
*   使用说明    ：
******************************************************************/
#include "pch.h"
#include "stack.h"

/******************************************************************
@brief   : 判断堆栈是否为空
@author  : xiaoqinxing
@input   ：none
@output  ：1 - empty
@detail  : none
******************************************************************/
char is_empty(Stack *stack_obj) {
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
    new_node = MALLOC(1, StackNode);
    new_node->value = value;
    new_node->next = stack_obj->node;
    stack_obj->node = new_node;
}

/******************************************************************
@brief   : pop
@author  : xiaoqinxing
@input   ：none
@output  ：none
@detail  : none
******************************************************************/
void pop(Stack *stack_obj) {
    StackNode *first_node = stack_obj->node;
    if (is_empty(stack_obj)) {
        LOGE("stack is empty,pop is error");
        return;
    }
    stack_obj->node = stack_obj->node->next;
    FREE(first_node);
}

/******************************************************************
@brief   : 堆栈栈顶的值
@author  : xiaoqinxing
@input   ：none
@output  ：返回堆栈栈顶的值
@detail  : none
******************************************************************/
STACK_TYPE top(Stack *stack_obj) {
    if (is_empty(stack_obj)) {
        LOGE("stack is empty,top is null");
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
    stack_obj->push = push;
    stack_obj->pop  = pop;
    stack_obj->top = top;
    stack_obj->is_empty = is_empty;
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
    while (!is_empty(stack_obj)) {
        pop(stack_obj);
    }
    FREE(stack_obj);
}