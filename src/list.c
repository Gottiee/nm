#include "../include/ft_nm.h"

t_list *init_list(t_list *list)
{
	list = malloc(sizeof(t_list));
	list->address = 0;
	list->type = 0;
	list->name = NULL;
	list->next = NULL;
	list->id = 0;
	return list;
}

void to_lower(char *str)
{
    for (int i = 0; str[i]; i++) 
        if (str[i] >= 'A' && str[i] <= 'Z') 
            str[i] = str[i] + ('a' - 'A');
}

void cut_under(char *str, char ret[100000])
{
	while (str && *str == '_')
		str ++;
	if (!str)
		str --;
	strcpy(ret, str);
	to_lower(ret);
}

t_list *find_place(t_list *list, char *name)
{
	t_list *before = NULL;
	char name_cut[100000];
	cut_under(name, name_cut);
	char list_cut[100000];


	while (list)
	{
		cut_under(list->name, list_cut);
		for (int i = 0; list_cut[i]; i ++)
		{
			if (!name_cut[i])
				return before;
			if (list_cut[i] > name_cut[i])
				return before;
			if (list_cut[i] < name_cut[i])
				break;
		}
		before = list;
		list = list->next;
	}
	return before;
}

t_list *add_list(t_list **list, char *name)
{
	t_list *new, tmp, *res;
	static int i = 0;

	if (i == 0)
	{
		(*list)->name = name;
		i++;
		return *list;
	}
	new = malloc(sizeof(t_list));
	new->name = name;
	res = find_place(*list, name);
	if (!res)
	{
		new->next = *list;
		*list = new;
		return new;
	}
	tmp = *res;
	res->next = new;
	new->next = tmp.next;
	return new;
}

void free_all(t_list *list)
{
	t_list *current = list;
    t_list *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void fill_new_list(t_data *data, t_64 *struct_64, t_list *list, Elf64_Sym sym)
{
	(void)data;
	(void)struct_64;
	(void)sym;
	list->address = getAdressSym();
	list->type = getTypeSym();
}

t_list *fill_list(t_64 *struct_64, t_data *data, t_list *list)
{
	int symbol_count = struct_64->symbol_section_header->sh_size / struct_64->symbol_section_header->sh_entsize;
	t_list *to_fill;

	for (int i = 0; i < symbol_count; i++)
	{
		if (!pars_symbol(struct_64->symbols[i]))
			continue;
		to_fill = add_list(&list, getNameSym(data, struct_64, struct_64->symbols[i]));
		fill_new_list(data, struct_64, to_fill, struct_64->symbols[i]);
	}
	return list;
}