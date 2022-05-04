#include "common.h"

void c_main(void)
{
	uart_puts("\r\nc_main\r\n");
	
	load_image_from_sd_mmc();
	
	jump_to_image_linux();
}
