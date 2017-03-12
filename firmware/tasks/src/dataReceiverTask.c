
#include "dataReceiverTask.h"
#include "LPC13Uxx.h"

static uint8_t fifo[64];
static uint8_t i;

extern QueueHandle_t xQueueInput;

void dataReceiverTask(void *pvParameters) {
#ifdef DBG_DATA_RECEIVER
	print_string("dataReceiverTask task launched\r\n");
#endif
	int j;

	for(;;) {
		memset((void *)fifo, '\0', sizeof(fifo));
		i = 0;

		while(!(LPC_USART->LSR & 0x01)); // Wait for a new command
		fifo[i] = LPC_USART->RBR;
		i++;

		if(fifo[(i-1)] == 0x7e) { // Beginning of a new trame
			while(!(LPC_USART->LSR & 0x01)); // Wait for the number of bytes to be transmitted
			fifo[i] = LPC_USART->RBR;
			xQueueSendToBack(xQueueInput, &fifo[i], 0);
			i++;

			for(j=0; j<fifo[1]; ++j) {
				while(!(LPC_USART->LSR & 0x01)); // Wait for each byte of the command
				fifo[i] = LPC_USART->RBR;
				xQueueSendToBack(xQueueInput, &fifo[i], 0);
				i++;
			}
		}
	}
}
