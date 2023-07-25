#include "../include/ft_nm.h"

void print_list(t_list *list)
{
	while (list)
	{
		printf("0000000000000000 %c %s\n", list->type, list->name);
		list = list->next;
	}
}