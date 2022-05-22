#ifndef __BOARD_H__
#define __BOARD_H__

#define BOARD_SATE210
//#define BOARD_TQ210V4

#if defined(BOARD_SATE210)
#define CONFIG_POWER_HOLD	0
#define SDRAM_SIZE			0x10000000	/* 256 MB */
#elif defined(BOARD_TQ210V4)
#define CONFIG_POWER_HOLD	1
#define SDRAM_SIZE			0x20000000	/* 512 MB */
#else
#error "You should define board type"
#endif

#define CONFIG_MCP_SINGLE
#define CONFIG_EVT1

//#define CONFIG_CLK_667_166_166_133
//#define CONFIG_CLK_533_133_100_100
//#define CONFIG_CLK_800_200_166_133
//#define CONFIG_CLK_800_100_166_133
#define CONFIG_CLK_1000_200_166_133
//#define CONFIG_CLK_400_200_166_133
//#define CONFIG_CLK_400_100_166_133

#if defined(CONFIG_CLK_667_166_166_133)
#define APLL_MDIV       0xfa
#define APLL_PDIV       0x6
#define APLL_SDIV       0x1
#elif defined(CONFIG_CLK_533_133_100_100)
#define APLL_MDIV       0x215
#define APLL_PDIV       0x18
#define APLL_SDIV       0x1
#elif defined(CONFIG_CLK_800_200_166_133) || \
	defined(CONFIG_CLK_800_100_166_133) || \
	defined(CONFIG_CLK_400_200_166_133) || \
	defined(CONFIG_CLK_400_100_166_133)
#define APLL_MDIV       0x64
#define APLL_PDIV       0x3
#define APLL_SDIV       0x1
#elif defined(CONFIG_CLK_1000_200_166_133)
#define APLL_MDIV       0x7d
#define APLL_PDIV       0x3
#define APLL_SDIV       0x1
#endif

#define APLL_LOCKTIME_VAL	0x2cf

#if defined(CONFIG_EVT1)
/* Set AFC value */
#define AFC_ON		0x00000000
#define AFC_OFF		0x10000010
#endif

#if defined(CONFIG_CLK_533_133_100_100)
#define MPLL_MDIV	0x190
#define MPLL_PDIV	0x6
#define MPLL_SDIV	0x2
#else
#define MPLL_MDIV	0x29b
#define MPLL_PDIV	0xc
#define MPLL_SDIV	0x1
#endif

#define EPLL_MDIV	0x60
#define EPLL_PDIV	0x6
#define EPLL_SDIV	0x2

#define VPLL_MDIV	0x6c
#define VPLL_PDIV	0x6
#define VPLL_SDIV	0x3

/* CLK_DIV0 */
#define APLL_RATIO	0
#define A2M_RATIO	4
#define HCLK_MSYS_RATIO	8
#define PCLK_MSYS_RATIO	12
#define HCLK_DSYS_RATIO	16
#define PCLK_DSYS_RATIO 20
#define HCLK_PSYS_RATIO	24
#define PCLK_PSYS_RATIO 28

#define CLK_DIV0_MASK	0x7fffffff

#define set_pll(mdiv, pdiv, sdiv)	(1<<31 | mdiv<<16 | pdiv<<8 | sdiv)

#define APLL_VAL	set_pll(APLL_MDIV,APLL_PDIV,APLL_SDIV)
#define MPLL_VAL	set_pll(MPLL_MDIV,MPLL_PDIV,MPLL_SDIV)
#define EPLL_VAL	set_pll(EPLL_MDIV,EPLL_PDIV,EPLL_SDIV)
#define VPLL_VAL	set_pll(VPLL_MDIV,VPLL_PDIV,VPLL_SDIV)

#if defined(CONFIG_CLK_667_166_166_133)
#define CLK_DIV0_VAL    ((0<<APLL_RATIO)|(3<<A2M_RATIO)|(3<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_533_133_100_100)
#define CLK_DIV0_VAL    ((0<<APLL_RATIO)|(3<<A2M_RATIO)|(3<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(3<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_800_200_166_133)
#define CLK_DIV0_VAL    ((0<<APLL_RATIO)|(3<<A2M_RATIO)|(3<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_800_100_166_133)
#define CLK_DIV0_VAL    ((0<<APLL_RATIO)|(7<<A2M_RATIO)|(7<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_400_200_166_133)
#define CLK_DIV0_VAL    ((1<<APLL_RATIO)|(3<<A2M_RATIO)|(1<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_400_100_166_133)
#define CLK_DIV0_VAL    ((1<<APLL_RATIO)|(7<<A2M_RATIO)|(3<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))			
#elif defined(CONFIG_CLK_1000_200_166_133)
#define CLK_DIV0_VAL    ((0<<APLL_RATIO)|(4<<A2M_RATIO)|(4<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#endif

#define CLK_DIV1_VAL	((1<<16)|(1<<12)|(1<<8)|(1<<4))
#define CLK_DIV2_VAL	(1<<0)

#if defined(CONFIG_CLK_533_133_100_100)

#if defined(CONFIG_MCP_SINGLE)

#define DMC0_TIMINGA_REF	0x40e
#define DMC0_TIMING_ROW		0x10233206
#define DMC0_TIMING_DATA	0x12130005
#define	DMC0_TIMING_PWR		0x0E100222

#define DMC1_TIMINGA_REF	0x40e
#define DMC1_TIMING_ROW		0x10233206
#define DMC1_TIMING_DATA	0x12130005
#define	DMC1_TIMING_PWR		0x0E100222

#else

#error "You should define memory type (AC type or H type or B type)"

#endif

#elif defined(CONFIG_CLK_800_200_166_133) || \
	defined(CONFIG_CLK_1000_200_166_133) || \
	defined(CONFIG_CLK_800_100_166_133) || \
	defined(CONFIG_CLK_400_200_166_133) || \
	defined(CONFIG_CLK_400_100_166_133)

#if defined(CONFIG_MCP_SINGLE)

#define DMC0_MEMCONFIG_0	0x20E01323	// MemConfig0	256MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC0_MEMCONFIG_1	0x40F01323	// MemConfig1
#define DMC0_TIMINGA_REF	0x00000618	// TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4E)
#define DMC0_TIMING_ROW		0x28233287	// TimingRow	for @200MHz
#define DMC0_TIMING_DATA	0x23240304	// TimingData	CL=3
#define	DMC0_TIMING_PWR		0x09C80232	// TimingPower

#define	DMC1_MEMCONTROL		0x00202400	// MemControl	BL=4, 2 chip, DDR2 type, dynamic self refresh, force precharge, dynamic power down off
#define DMC1_MEMCONFIG_0	0x40C01323	// MemConfig0	512MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC1_MEMCONFIG_1	0x00E01323	// MemConfig1
#define DMC1_TIMINGA_REF	0x00000618	// TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4
#define DMC1_TIMING_ROW		0x28233289	// TimingRow	for @200MHz
#define DMC1_TIMING_DATA	0x23240304	// TimingData	CL=3
#define	DMC1_TIMING_PWR		0x08280232	// TimingPower
#if defined(CONFIG_CLK_800_100_166_133) || defined(CONFIG_CLK_400_100_166_133)
#define DMC0_MEMCONFIG_0	0x20E01323	// MemConfig0	256MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC0_MEMCONFIG_1	0x40F01323	// MemConfig1
#define DMC0_TIMINGA_REF	0x0000030C	// TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4E)
#define DMC0_TIMING_ROW		0x28233287	// TimingRow	for @200MHz
#define DMC0_TIMING_DATA	0x23240304	// TimingData	CL=3
#define	DMC0_TIMING_PWR		0x09C80232	// TimingPower

#define	DMC1_MEMCONTROL		0x00202400	// MemControl	BL=4, 2 chip, DDR2 type, dynamic self refresh, force precharge, dynamic power down off
#define DMC1_MEMCONFIG_0	0x40C01323	// MemConfig0	512MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC1_MEMCONFIG_1	0x00E01323	// MemConfig1
#define DMC1_TIMINGA_REF	0x0000030C	// TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4
#define DMC1_TIMING_ROW		0x28233289	// TimingRow	for @200MHz
#define DMC1_TIMING_DATA	0x23240304	// TimingData	CL=3
#define	DMC1_TIMING_PWR		0x08280232	// TimingPower
#endif

#else

#error "You should define memory type (AC type or H type)"

#endif //

#else

#define DMC0_TIMINGA_REF	0x50e
#define DMC0_TIMING_ROW		0x14233287
#define DMC0_TIMING_DATA	0x12130005
#define	DMC0_TIMING_PWR		0x0E140222

#define DMC1_TIMINGA_REF	0x618
#define DMC1_TIMING_ROW		0x11344309
#define DMC1_TIMING_DATA	0x12130005
#define	DMC1_TIMING_PWR		0x0E190222

#endif


#if defined(CONFIG_CLK_533_133_100_100)
#define UART_UBRDIV_VAL		26
#define UART_UDIVSLOT_VAL	0x0808
#else
#define UART_UBRDIV_VAL		34
#define UART_UDIVSLOT_VAL	0xDDDD
#endif

#define DEBUG_UART			3
#if (DEBUG_UART == 0)
	#define UART_OFFSET		ELFIN_UART0_OFFSET
	#define BOOTARGS_UART	"console=ttySAC0"
#elif (DEBUG_UART == 1)
	#define UART_OFFSET		ELFIN_UART1_OFFSET
	#define BOOTARGS_UART	"console=ttySAC1"
#elif (DEBUG_UART == 2)
	#define UART_OFFSET		ELFIN_UART2_OFFSET
	#define BOOTARGS_UART	"console=ttySAC2"
#elif (DEBUG_UART == 3)
	#define UART_OFFSET		ELFIN_UART3_OFFSET
	#define BOOTARGS_UART	"console=ttySAC3"
#else
	#error "DEBUG_UART define error"
#endif

#define ELFIN_UART_CONSOLE_BASE (ELFIN_UART_BASE + UART_OFFSET)

#define CONFIG_BOOTARGS		BOOTARGS_UART " noinitrd root=/dev/mmcblk0p1 rw " \
							"rootfstype=ext4 rootwait init=/linuxrc"

#define PHYS_SDRAM_1_BASE	0x20000000	/* DDR2 Bank #0 */
#define PHYS_SDRAM_1_SIZE	SDRAM_SIZE
#define PHYS_SDRAM_2_BASE	0x40000000	/* DDR2 Bank #1 */
#define PHYS_SDRAM_2_SIZE	SDRAM_SIZE

#define STACK_SIZE					(8 * 1024 * 1024)
#define CONFIG_SYS_INIT_SP_ADDR		(PHYS_SDRAM_2_BASE + STACK_SIZE)		// 0x40800000 --> 0x40000000

/* 
The tagged list should be stored in system RAM.

The tagged list must be placed in a region of memory where neither
the kernel decompressor nor initrd 'bootp' program will overwrite
it.  The recommended placement is in the first 16KiB of RAM.
 */
#define TAGGED_LIST_ADDR			0x20000100	// offset=256

/* 
The zImage may also be placed in system RAM and called there.  The
kernel should be placed in the first 128MiB of RAM.  It is recommended
that it is loaded above 32MiB in order to avoid the need to relocate
prior to decompression, which will make the boot process slightly
faster.
 */
#define KERNEL_LOAD_ADDR			0x20008000	// offset=32k

/*
 * bootloader(sd)
 * |512|SPL(16k)|ENV(8k)|UBOOT(512k)|KERNEL(16M)
 */
#define UBOOT_LBA_OFFSET	49
#define UBOOT_LBA_SIZE		1024
#define KERNEL_LBA_OFFSET	(49 + 1024)
#define KERNEL_LBA_SIZE		32768

#endif /*__BOARD_H__*/
