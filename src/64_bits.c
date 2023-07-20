#include "../include/ft_nm.h"

t_list *init_64(t_64 *struct_64, Elf64_Ehdr *header, t_list *list)
{
	struct_64->header = header;
	struct_64->string_section_header = NULL;
	struct_64->symbol_section_header = NULL;
	struct_64->symbols = NULL;
	list = malloc(sizeof(t_list));
	list->address = 0;
	list->type = 0;
	list->name = NULL;
	list->next = NULL;
	list->id = 0;
	return list;
}

Elf64_Shdr *get_string_section_64(void *f, int idx)
{
	return f + (((Elf64_Ehdr *)f)->e_shoff + (idx * ((Elf64_Ehdr *)f)->e_shentsize));
}

void fill_struct_64(t_64 *struct_64, Elf64_Ehdr *header, t_data *data)
{
	if (header->e_shoff == 0)
		print_error("nm: no section header table\n", NULL, data);
	Elf64_Shdr *section_header = (Elf64_Shdr *)(data->file_data + header->e_shoff);
	for (int i = 0; i < header->e_shnum; i++)
	{
		if (section_header[i].sh_type == SHT_SYMTAB)
		{
			struct_64->symbol_section_header = &section_header[i];
			break;
		}
	}
	if (!struct_64->symbol_section_header)
		print_error("nm: %s: no symbols\n", data->file_name, data);
	struct_64->symbols = (Elf64_Sym *)(data->file_data + struct_64->symbol_section_header->sh_offset);
	struct_64->string_section_header = get_string_section_64((void *)struct_64->header, struct_64->symbol_section_header->sh_link);
	if (!struct_64->string_section_header)
		print_error("nm: %s: no string table associated\n", data->file_name, data);
}

void main_64(Elf64_Ehdr *header, t_data *data)
{
	t_64 struct_64;
	t_list *list = NULL;

	list = init_64(&struct_64, header, list);
	fill_struct_64(&struct_64, header, data);
	fill_list(&struct_64, data, list);
	// free la list et munmup a la fin
}