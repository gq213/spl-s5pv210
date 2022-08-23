#include "common.h"

typedef unsigned int(*copy_sd_mmc_to_mem)
	(unsigned int channel, unsigned int start_block, unsigned short block_size, unsigned int *dst, unsigned int with_init);

int load_kernel_from_sd_mmc(void)
{
	unsigned int sd_ch;
	unsigned int sd_idx;
	unsigned int ret;
	unsigned int *p;
	unsigned int image_size;

	sd_ch = *(volatile unsigned int *)(0xD0037488);
	copy_sd_mmc_to_mem copy_lba = (copy_sd_mmc_to_mem)(*(unsigned int *)(0xD0037F98));

	uart_puts("load kernel...\r\n");

	if (sd_ch == 0xEB000000) {
		sd_idx = 0;
	} else if (sd_ch == 0xEB200000) {
		sd_idx = 2;
	} else {
		uart_puts("sd_ch error!\r\n");
		return -1;
	}
	
	ret = copy_lba(sd_idx, KERNEL_LBA_OFFSET, 1, (unsigned int *)KERNEL_LOAD_ADDR, 0);
	if (ret) {
		p = (unsigned int *)KERNEL_LOAD_ADDR;
		image_size = *p;
		uart_puts("image_size=0x");
		dump_hex_32(image_size);
		uart_puts("bytes, ");
		image_size /= 512;
		uart_puts("0x");
		dump_hex_32(image_size);
		uart_puts("lba\r\n");
		if (image_size > (KERNEL_LBA_SIZE - 1)) {
			uart_puts("image too big!\r\n");
			ret = 0;
		} else {
			ret = copy_lba(sd_idx, KERNEL_LBA_OFFSET + 1, image_size, (unsigned int *)KERNEL_LOAD_ADDR, 0);
		}
	}

	if (ret == 0) {
		uart_puts("copy error!\r\n");
		return -1;
	}

	uart_puts("done.\r\n");

	return 0;
}

int load_uboot_from_sd_mmc(void)
{
	unsigned int sd_ch;
	unsigned int sd_idx;
	unsigned int ret;

	sd_ch = *(volatile unsigned int *)(0xD0037488);
	copy_sd_mmc_to_mem copy_lba = (copy_sd_mmc_to_mem)(*(unsigned int *)(0xD0037F98));

	uart_puts("load uboot...\r\n");

	if (sd_ch == 0xEB000000) {
		sd_idx = 0;
	} else if (sd_ch == 0xEB200000) {
		sd_idx = 2;
	} else {
		uart_puts("sd_ch error!\r\n");
		return -1;
	}
	
	ret = copy_lba(sd_idx, UBOOT_LBA_OFFSET, UBOOT_LBA_SIZE, (unsigned int *)UBOOT_LOAD_ADDR, 0);
	if (ret == 0) {
		uart_puts("copy error!\r\n");
		return -1;
	}

	uart_puts("done.\r\n");

	return 0;
}
