all:
	@echo "Must specify a subcommand."

build-full: Dockerfile.full
	docker build -t xv6-full -f Dockerfile.full .

# Full Virtualization...Run Docker to compile xv6 AND run the QEMU image that it makes
run-full: build-full
	docker run --rm -it xv6-full


build-compiler: Dockerfile.compiler
	docker build -t xv6-compiler -f Dockerfile.compiler .

compile: build-compiler
	docker run --rm -v "${PWD}":/xv6 -it xv6-compiler
	sleep 2 # Wait for files to copy out of container... :/

# Compiles xv6 with the version of gcc/on the platform it was designed and spit out an image...run in QEMU on host (no nested virtualization)
run-compile: compile fs.img xv6.img
	qemu-system-i386 -serial mon:stdio -hdb fs.img xv6.img -smp 1 -m 2G -display none

clean:
	rm fs.img xv6.img
