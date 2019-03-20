/*
**���׷���������ڴ��������ʵ��
*/
#include "pch.h"
#include <stdio.h>
#include "alloc.h"
#undef malloc

/*
** �Զ�������������ڴ�
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
** �Զ����ͷ�����Ķ�̬�ڴ�
*/
void free_c(void **pointer) {
	if (*pointer != NULL) {
		free(*pointer);
		//free��ָ���ΪNULL����ֹ��ΪҰָ��
		*pointer = NULL;
	}
}