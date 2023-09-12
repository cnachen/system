#include <stdarg.h>

#include "uart.h"
#include "types.h"

static char digits[] = "0123456789abcdef";

static void print_uptr(uptr x, int base)
{
	char b[32];
	int i = 0;

	if (base == 16) {
		uart_putc('0');
		uart_putc('x');
	}

	do {
		b[i++] = digits[x % base];
	} while ((x /= base) != 0);

	while (--i >= 0)
		uart_putc(b[i]);
}

static void print_sptr(sptr x, int base)
{
	if (x < 0) {
		uart_putc('-');
		x = -x;
	}

	print_uptr(x, base);
}

void printk(char *fmt, ...)
{
	va_list ap;
	int i, c;

	va_start(ap, fmt);
	for (i = 0; (c = fmt[i] & 0xff); i++) {
		if (c != '%') {
			uart_putc(c);
			continue;
		}
		c = fmt[++i] & 0xff;
		switch (c) {
		case 'd':
			print_sptr(va_arg(ap, int), 10);
			break;
		case 'x':
			print_sptr(va_arg(ap, int), 16);
			break;
		case 'p':
			print_uptr(va_arg(ap, uptr), 16);
			break;
		case '%':
			uart_putc('%');
			break;
		default:
			uart_putc('%');
			uart_putc(c);
			break;
		}
	}
	va_end(ap);
}
