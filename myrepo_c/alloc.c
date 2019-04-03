/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：不易发生错误的内存分配器的实现
*   使用说明    ：
******************************************************************/
#include "pch.h"
#include <stdio.h>
#include "alloc.h"
#undef malloc

/******************************************************************
@brief   : 自定义请求所需的内存
@author  : xiaoqinxing
@input   ：申请内存大小
@output  ：指向所需内存的指针
******************************************************************/
void *alloc(size_t size) {
	void *new_mem;
	new_mem = malloc(size);
	if (new_mem == NULL) {
		printf("out of memory\n");
		exit(1);
	}
	return new_mem;
}


/******************************************************************
@brief   : 自定义释放申请的动态内存
@author  : xiaoqinxing
@input   ：指向需要释放内存块的指针的地址
@output  ：void
******************************************************************/
void free_c(void **pointer) {
	if (*pointer != NULL) {
		free(*pointer);
		//free后将指针变为NULL，防止变为野指针
		*pointer = NULL;
	}
}

/******************************************************************
@brief   : 内存处理模板函数
@author  : xiaoqinxing
@input   ：BufferContext
@output  ：0  - success 
           -1 - 申请内存失败
@detail  : none
******************************************************************/
char MemBuffer(BufferContext *pThis) {
    pThis->pBuf = malloc(pThis->size);
    if (pThis->pBuf == NULL) return -1;
    pThis->process(pThis);
    free(pThis->pBuf);
    return 0;
}