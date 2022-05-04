#include "common.h"

static void *g_tagged_list = (void *)((unsigned long)TAGGED_LIST_ADDR);

static struct tag *params;

static void setup_start_tag(void)
{
	params = (struct tag *)g_tagged_list;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}

static void setup_memory_tags(unsigned int start, unsigned int size)
{
	params->hdr.tag = ATAG_MEM;
	params->hdr.size = tag_size (tag_mem32);

	params->u.mem.start = start;
	params->u.mem.size = size;

	params = tag_next (params);
}

static void setup_commandline_tag(char *p)
{
	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;

	strcpy (params->u.cmdline.cmdline, p);

	params = tag_next (params);
}

static void setup_end_tag(void)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}

static void boot_prep_linux(void)
{
	setup_start_tag();
	setup_commandline_tag(CONFIG_BOOTARGS);
	setup_memory_tags(PHYS_SDRAM_1_BASE, PHYS_SDRAM_1_SIZE);
	setup_memory_tags(PHYS_SDRAM_2_BASE, PHYS_SDRAM_2_SIZE);
	setup_end_tag();
}

void jump_to_image_linux(void)
{
	unsigned long machid = 2457;
	typedef void (*image_entry_arg_t)(int, int, void *);
	
	image_entry_arg_t image_entry =
		(image_entry_arg_t)(unsigned long)KERNEL_LOAD_ADDR;

	boot_prep_linux();
	
	image_entry(0, machid, g_tagged_list);
}
