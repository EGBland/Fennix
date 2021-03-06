# Fennix
An x86 kernel, written in assembly and C.

## Dependencies
You need a `gcc` cross-compiler and `binutils`, targeting `i686-elf`. You'll also need `nasm` for assembling the assembly files not generated by `gcc`.

## Building
On the first line of the makefile is the variable `PREFIX`; set that to the location of your cross-compiling toolchain. Then, make a folder called `bin` in the root directory of the project, and then do `make all`. This will build `bin/fennix.bin`, a disk image containing the bootloader and kernel.

## References
* Writing a kernel is a new endeavour for me, so my primary reference is Erik Helin and Adam Renberg's *[The little book about OS development](https://littleosbook.github.io/)*.
* The [OSDev wiki](https://wiki.osdev.org/) has been immensely helpful; I've also osmosed some helpful tidbits by lurking in #osdev on libera.chat.
* The *[Intel 64 and IA-32 Architectures Software Developer’s Manual](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)* has offered sufficiently approachable and (naturally) very detailed synopses and explanations of how to program an x86 processor.
