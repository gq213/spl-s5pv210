
从uboot里面提取部分代码，完成最基础功能的初始化，通过按键判断引导uboot或kernel。


编译适用于sate210的spl

修改src/board.h

#define BOARD_SATE210

//#define BOARD_TQ210V4

然后make


编译适用于tq210v4的spl

修改src/board.h

//#define BOARD_SATE210

#define BOARD_TQ210V4

然后make


烧录spl

sudo dd if=spl_signed.bin of=/dev/sdX bs=512 seek=1

sync


烧录uboot

sudo dd if=u-boot.bin of=/dev/sdX bs=512 seek=49

sync


烧录kernel

sudo dd if=zImagedtb_pad of=/dev/sdX bs=512 seek=1073

sync
