#include "pch.h"
#include "stdio.h"

int main()
{
	int *new_memory;
	new_memory = MALLOC(25, int);
	for (int i = 0; i < 25; i++)
		*(new_memory + i) = i;
	for (int i = 0; i < 25; i++)
		printf("%d	", *(new_memory + i));
}