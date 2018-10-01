all: build run
	@echo "Done"

build: guess.s
	nasm -Wall -f bin -o guess guess.s
	@echo $(shell du -b guess | cut -f1)

run:
	qemu-system-i386 -hda guess

clean:
	rm -rf guess