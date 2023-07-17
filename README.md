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

### Docu

[man nm](https://linux.die.net/man/1/nm)
[Explanation of ELF](https://www.youtube.com/watch?v=nC1U1LJQL8o)

