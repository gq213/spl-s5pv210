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

#if !CONFIG_SYS_ICACHE_OFF
static inline unsigned int get_cr(void)
{
	unsigned int val;

	asm volatile("mrc p15, 0, %0, c1, c0, 0	@ get CR" : "=r" (val)
							  :
							  : "cc");

	return val;
}

static inline void set_cr(unsigned int val)
{
	asm volatile("mcr p15, 0, %0, c1, c0, 0	@ set CR" :
							  : "r" (val)
							  : "cc");
	isb();
}

static void icache_disable(void)
{
	unsigned int reg;

	reg = get_cr();

	set_cr(reg & ~CR_I);
}

static void invalidate_icache_all(void)
{
	/*
	 * Invalidate all instruction caches to PoU.
	 * Also flushes branch target cache.
	 */
	asm volatile ("mcr p15, 0, %0, c7, c5, 0" : : "r" (0));

	/* Invalidate entire branch predictor array */
	asm volatile ("mcr p15, 0, %0, c7, c5, 6" : : "r" (0));

	/* Full system DSB - make sure that the invalidation is complete */
	dsb();

	/* ISB - make sure the instruction stream sees it */
	isb();
}
#endif

void jump_to_image_linux(void)
{
	unsigned long machid = 2457;
	typedef void (*image_entry_arg_t)(int, int, void *);
	
	image_entry_arg_t image_entry =
		(image_entry_arg_t)(unsigned long)KERNEL_LOAD_ADDR;

	boot_prep_linux();
	
	#if !CONFIG_SYS_ICACHE_OFF
	#warning "turn off I-cache"
	icache_disable();
	invalidate_icache_all();
	#endif
	
	image_entry(0, machid, g_tagged_list);
}
