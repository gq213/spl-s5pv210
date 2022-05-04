#include "common.h"

/* baudrate rest value */
union br_rest {
	unsigned short	slot;		/* udivslot */
	unsigned char	value;		/* ufracval */
};

struct s5p_uart {
	unsigned int	ulcon;
	unsigned int	ucon;
	unsigned int	ufcon;
	unsigned int	umcon;
	unsigned int	utrstat;
	unsigned int	uerstat;
	unsigned int	ufstat;
	unsigned int	umstat;
	unsigned char	utxh;
	unsigned char	res1[3];
	unsigned char	urxh;
	unsigned char	res2[3];
	unsigned int	ubrdiv;
	union br_rest	rest;
	unsigned char	res3[0x3d0];
};

int uart_getc(void)
{
	struct s5p_uart *const uart = (struct s5p_uart *)(ELFIN_UART_CONSOLE_BASE);

	while ((readl(&uart->utrstat) & 0x1) != 0x1);
	
	return readb(&uart->urxh);
}

void uart_putc(const char c)
{
	struct s5p_uart *const uart = (struct s5p_uart *)(ELFIN_UART_CONSOLE_BASE);

	while ((readl(&uart->utrstat) & 0x4) != 0x4);
	
	writeb(c, &uart->utxh);
}

void uart_puts(const char *s)
{
	while (*s) {
		uart_putc(*s++);
	}
}

void dump_hex_8(unsigned char v)
{
	char tmp;
	tmp = (v >> 4) & 0x0f;
	uart_putc((tmp > 9) ? (tmp - 0xa + 'A') : (tmp + '0'));
	tmp = v & 0x0f;
	uart_putc((tmp > 9) ? (tmp - 0xa + 'A') : (tmp + '0'));
}

void dump_hex_16(unsigned short v)
{
	dump_hex_8((v >> 8) & 0x00ff);
	dump_hex_8(v & 0x00ff);
}

void dump_hex_32(unsigned int v)
{
	dump_hex_16((v >> 16) & 0x0000ffff);
	dump_hex_16(v & 0x0000ffff);
}
