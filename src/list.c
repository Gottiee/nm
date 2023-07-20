#include "../include/ft_nm.h"

t_list *add_list(t_list *list)
{
	static int i = 0;
	t_list *new;

	if (i == 0)
	{
		i++;
		return list;
	}
	new = malloc(sizeof(t_list));
	while (list->next)
		list = list->next;
	new->id = i++;
	new->next = NULL;
	list->next = new;
	return new;
}

void fill_new_list(t_data *data, t_64 *struct_64, t_list *list, Elf64_Sym sym)
{
	list->address = getAdressSym();
	list->type = getTypeSym();
	list->name = getNameSym(data, struct_64, sym);
}

void print_list(t_list *list)
{
	while (list)
	{
		printf("0000000000000000 %c %s\n", list->type, list->name);
		list = list->next;
	}
}

void fill_list(t_64 *struct_64, t_data *data, t_list *list)
{
	int symbol_count = struct_64->symbol_section_header->sh_size / struct_64->symbol_section_header->sh_entsize;
	t_list *to_fill;

	for (int i = 0; i < symbol_count; i++)
	{
		if (!pars_symbol(struct_64->symbols[i]))
			continue;
		to_fill = add_list(list);
		fill_new_list(data, struct_64, to_fill, struct_64->symbols[i]);
	}
	sort_list(list);
	print_list(list);
}