/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    ������ģ�巽��ģʽʵ���ļ���д
*   ʹ��˵��    �����ļ���д������ʱ���ȶ����ļ���������
                  �ٶ����ļ������Ķ���FileAccessorContext,
                  ��ʹ��ģ�庯��FileAccess
******************************************************************/
#ifndef  __FILE_OPERATE_H_
#define __FILE_OPERATE_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "stdio.h"
#define fopen  
#define fwrite
#define FILE_SAFE_FUNCTION 0

/******************************************************************
@brief   : �ļ�����ģ��ṹ��
@author  : xiaoqinxing
@input   ��pFname  - ���ļ��ĵ�ַ���ļ���
           pMode   - ���ļ��ķ�ʽ
           process - ������
@output  ��none
@detail  : none
******************************************************************/

typedef struct FileAccessorContext {
    const char * const pFname;
    const char * const pMode;
    void(*const process)(struct 
        FileAccessorContext *pThis, FILE *p);
}FileAccessorContext;

typedef struct {
    FileAccessorContext base;
    int rc;
}IntFileAccessorContext;

char FileAccess(FileAccessorContext *pCtx);

#ifdef __cplusplus
}
#endif

#endif
