#include "../include/ft_nm.h"

int open_file(char *file)
{
	int fd = open(file, O_RDONLY);
	return fd;
}

void choose_bits(int fd, char *file)
{
	Elf64_Ehdr header;
	size_t r = read(fd, &header, sizeof(header));
	if (r != sizeof(header))
	{
		perror("Error reading file:");
		close(fd);
		exit(1);
	}
	if (header.e_ident[EI_CLASS] == ELFCLASS32)
		main_32(file, fd);
	else if (header.e_ident[EI_CLASS] == ELFCLASS64)
		main_64(header);
	else
	{
		fprintf(stderr, "Wrong Class used");
		close(fd);
		exit(1);
	}
		
}

int main(int argc, char **argv)
{
	int fd;

	char *file;

	if (argc == 1)
	{
		if ((fd = open_file("a.out")) == -1)
			return (printf("No a.out\n"), 1);
		file = "a.out";
	}
	else
	{
		if ((fd = open_file(argv[1])) == -1)
			return (printf("File %s can't be open\n", argv[1]), 1);
		file = argv[1];
	}
	// tester le format aussi
	choose_bits(fd, file);
	close(fd);
}