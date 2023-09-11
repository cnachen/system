#include "uart.h"

int print(const char *s)
{
	int i = 0;
	while (s[i]) {
		uart_putc(s[i++]);
	}
	return i - 1;
}

int printd(int d)
{
	if (d < 0) {
		uart_putc('-');
		d *= -1;
	}
	if (d / 10 != 0) {
		printd(d / 10);
	}
	uart_putc(d % 10 + '0');
	return d;
}

int start()
{
	uart_init();
	printd(114514);
	print("\n");

	return 0;
 }
