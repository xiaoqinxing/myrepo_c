// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#ifndef PCH_H
#define PCH_H

// TODO: 添加要在此处预编译的标头
#include "alloc.h"
#include "stdio.h"
#include "stdlib.h"
#include "version.h"
#include "debug.h"
#include "file_operate.h"

/**************************************************
                    typedefs
**************************************************/

typedef           char       int8_t;
typedef  unsigned char      uint8_t;
typedef           short      int16_t;
typedef  unsigned short     uint16_t;
typedef           long       int32_t;
typedef  unsigned long      uint32_t;

//使用pthread.h需要此宏定义
#define HAVE_STRUCT_TIMESPEC

#define NO_ERR  0
#define ERROR     1
#define NO_MEMORY 2
#define ERR_QUEUE_FULL 3

#endif //PCH_H
