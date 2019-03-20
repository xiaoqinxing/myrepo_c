/*
**用于创建SUBASSEMBLY存货纪录的函数
*/
#include "pch.h"
#include "invendor.h"

//创建存货信息
Invrec *create_subassy_record(int n_parts) {
	Invrec *new_rec;
	//尝试为Invrec部分分配内存
	new_rec = MALLOC(1, Invrec);
	new_rec->info.subassy = MALLOC(1, Subassyinfo);
	new_rec->info.subassy->part = MALLOC(n_parts, SUBASSYPART);
	new_rec->type = SUBASSY;
	new_rec->info.subassy->n_parts = n_parts;
	return new_rec;
}

//删除存货信息
void discard_inventory_record(Invrec **record) {
	switch ((*record)->type) {
	case SUBASSY:
		FREE((*record)->info.subassy->part);
		FREE((*record)->info.subassy);
	break;
	case PART:
		FREE((*record)->info.part);
		break;
	default:
		printf("record type is error");
	}
	FREE(*record);
}