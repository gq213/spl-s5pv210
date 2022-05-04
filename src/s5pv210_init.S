#include "s5pv210.h"
#include "board.h"

	.globl lowlevel_init
lowlevel_init:
	mov	r11, lr
	
#if CONFIG_POWER_HOLD
	/* PS_HOLD(GPJ2_5) set to output high */
	ldr	r0, =0xE0200000
	ldr	r1, =0x00100000
	str	r1, [r0, #0x280]

	ldr	r1, =0x0400
	str	r1, [r0, #0x288]

	ldr	r1, =0x20
	str	r1, [r0, #0x284]
#endif
	
	bl async_init
	
	/* IO Retention release */
	ldr	r0, =0xE010E000
	ldr	r1, [r0]
	ldr	r2, =((1 << 31) | (1 << 29) | (1 << 28))	/* gpio-31, mmc-29, uart-28 */
	orr	r1, r1, r2
	str	r1, [r0]
	
	/* Disable Watchdog */
	ldr	r0, =0xE2700000
	mov	r1, #0
	str	r1, [r0]
	
	bl interrupt_init
	
	bl system_clock_init
	bl mem_ctrl_asm_init
	bl uart_asm_init
	bl tzpc_init
	
	/* ABB disable */
	ldr	r0, =0xE010C300
	ldr	r1, =0x00800000
	str	r1, [r0]
	
	/* Print 'K' */
	ldr	r0, =ELFIN_UART_CONSOLE_BASE
	ldr	r1, =0x4b4b4b4b
	str	r1, [r0, #UTXH_OFFSET]
	
	mov	lr, r11
	mov	pc, lr

/*
 * uart_asm_init: Initialize UART in asm mode, 115200bps fixed.
 * void uart_asm_init(void)
 */
uart_asm_init:

	/* set GPIO(GPA) to enable UART0-UART4 */
	@ GPIO setting for UART0-UART4
	ldr	r0, =ELFIN_GPIO_BASE
	ldr	r1, =0x22222222
	str r1, [r0, #GPA0CON_OFFSET]
	ldr r1, =0x2222
	str r1, [r0, #GPA1CON_OFFSET]
	
	ldr	r0, =ELFIN_UART_CONSOLE_BASE
	mov	r1, #0x0
	str	r1, [r0, #0x08]
	str	r1, [r0, #0x0C]
	
	mov	r1, #0x3
	str	r1, [r0, #0x00]
	
	ldr	r1, =0x3c5
	str	r1, [r0, #0x04]
	
	ldr	r1, =UART_UBRDIV_VAL
	str	r1, [r0, #0x28]
	
	ldr	r1, =UART_UDIVSLOT_VAL
	str	r1, [r0, #0x2C]
	
	ldr	r1, =0x4f4f4f4f
	str	r1, [r0, #UTXH_OFFSET]		@'O'
	
	mov	pc, lr
