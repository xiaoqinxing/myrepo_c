/******************************************************************
*   作    者    ：xiaoqinxing
*   功能描述    ：定义一个不易发生错误的内存分配器
*   使用说明    ：
******************************************************************/
#ifndef __ALLOC_H__
#define __ALLOC_H__
/*************************************************************
@brief   : c/c++混合编程
@author  : xiaoqinxing
detail   :
C++为了支持重载，其编译器在编译完成后会对原有的函数名进行修改
但是C编译器却不会修改函数名；为了c/c++都能引用同一个函数，进行
混合编程，增加extern "C"。由于c中没有这个关键字，只能在cpp中使
用增加条件编译，因为__cplusplus只有在c++中才定义了
*************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/*************************************************************
@brief   : malloc宏定义
@author  : xiaoqinxing
@detail  :
这个#define malloc指令，是用于防止由于其他代码块直接调用malloc
的行为。增加这个指令后，直接调用malloc将会因为语法错误而无法编
译。在alloc.v中必须加入#undef，这样它才能调用malloc而不至于出错。
*************************************************************/
#define malloc  
#define free

#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
#define FREE(pointer) free_c((void**)&(pointer))
extern void *alloc(size_t size);
extern void free_c(void **pointer);


/******************************************************************
@brief   : 内存处理模板结构体
@author  : xiaoqinxing
@input   ：pBuf    - 返回的指针
           size    - 申请的内存大小
           process - 处理函数
@output  ：none
@detail  : none
******************************************************************/

typedef struct BufferContext {
    void *pBuf;
    size_t size;
    void(*process)(struct BufferContext *p);
}BufferContext;

char MemBuffer(BufferContext *pThis);

#ifdef __cplusplus
}
#endif

#endif // !__ALLOC_H__