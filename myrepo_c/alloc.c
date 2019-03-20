/*
**不易发生错误的内存分配器的实现
*/
#include "pch.h"
#include <stdio.h>
#include "alloc.h"
#undef malloc

/*
** 自定义请求所需的内存
*/
void *alloc(size_t size) {
	void *new_mem;
	new_mem = malloc(size);
	if (new_mem == NULL) {
		printf("out of memory\n");
		exit(1);
	}
	return new_mem;
}

/*
** 自定义释放申请的动态内存
*/
void free_c(void **pointer) {
	if (*pointer != NULL) {
		free(*pointer);
		//free后将指针变为NULL，防止变为野指针
		*pointer = NULL;
	}
}