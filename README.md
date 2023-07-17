# nm

GNU nm lists the symbols from object files objfile.... If no object files are listed as arguments, nm assumes the file a.out.

## Usage

I recoded nm without option

usage `make ; ./ft_nm [.exe]`

> It support 64 and 32 bits executables

## Explanation

```bash
$>hexdump -C a.out | head -n 1
00000000  7f 45 4c 46 02 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
```

Hexa Code | Signification | ascii | details
--- | --- | --- | ---
```7f 45 4c``` | Magic(same byte for all ELF files) | .ELF | /
```02``` | Class | .. | 0: none / 1: 32 bit / 2: 64 bit
```01``` | Significant Byte first | / | 0: none / 1: Least first / 2:Most first
```01``` | always 1 | / |  /
```00``` | OS ABI | .. | 0: None/system V(very Common)
```00``` | ABI Version | / | not used
```00 00 00 00 00 00 00``` | padding | / | /

As you can see, ELF file have usefull informations stored.

You can exploit them in c with the ```struct Elf64_Ehdr``` or ```struct Elf32_Ehdr``` by reading the file with the struct has a buffer.

```c
	Elf64_Ehdr header;
	size_t r = read(fd, &header, sizeof(header));
```



### Docu

[man nm](https://linux.die.net/man/1/nm)
[Explanation of ELF](https://www.youtube.com/watch?v=nC1U1LJQL8o)

