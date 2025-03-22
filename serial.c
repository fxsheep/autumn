#include <stdint.h>
#include "serial.h"
#include "memio.h"

#define UART_BASE 0xc0180000

#define uart_getreg(x) readl(UART_BASE + x)
#define uart_setreg(x,y) writel(y, UART_BASE + x)

enum uart_baudrate {
	UART_19200,
	UART_38400,
	UART_57600,
	UART_115200,
	UART_230400,
	UART_460800,
	UART_614400,
	UART_921600,
};
#define UART_BAUD_RATE UART_19200

// uart clk seems to be 3MHz
static const uint8_t divider[] = {
	[UART_19200]    = 155,
	[UART_38400]    = 78,
	[UART_57600]    = 52,
	[UART_115200]   = 26,
//	[UART_230400]   = 13,
//	[UART_460800]   = 7,
//	[UART_921600]   = 3,
};

int serial_putc(uint8_t c)
{
	/* Wait for UART to be empty */
	while (! (uart_getreg(0x0c) & 0x02));

	uart_setreg(0x00, c);
	return 0;
}

uint8_t serial_getc(void)
{
	while (! (uart_getreg(0x0c) & 0x01));
	return uart_getreg(0x04);
}

/* Return true if there's pending received char */
int serial_available(void)
{
	return uart_getreg(0x0c) & 0x01;
}

int serial_puts(const void *s)
{
	const char *str = s;
	while(*str) {
		if (*str == '\n')
			serial_putc('\r');
		serial_putc(*str++);
	}
	return 0;
}

int serial_read(void *data, int bytes)
{
	int i;
	for (i = 0; i < bytes; i++) {
		*((uint8_t *)data) = serial_getc();
		data++;
	}

	return 0;
}

void serial_init(void)
{
	writel(0x8881, 0xc0180008);
	writel(divider[UART_BAUD_RATE], 0xc0180010);
}
