
COMPILE_PATH  = /mnt/disk/210/toolchain/gcc-linaro-6.3.1-2017.05-x86_64_arm-linux-gnueabihf/bin
CROSS_COMPILE ?= $(COMPILE_PATH)/arm-linux-gnueabihf-
CC			= $(CROSS_COMPILE)gcc
LD			= $(CROSS_COMPILE)ld.bfd
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

CPPFLAGS	= -nostdinc -isystem $(COMPILE_PATH)/../lib/gcc/arm-linux-gnueabihf/6.3.1/include
CPPFLAGS	+= -DCONFIG_SPL_STACK=0xD0037D80
CFLAGS		= -marm -mno-thumb-interwork -march=armv7-a -mtune=cortex-a8
CFLAGS		+= -Wall -Os

HEAD_FILE 	= $(wildcard src/*.h)

SRC_S = $(wildcard src/*.S)
OBJ_S = $(patsubst src/%.S, src/%.o, $(SRC_S))
SRC_C = $(wildcard src/*.c)
OBJ_C = $(patsubst src/%.c, src/%.o, $(SRC_C))

TARGET = spl_signed.bin

all:$(TARGET)

spl_signed.bin:spl.bin
	gcc -Wall tools/signed_tool.c -o signed_tool
	./signed_tool spl.bin spl_signed.bin

spl.bin:$(OBJ_S) $(OBJ_C)
	$(LD) -T src/spl.lds -Ttext 0xD0020010 -o spl.elf $^
	$(OBJCOPY) -O binary spl.elf spl.bin
	$(OBJDUMP) -D spl.elf > spl.dis

%.o:%.S $(HEAD_FILE)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

%.o:%.c $(HEAD_FILE)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $< -c

clean:
	rm $(OBJ_S) $(OBJ_C) signed_tool *.elf *.bin *.dis -f
