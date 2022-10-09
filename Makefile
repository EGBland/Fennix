PREFIX  = /usr/local/cross
OBJECTS = kernel.o kmain.o vga.o asm.o serial.o log.o idt.o interrupt.o heap.o stdio.o pic.o ps2.o timer.o terminal.o
CC      = $(PREFIX)/bin/i686-elf-gcc
CFLAGS  = -m32 -ffreestanding -I./include -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-value -O0
LD      = $(PREFIX)/bin/i686-elf-ld
LDFLAGS = -Tlink.ld -melf_i386 -L$(PREFIX)/lib/gcc/i686-elf/13.0.0 -lgcc
AS      = nasm
ASFLAGS = -f elf
OBJCOPY = $(PREFIX)/bin/i686-elf-objcopy

all: bin/fennix.bin

bin/fennix.bin: bin/boot.bin bin/kernel.bin
	cat bin/boot.bin bin/kernel.bin > bin/fennix.bin

bin/boot.bin: src/boot/boot.s
	mkdir -p bin
	nasm src/boot/boot.s -f bin -o bin/boot.bin

bin/kernel.bin: kernel.elf
	$(OBJCOPY) -O binary kernel.elf bin/kernel.bin
	#rm -rf kernel.elf

kernel.elf: $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o kernel.elf

%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: src/%.s
	$(AS) $< $(ASFLAGS) -o $@

clean:
	rm -rf *.o *.elf bin

