/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    �����׷���������ڴ��������ʵ��
*   ʹ��˵��    ��
******************************************************************/
#include "pch.h"
#include <stdio.h>
#include "alloc.h"
#undef malloc

/******************************************************************
@brief   : �Զ�������������ڴ�
@author  : xiaoqinxing
@input   �������ڴ��С
@output  ��ָ�������ڴ��ָ��
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
@brief   : �Զ����ͷ�����Ķ�̬�ڴ�
@author  : xiaoqinxing
@input   ��ָ����Ҫ�ͷ��ڴ���ָ��ĵ�ַ
@output  ��void
******************************************************************/
void free_c(void **pointer) {
	if (*pointer != NULL) {
		free(*pointer);
		//free��ָ���ΪNULL����ֹ��ΪҰָ��
		*pointer = NULL;
	}
}

/******************************************************************
@brief   : �ڴ洦��ģ�庯��
@author  : xiaoqinxing
@input   ��BufferContext
@output  ��0  - success 
           -1 - �����ڴ�ʧ��
@detail  : none
******************************************************************/
char MemBuffer(BufferContext *pThis) {
    pThis->pBuf = malloc(pThis->size);
    if (pThis->pBuf == NULL) return -1;
    pThis->process(pThis);
    free(pThis->pBuf);
    return 0;
}