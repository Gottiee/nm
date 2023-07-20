#include "../include/ft_nm.h"

char *getNameSym(t_data *data, t_64 *struct_64, Elf64_Sym sym)
{
	char *str_table = data->file_data + struct_64->string_section_header->sh_offset;
	return str_table + (sym.st_name);
}

char getTypeSym(void)
{
	return 'X';
}

long getAdressSym(void)
{
	return 0;
}

bool pars_symbol(Elf64_Sym sym)
{
	if (sym.st_name == 0)
		return false;
	// if (sym.st_info != STB_GLOBAL)
	// 	return false;
	return true;
}