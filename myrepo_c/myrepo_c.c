#include "pch.h"
#include "invendor.h"
int main()
{
	Invrec *a;
	/*
	**注意了，由于动态分配的内存需要释放，如果将这个指针进行了运算
	**free的时候就会出问题，另外如果运算了，其他地方进行引用，也容易
	**出现找错内存块的问题。
	*/
    version_print();
	a = create_subassy_record(3);
	//将参与运算的指针保护起来。
	SUBASSYPART *new_part = a->info.subassy->part;
	strcpy(new_part->partno,"hello world");
	printf("%p\r\n", new_part);
	new_part++;
	strcpy(new_part->partno, "this is my");
	printf("%p\r\n", new_part);
	new_part++;
	//注意此处如果拷贝的数据超过数组长度，内存溢出
	strcpy(new_part->partno, "first function");
	printf("%p\r\n", new_part);
	printf("%s\r\n", new_part->partno);
	//注意这里的a没有被释放，因为他是在函数中调用free
	//只是对a的拷贝进行了修改
	//discard_inventory_record(a);
	discard_inventory_record(&a);
	printf("回收后的地址%p\r\n", a);
	//注意这里如果引用释放后的指针会出问题
	//如果引用NULL指向的数也会出问题，这些编译器都检查不出来
	//printf("回收后的指针地址2%p\r\n", a->info.subassy);
    LOGE("OK");
    LOGD("%s", "hello");
    SETLOG(MAIN_MODULE, DBG_DEBUG);
    LOGD("%s", "hello2");
    LOGI("%s", "DSFASDJKHFKL ASHJDLFIHKSDFDSLKAJFKLJASDLKJFK");
}