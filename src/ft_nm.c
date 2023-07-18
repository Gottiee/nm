#include "../include/ft_nm.h"

int open_file(char *file)
{
	int fd = open(file, O_RDONLY);
	return fd;
}

void print_perror(char *file, int fd, char *string, char *cmd)
{
	char *err_mess = malloc(strlen(file) + 500);
	if (!err_mess)
		perror("nm:");
	else
	{
		if (!string)
			sprintf(err_mess, "%s: '%s'", cmd, file);
		else
			sprintf(err_mess, string, file);
		perror(err_mess);
		free(err_mess);
	}
	if (fd > 0)
		close(fd);
	exit(1);
}

void print_error(char *file, char *err, int fd)
{
	if (file)
		fprintf(stderr, err, file);
	else
		fprintf(stderr, "%s", err);
	if (fd > 0)
		close(fd);
	exit(1);
}

void choose_bits(int fd, char *file, char *file_data)
{
	Elf64_Ehdr *header = (Elf64_Ehdr *)file_data;
	(void)header;
	(void)fd;
	(void)file;
	if (header->e_ident[EI_CLASS] == ELFCLASS32)
		main_32(file, fd);
	else if (header->e_ident[EI_CLASS] == ELFCLASS64)
		main_64(header, file_data);
	else
		print_error(file, "nm: %s: File format not recognized\n", fd);
}

char *check_arg(int argc, char **argv, int *fd)
{
	char *file;

	if (argc == 1)
	{
		if ((*fd = open_file("a.out")) == -1)
			print_perror("a.out", -1, 0, "nm");
		file = "a.out";
	}
	else
	{
		if ((*fd = open_file(argv[1])) == -1)
			print_perror(argv[1], -1, 0, "nm");
		file = argv[1];
	}
	return file;
}

char *mmap_file(int fd, char *file)
{
	struct stat file_stat;
	char *file_data;

	if (fstat(fd, &file_stat) == -1)
		print_perror(file, fd, 0, "fstat");
	if (S_ISDIR(file_stat.st_mode))
		print_error(file, "nm: Warning: '%s' is a directory\n", fd);
	file_data = mmap(NULL, file_stat.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (file_data == MAP_FAILED)
		print_perror(file, fd, 0, "mmap");
	return file_data;
}

int main(int argc, char **argv)
{
	int fd;
	char *file;
	char *file_data;

	file = check_arg(argc, argv, &fd);
	file_data = mmap_file(fd, file);
	choose_bits(fd, file, file_data);
	close(fd);
}