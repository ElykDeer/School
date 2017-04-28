all:
	yasm -f 32 -o solve.o solve.asm
	ld -m elf_i386 -o solve solve.o
	rm solve.o
