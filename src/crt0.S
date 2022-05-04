/* SPDX-License-Identifier: GPL-2.0+ */
/*
 *  crt0 - C-runtime startup Code for ARM U-Boot
 *
 *  Copyright (c) 2012  Albert ARIBAUD <albert.u.boot@aribaud.net>
 */

#include "linkage.h"

.macro CLEAR_BSS
	ldr	r0, =__bss_start	/* this is auto-relocated! */

	ldr	r1, =__bss_end		/* this is auto-relocated! */
	mov	r2, #0x00000000		/* prepare zero to clear BSS */

clbss_l:cmp	r0, r1			/* while not at end of BSS */
	strlo	r2, [r0]		/* clear 32-bit BSS word */
	addlo	r0, r0, #4		/* move to next */
	blo	clbss_l
.endm

/*
 * entry point of crt0 sequence
 */

ENTRY(_main)

/*
 * Set up initial C runtime environment.
 */

	ldr	r0, =(CONFIG_SPL_STACK)
	bic	r0, r0, #7	/* 8-byte alignment for ABI compliance */
	mov	sp, r0

	CLEAR_BSS
	
	ldr	pc, =c_main
	
	/* we should not return here. */

ENDPROC(_main)
