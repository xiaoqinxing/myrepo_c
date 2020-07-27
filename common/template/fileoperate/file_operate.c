/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    ��
*   ʹ��˵��    ��
******************************************************************/
#include "pch.h"
#include "file_operate.h"
#undef fopen
#undef fwrite

/******************************************************************
@brief   : �ļ�����ģ��
@author  : xiaoqinxing
@input   ��pFname    - �ļ���ַ
           pMode     - ��дģʽ
           processor - ��������
@output  ��-1 - ��ʧ��
           0  - �ɹ�
           >0 - �ļ��򿪷��صĴ���ֵ
@detail  : ���������
******************************************************************/
char FileAccess(FileAccessorContext *pCtx) {
#if FILE_SAFE_FUNCTION
    FILE *fp;
    errno_t rc = fopen_s(&fp, pCtx->pFname, pCtx->pMode);
    if (fp == NULL) return -1;
    pCtx->process(pCtx, fp);
    fclose(fp);
    return 0;
#else
    FILE *fp = fopen(pCtx->pFname, pCtx->pMode);
    if (fp == NULL) return -1;
    pCtx->process(pCtx, fp);
    fclose(fp);
    return 0;
#endif
}

