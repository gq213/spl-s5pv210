#ifndef __UART_H__
#define __UART_H__

int uart_getc(void);
void uart_putc(const char c);
void uart_puts(const char *s);
void dump_hex_8(unsigned char v);
void dump_hex_16(unsigned short v);
void dump_hex_32(unsigned int v);

#endif /*__UART_H__*/
