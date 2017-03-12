
#include "LPC13Uxx.h"

#include "gpio.h"
#include "uart.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "instantPowerTask.h"
#include "liveModeTask.h"
#include "majTimestampTask.h"
#include "commandsHandlerTask.h"
#include "dataReceiverTask.h"
#include "initTask.h"

#include "smartOutletConfig.h"

QueueHandle_t xQueueInput;
QueueHandle_t xQueueOutput;

uint32_t timestamp = 1444043772; // TBC - Must be synchronized by the application
uint32_t lastInstPowerValue = 0;

TaskHandle_t lMHandle = NULL;

SemaphoreHandle_t xSemaphore = NULL;
SemaphoreHandle_t xSemaphoreInstPower = NULL;
SemaphoreHandle_t xSemaphoreTimestamp = NULL;

uint8_t fanion = FANION;

int main(void) {
	SystemCoreClockUpdate();

	GPIOInit();
	UARTInit(9600);

	TaskHandle_t iHandle, cHHandle, dRHandle, mTHandle, iPHandle;

	xTaskCreate(initTask, "init", 100, NULL, (tskIDLE_PRIORITY + 2), &iHandle);
	xTaskCreate(commandsHandlerTask, "commandsHandler", 100, NULL, (tskIDLE_PRIORITY + 1), &cHHandle);
	xTaskCreate(dataReceiverTask, "dataReceiver", 100, NULL, (tskIDLE_PRIORITY + 1), &dRHandle);
	xTaskCreate(majTimestampTask, "majTimestamp", 100, NULL, (tskIDLE_PRIORITY + 1), &mTHandle);
	xTaskCreate(liveModeTask, "liveMode", 100, NULL, (tskIDLE_PRIORITY + 1), &lMHandle);
	xTaskCreate(instantPowerTask, "instantPower", 100, NULL, (tskIDLE_PRIORITY + 1), &iPHandle);

	if(iHandle != NULL && cHHandle != NULL && dRHandle != NULL && lMHandle != NULL) {
		vTaskStartScheduler();
		print_string("[adctest.c] - vTaskStartScheduler error\n");
	}
	else {
		print_string("[adctest.c] - handler error\n");
	}

	for(;;); // Should never reach here
}
