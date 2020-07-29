/******************************************************************
*   ��    ��    ��xiaoqinxing
*   ��������    ������һ�����׷���������ڴ������
*   ʹ��˵��    ��
******************************************************************/
#ifndef __ALLOC_H__
#define __ALLOC_H__
/*************************************************************
@brief   : c/c++��ϱ��
@author  : xiaoqinxing
detail   :
C++Ϊ��֧�����أ���������ڱ�����ɺ���ԭ�еĺ����������޸�
����C������ȴ�����޸ĺ�������Ϊ��c/c++��������ͬһ������������
��ϱ�̣�����extern "C"������c��û������ؼ��֣�ֻ����cpp��ʹ
�������������룬��Ϊ__cplusplusֻ����c++�вŶ�����
*************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/*************************************************************
@brief   : malloc�궨��
@author  : xiaoqinxing
@detail  :
���#define mallocָ������ڷ�ֹ�������������ֱ�ӵ���malloc
����Ϊ���������ָ���ֱ�ӵ���malloc������Ϊ�﷨������޷���
�롣��alloc.v�б������#undef�����������ܵ���malloc�������ڳ���
*************************************************************/
#define malloc  
#define free

#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
#define FREE(pointer) free_c((void**)&(pointer))
extern void *alloc(size_t size);
extern void free_c(void **pointer);


/******************************************************************
@brief   : �ڴ洦��ģ��ṹ��
@author  : xiaoqinxing
@input   ��pBuf    - ���ص�ָ��
           size    - ������ڴ��С
           process - ������
@output  ��none
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