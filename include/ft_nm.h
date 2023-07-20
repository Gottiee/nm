#ifndef FT_NM
#define FT_NM

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <elf.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdbool.h>

typedef struct s_list
{
	unsigned long address;
	char type;
	char *name;
	struct s_list *next;
	int id;
} t_list;

typedef struct s_data
{
	int fd;
	off_t size_mmap;
	char *file_data;
	char *file_name;
} t_data;

typedef struct s_64
{
	Elf64_Shdr	*symbol_section_header;
	Elf64_Shdr	*string_section_header;
	Elf64_Sym	*symbols;
	Elf64_Ehdr	*header;
} t_64;

/* ft_nm*/
void main_32(t_data *data);
void main_64(Elf64_Ehdr *header, t_data *data);
void print_error(char *err, char *file_name, t_data *data);
void print_perror(char *string, char *cmd, t_data *data);

/* list*/
void fill_list(t_64 *struct_64, t_data *data, t_list *list);

/* symbols*/
bool pars_symbol(Elf64_Sym sym);
long getAdressSym(void);
char getTypeSym(void);
char *getNameSym(t_data *data, t_64 *struct_64, Elf64_Sym sym);

/* sort*/
void sort_list(t_list *list);
#endif