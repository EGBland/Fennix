# Fennix
An x86 microkernel, written in assembly and C.

## Building
You should be good to go so long as you have gcc and nasm. A simple `make all` will build `kernel.elf`, and then you can bung that into your favourite emulator/virtualiser/throwaway hardware. I've been using [QEMU](https://qemu.org/).

## References
Writing a microkernel is a new endeavour for me, so my primary reference is Erik Helin and Adam Renberg's *[The little book about OS development](https://littleosbook.github.io/)*.
