#include "common.h"

void jump_to_image_uboot(void)
{
	unsigned int *p_board_type;
	typedef void (*image_entry_noargs_t)(void);
	
	p_board_type = (unsigned int *)(BOARD_TYPE_ADDR);
	
	#if defined(BOARD_SATE210)
	*p_board_type = 1;
	#elif defined(BOARD_TQ210V4)
	*p_board_type = 2;
	#endif
	
	image_entry_noargs_t image_entry =
		(image_entry_noargs_t)(unsigned long)UBOOT_LOAD_ADDR;
	
	image_entry();
}
