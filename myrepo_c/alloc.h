#ifndef __ALLOC_H__
#define __ALLOC_H__
/*
**����һ�����׷���������ڴ������
*/

#include <stdlib.h>

/*
**���#define mallocָ������ڷ�ֹ�������������ֱ�ӵ���
**malloc����Ϊ���������ָ���ֱ�ӵ���malloc������Ϊ�﷨
**������޷����롣��alloc.v�б������#undef�����������ܵ���
**malloc�������ڳ���
*/
#define malloc  

#define MALLOC(num, type) (type *)alloc((num) * sizeof(type))
extern void *alloc(size_t size);

#endif // !__ALLOC_H__