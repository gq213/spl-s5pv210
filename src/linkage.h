/*
 * U-Boot - linkage.h
 *
 * Copyright (c) 2005-2007 Analog Devices Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _LINUX_LINKAGE_H
#define _LINUX_LINKAGE_H

/* Some toolchains use other characters (e.g. '`') to mark new line in macro */
#ifndef ASM_NL
#define ASM_NL		 ;
#endif

#define SYMBOL_NAME(X)		X
#define SYMBOL_NAME_LABEL(X)	X:

#ifndef __ALIGN
#define __ALIGN .align		0
#endif

#define ALIGN			__ALIGN

#define LENTRY(name) \
	ALIGN ASM_NL \
	SYMBOL_NAME_LABEL(name)

#define ENTRY(name) \
	.globl SYMBOL_NAME(name) ASM_NL \
	LENTRY(name)

#ifndef END
#define END(name) \
	.size name, .-name
#endif

#ifndef ENDPROC
#define ENDPROC(name) \
	.type name STT_FUNC ASM_NL \
	END(name)
#endif

#endif
