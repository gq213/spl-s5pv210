#include "common.h"

/* gph01 */
static int is_key_press(void)
{
	unsigned int val;
	int cnt;
	
	val = readl(0xE0200C00);
	val &= ~(0xf << 4);
	writel(val, 0xE0200C00);
	
	val = readl(0xE0200C08);
	val &= ~(0x3 << 2);
	val |= 0x2 << 2;
	writel(val, 0xE0200C08);
	
	cnt = 0;
	while (cnt < 10) {
		cnt++;
		uart_puts("##########\r\n");
	}
	
	val = readl(0xE0200C04);
	uart_puts("val=0x");
	dump_hex_32(val);
	uart_puts("\r\n");
	
	if (val & (0x1 << 1)) {
		return 0;
	}
	
	return 1;
}

void c_main(void)
{
	uart_puts("\r\nc_main\r\nboard_type: ");
	#if defined(BOARD_SATE210)
	uart_puts("sate210\r\n");
	#elif defined(BOARD_TQ210V4)
	uart_puts("tq210v4\r\n");
	#endif
	
	if (is_key_press()) {
		load_kernel_from_sd_mmc();
		jump_to_image_linux();
	} else {
		load_uboot_from_sd_mmc();
		jump_to_image_uboot();
	}
}
