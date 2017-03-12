
#include "initTask.h"

#include "uart.h"
#include "gpio.h"


extern QueueHandle_t xQueueInput;
extern QueueHandle_t xQueueOutput;

extern SemaphoreHandle_t xSemaphore;
extern SemaphoreHandle_t xSemaphoreInstPower;
extern SemaphoreHandle_t xSemaphoreTimestamp;

void initTask(void *pvParameters) {
#ifdef DBG_INIT
	print_string("initTask task launched\r\n");
#endif

	xQueueInput = xQueueCreate(50, sizeof(uint8_t));
	xQueueOutput = xQueueCreate(10, sizeof(uint8_t));

	GPIOInit();
	GPIOSetDir(1, 13, 1); // TODO - Use of constants

	vSemaphoreCreateBinary(xSemaphore);
	vSemaphoreCreateBinary(xSemaphoreInstPower);
	vSemaphoreCreateBinary(xSemaphoreTimestamp);

#ifdef DBG_INIT
	if(xQueueInput == 0)
		print_string("xQueueInput = 0\r\n");
	else
		print_string("xQueueInput created\r\n");
#endif

#ifdef DBG_INIT
	if(xQueueOutput == 0)
		print_string("xQueueOutput = 0\r\n");
	else
		print_string("xQueueOutput created\r\n");
#endif

	vTaskSuspend(NULL);
	for(;;) {
	}
}
