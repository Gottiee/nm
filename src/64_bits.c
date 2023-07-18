#include "../include/ft_nm.h"

void main_64(Elf64_Ehdr *header, char *file_data)
{
	Elf64_Shdr *section_header = (Elf64_Shdr *)(file_data + header->e_shoff);
}