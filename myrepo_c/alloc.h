#ifndef __ALLOC_H__
#define __ALLOC_H__
/*
**定义一个不易发生错误的内存分配器
*/

#include <stdlib.h>

/*
**这个#define malloc指令，是用于防止由于其他代码块直接调用
**malloc的行为。增加这个指令后，直接调用malloc将会因为语法
**错误而无法编译。在alloc.v中必须加入#undef，这样它才能调用
**malloc而不至于出错。
*/
#define malloc  

#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
extern void *alloc(size_t size);

#endif // !__ALLOC_H__