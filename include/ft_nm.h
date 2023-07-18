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

void main_32(char *file, int fd);
void main_64(Elf64_Ehdr *header, char *file_data);

#endif