#include <stdint.h>
#include "uart.h"

static volatile uint8_t *uart;

void uart_init()
{
	uart = (uint8_t *)UART_BASE_ADDR;
	uint32_t clock_freq = UART_CLOCK_FREQ;
	uint32_t baud_rate = UART_BAUD_RATE;
	uint32_t divisor = clock_freq / (16 * baud_rate);
	uart[UART_LCR] = UART_LCR_DLAB;
	uart[UART_DLL] = divisor & 0xff;
	uart[UART_DLM] = (divisor >> 8) & 0xff;
	uart[UART_LCR] = UART_LCR_PODD | UART_LCR_8BIT;
}

void uart_putc(int c)
{
	while ((uart[UART_LSR] & UART_LSR_RI) == 0);
	uart[UART_THR] = c & 0xff;
}
