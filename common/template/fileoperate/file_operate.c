/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：
*   使用说明    ：
******************************************************************/
#include "pch.h"
#include "file_operate.h"
#undef fopen
#undef fwrite

/******************************************************************
@brief   : 文件操作模板
@author  : xiaoqinxing
@input   ：pFname    - 文件地址
           pMode     - 读写模式
           processor - 操作函数
@output  ：-1 - 打开失败
           0  - 成功
           >0 - 文件打开返回的错误值
@detail  : 定义好了用
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

