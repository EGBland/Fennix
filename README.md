# Fennix
An x86 microkernel, written in assembly and C.

## Dependencies
You need a `gcc` cross-compiler and `binutils`, targeting `i686-elf`.

## Building
On the first line of the makefile is the variable `PREFIX`; set that to the location of your cross-compiling toolchain. Then, make a folder called `bin` in the root directory of the project, and then do `make all`. This will build `bin/fennix.bin`, a disk image containing the bootloader and kernel.

## References
Writing a microkernel is a new endeavour for me, so my primary reference is Erik Helin and Adam Renberg's *[The little book about OS development](https://littleosbook.github.io/)*.

The [OSDev wiki](https://wiki.osdev.org/) has been helpful.