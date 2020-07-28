/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：利用模板方法模式实现文件读写
*   使用说明    ：对文件读写操作的时候，先定义文件操作函数
                  再定义文件操作的对象FileAccessorContext,
                  在使用模板函数FileAccess
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
@brief   : 文件操作模板结构体
@author  : xiaoqinxing
@input   ：pFname  - 打开文件的地址及文件名
           pMode   - 打开文件的方式
           process - 处理函数
@output  ：none
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
