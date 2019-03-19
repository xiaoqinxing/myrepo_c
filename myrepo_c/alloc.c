/*
**不易发生错误的内存分配器的实现
*/
#include "pch.h"
#include <stdio.h>
#include "alloc.h"
#undef malloc


void *alloc(size_t size) {
	void *new_mem;
	/*
	** 请求所需的内存
	*/
	new_mem = malloc(size);
	if (new_mem == NULL) {
		printf("out of memory\n");
		exit(1);
	}
	return new_mem;
}