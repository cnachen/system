#include "uart.h"
#include "library.h"

extern char etext;
extern char edata;
extern char end;

int start()
{
	uart_init();
	printk("%p\n", &etext);
	printk("%p\n", &edata);
	printk("%p\n", &end);

	printk("%p\n", start);
	return 0;
}
