/*
**���ڴ���SUBASSEMBLY�����¼�ĺ���
*/
#include "pch.h"
#include "invendor.h"

//���������Ϣ
Invrec *create_subassy_record(int n_parts) {
	Invrec *new_rec;
	//����ΪInvrec���ַ����ڴ�
	new_rec = MALLOC(1, Invrec);
	new_rec->info.subassy = MALLOC(1, Subassyinfo);
	new_rec->info.subassy->part = MALLOC(n_parts, SUBASSYPART);
	new_rec->type = SUBASSY;
	new_rec->info.subassy->n_parts = n_parts;
	return new_rec;
}

//ɾ�������Ϣ
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