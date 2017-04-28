all:
	yasm -p gas -f elf32 -o assembly.o assembly.s
	ld -m elf_i386 -o assembly assembly.o
	rm assembly.o
