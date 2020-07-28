#ifndef __INVENDOR_H__
#define __INVENDOR_H__
//定义一个存货记录的声明
typedef struct {
	int cost;
	int supplier;
}Partinfo;

typedef struct {
	char partno[20];
	short quan;
}SUBASSYPART;

typedef struct {
	int n_parts;
	SUBASSYPART *part;
}Subassyinfo;

typedef struct {
	char partno[20];
	int quan;
	enum {PART, SUBASSY}type;
	union {
		Partinfo *part;
		Subassyinfo *subassy;
	}info;
}Invrec;

Invrec *create_subassy_record(int n_parts);
void discard_inventory_record(Invrec **record);

#endif // !__DATA_TYPE_H__

