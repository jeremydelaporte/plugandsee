
#include "LPC13Uxx.h"

#include "uart.h"

int main(void){

	uint8_t buff[] = "Plug And See\r\n";
	SystemCoreClockUpdate();

	UARTInit(115200);
	UARTSend(buff, 14);

	UARTInit(9600);
	UARTSend(buff, 14);

	for(;;);
}
