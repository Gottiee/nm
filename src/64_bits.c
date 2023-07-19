#include "../include/ft_nm.h"

void print_symbols(t_64 *struct_64, t_data *data)
{
	char *str_table = data->file_data + struct_64->string_section_header->sh_offset;
	int symbol_count = struct_64->symbol_section_header->sh_size / struct_64->symbol_section_header->sh_entsize;
	Elf64_Sym	*symbol;

	for (int i = 0; i < symbol_count; i++)
	{
		symbol = &struct_64->symbols[i];
		(void)symbol;
		if (struct_64->symbols[i].st_name == 0)
			continue;
		char *symbol_name = str_table + (struct_64->symbols[i].st_name);
		printf("Symbol %d: %s\n", i, symbol_name);
	}
}

void init_64(t_64 *struct_64, Elf64_Ehdr *header)
{
	struct_64->header = header;
	struct_64->string_section_header = NULL;
	struct_64->symbol_section_header = NULL;
	struct_64->symbols = NULL;
}

Elf64_Shdr *get_string_section_64(void *f, int idx)
{
	return f + (((Elf64_Ehdr *)f)->e_shoff + (idx * ((Elf64_Ehdr *)f)->e_shentsize ));
}

void main_64(Elf64_Ehdr *header, t_data *data)
{
	t_64 struct_64;

	init_64(&struct_64, header);
	if (header->e_shoff == 0)
		print_error("nm: no section header table\n", NULL, data);
	Elf64_Shdr *section_header = (Elf64_Shdr *)(data->file_data + header->e_shoff);
	for (int i = 0; i < header->e_shnum; i++)
	{
		if (section_header[i].sh_type == SHT_SYMTAB)
			struct_64.symbol_section_header = &section_header[i];
		else if (section_header[i].sh_type == SHT_STRTAB)
			struct_64.string_section_header = &section_header[i];
		if (struct_64.symbol_section_header && struct_64.string_section_header)
		{
			break;
		}
	}
	if (!struct_64.symbol_section_header || !struct_64.string_section_header)
		print_error("nm: %s: no symbols", data->file_name, data);
	struct_64.symbols = (Elf64_Sym *)(data->file_data + struct_64.symbol_section_header->sh_offset);
	struct_64.string_section_header = get_string_section_64((void *)struct_64.header, struct_64.symbol_section_header->sh_link);
	print_symbols(&struct_64, data);
}