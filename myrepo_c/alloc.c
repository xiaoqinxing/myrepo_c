/*
**���׷���������ڴ��������ʵ��
*/
#include "pch.h"
#include <stdio.h>
#include "alloc.h"
#undef malloc


void *alloc(size_t size) {
	void *new_mem;
	/*
	** ����������ڴ�
	*/
	new_mem = malloc(size);
	if (new_mem == NULL) {
		printf("out of memory\n");
		exit(1);
	}
	return new_mem;
}