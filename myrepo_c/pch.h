// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�

#ifndef PCH_H
#define PCH_H

// TODO: ���Ҫ�ڴ˴�Ԥ����ı�ͷ
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

//ʹ��pthread.h��Ҫ�˺궨��
#define HAVE_STRUCT_TIMESPEC

#define NO_ERR  0
#define ERROR     1
#define NO_MEMORY 2
#define ERR_QUEUE_FULL 3

#endif //PCH_H
