#include "pch.h"
#include "invendor.h"
int main()
{
	Invrec *a;
	/*
	**ע���ˣ����ڶ�̬������ڴ���Ҫ�ͷţ���������ָ�����������
	**free��ʱ��ͻ�����⣬������������ˣ������ط��������ã�Ҳ����
	**�����Ҵ��ڴ������⡣
	*/
    version_print();
	a = create_subassy_record(3);
	//�����������ָ�뱣��������
	SUBASSYPART *new_part = a->info.subassy->part;
	strcpy(new_part->partno,"hello world");
	printf("%p\r\n", new_part);
	new_part++;
	strcpy(new_part->partno, "this is my");
	printf("%p\r\n", new_part);
	new_part++;
	//ע��˴�������������ݳ������鳤�ȣ��ڴ����
	strcpy(new_part->partno, "first function");
	printf("%p\r\n", new_part);
	printf("%s\r\n", new_part->partno);
	//ע�������aû�б��ͷţ���Ϊ�����ں����е���free
	//ֻ�Ƕ�a�Ŀ����������޸�
	//discard_inventory_record(a);
	discard_inventory_record(&a);
	printf("���պ�ĵ�ַ%p\r\n", a);
	//ע��������������ͷź��ָ��������
	//�������NULLָ�����Ҳ������⣬��Щ����������鲻����
	//printf("���պ��ָ���ַ2%p\r\n", a->info.subassy);
    LOGE("OK");
    LOGD("%s", "hello");
    SETLOG(MAIN_MODULE, DBG_DEBUG);
    LOGD("%s", "hello2");
    LOGI("%s", "DSFASDJKHFKL ASHJDLFIHKSDFDSLKAJFKLJASDLKJFK");
}