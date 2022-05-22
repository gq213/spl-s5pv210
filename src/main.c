#include "common.h"

void c_main(void)
{
	uart_puts("\r\nc_main\r\nboard_type: ");
	#if defined(BOARD_SATE210)
	uart_puts("sate210\r\n");
	#elif defined(BOARD_TQ210V4)
	uart_puts("tq210v4\r\n");
	#endif
	
	load_image_from_sd_mmc();
	
	jump_to_image_linux();
}
