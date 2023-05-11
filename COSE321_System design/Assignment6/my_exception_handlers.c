#include "xil_exception.h"
#include "uart_regs.h"

unsigned char * LED_addr  = (unsigned int *) 0x41200000;
unsigned char   LED_data = 0xC3;
char			time_str[12] = {'0', '0', ':', ' ', '0', '0', ':', ' ', '0', '0', '\r', '\0'};

void _update_time(unsigned short hour, unsigned short min, unsigned short sec) {
	time_str[0] = hour / 10 + '0';
	time_str[1] = hour % 10 + '0';
	time_str[4] = min / 10 + '0';
	time_str[5] = min % 10 + '0';
	time_str[8] = sec / 10 + '0';
	time_str[9] = sec % 10 + '0';
}

void _print_time_UART(void) {
	unsigned int	*UART_Channel_sts_reg0 = uart_Channel_sts_reg0;
	unsigned int	*UART_TX_RX_FIFO0 = uart_TX_RX_FIFO0;
	int 			i;

	i = -1;
	while (time_str[++i]) {
		// Check to see if the Tx FIFO is empty
		while ((*UART_Channel_sts_reg0 & 0x8) != 0x8);
		*UART_TX_RX_FIFO0 = time_str[i];
	}
}

Xil_ExceptionHandler Suh_SVC_handler(void *Data)
{
	// turn on 2 LEDs on Zedboard
	*LED_addr = 0x81;
}

Xil_ExceptionHandler My_IRQ_handler(void *Data)
{
	unsigned int * GICC_IAR  = (unsigned int *) 0xF8F0010C;
	unsigned int * GICC_EOIR = (unsigned int *) 0xF8F00110;

	unsigned int 			who_requested;
	static unsigned short	hour;
	static unsigned short	minute;
	static unsigned short	second;

	// Check out who requested the interrupt
	// by reading Acknowledge Register in GICC
	who_requested = *GICC_IAR ;

	// Private Timer IRQ handler
	if (who_requested == 29) {
		second += 1;
		if (second == 60) {
			second = 0;
			minute += 1;
			if (minute == 60) {
				minute = 0;
				hour += 1;
			}
		}
		_update_time(hour, minute, second);
		_print_time_UART();
	}

	// Inform GICC that the IRQ service has been completed
	*GICC_EOIR = who_requested ;
}

void My_register_exception_handler()
{

	// Register callback function for SVC exception: suh_SVC_handler
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, My_IRQ_handler, NULL);

	// Register callback function for SVC exception: suh_SVC_handler
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_SWI_INT, Suh_SVC_handler, NULL);

}
