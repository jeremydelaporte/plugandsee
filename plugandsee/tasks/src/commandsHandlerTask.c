
#include "commandsHandlerTask.h"
#include "smartOutletConfig.h"

#include "type.h"
#include "uart.h"
#include "gpio.h"

#include "LPC13Uxx.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t buffCommandsHandler[64];
uint8_t iBuff;

extern QueueHandle_t xQueueInput;
extern QueueHandle_t xQueueOutput;

extern TaskHandle_t lMHandle;
extern SemaphoreHandle_t xSemaphore;

void commandsHandlerTask(void *pvParameters) {
#ifdef DBG_CMDS_HANDLER
	print_string("commandsHandlerTask task launched\r\n");
#endif

	uint8_t nbBytes;

	for(;;) {
		vTaskDelay((200/portTICK_PERIOD_MS));

		if(xQueueInput != 0) { // xQueueInput MUST be valid
			if(uxQueueMessagesWaiting(xQueueInput) > 0) {
				memset((void *)buffCommandsHandler, '\0', sizeof(buffCommandsHandler));
				iBuff = 0;

				xQueueReceive(xQueueInput, &nbBytes, (TickType_t) 0);

				do{
					if(uxQueueMessagesWaiting(xQueueInput) > 0) {
						xQueueReceive(xQueueInput, &buffCommandsHandler[iBuff], (TickType_t) 0);
						iBuff += 1;
					}
				}while(iBuff != nbBytes);

				if(strcmp((const char *)buffCommandsHandler, "relay on") == 0){
					relayOn();
				}else if(strcmp((const char *)buffCommandsHandler, "relay off") == 0){
					relayOff();
				}else if(strcmp((const char *)buffCommandsHandler, "relay status") == 0){
					relayStatus();
				}else if(strcmp((const char *)buffCommandsHandler, "live mode") == 0){
					if(lMHandle != NULL) {
						vTaskResume(lMHandle);
					}
				}
			}
		} else {
#ifdef DBG_CMDS_HANDLER
			print_string("xQueueInput = 0\r\n");
#endif
		}
	}
}

// TODO - Add a physical relay
void relayOn(void) {
	uint32_t status;

	uint8_t fanion = FANION;
	uint8_t length;

	GPIOSetBitValue(RELAY_PORT_NUM, RELAY_BIT_VALUE, ON);
	status = GPIOGetPinValue(RELAY_PORT_NUM, RELAY_BIT_VALUE);

	if(xSemaphore != NULL) {
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
		UARTSend(&fanion, 1);
		if(status == ON) {
			length = strlen(RELAYONOK)-1;
			UARTSend(&length, 1);
			print_string(RELAYONOK);
		}
		else {
			length = strlen(RELAYONNOK)-1;
			UARTSend(&length, 1);
			print_string(RELAYONNOK);
		}
		xSemaphoreGive(xSemaphore);
	}
}

void relayOff(void) {
	uint32_t status;

	uint8_t fanion = FANION;
	uint8_t length;

	GPIOSetBitValue(RELAY_PORT_NUM, RELAY_BIT_VALUE, OFF);
	status = GPIOGetPinValue(RELAY_PORT_NUM, RELAY_BIT_VALUE);
	if(xSemaphore != NULL) {
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
		UARTSend(&fanion, 1);
		if(status == OFF) {
			length = strlen(RELAYOFFOK)-1;
			UARTSend(&length, 1);
			print_string(RELAYOFFOK);
		}
		else {
			length = strlen(RELAYOFFNOK)-1;
			UARTSend(&length, 1);
			print_string(RELAYOFFNOK);
		}
		xSemaphoreGive(xSemaphore);
	}
}

void relayStatus(void) {
	uint32_t status;

	uint8_t fanion = FANION;
	uint8_t length;

	status = GPIOGetPinValue(RELAY_PORT_NUM, RELAY_BIT_VALUE);

	if(xSemaphore != NULL) {
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
		UARTSend(&fanion, 1);
		if(status == OFF) {
			length = strlen(RELAYSTATUSOFF)-1;
			UARTSend(&length, 1);
			print_string(RELAYSTATUSOFF);
		} else {
			length = strlen(RELAYSTATUSON)-1;
			UARTSend(&length, 1);
			print_string(RELAYSTATUSON);
		}
		xSemaphoreGive(xSemaphore);
	}
}

// TODO - Add a physical temperature sensor
void tempInside(void) {
	uint8_t fanion = FANION;
	uint8_t length;

	UARTSend(&fanion, 1);

	length = strlen(TEMPINSIDE_MOCK)-1;
	UARTSend(&length, 1);

	print_string(TEMPINSIDE_MOCK);
}

/*void majTimestamp(uint8_t *buff) {
	if(mutTimestamp != NULL) {
		if(xSemaphoreTake(mutTimestamp, (TickType_t) 10) == pdTRUE) {
			timestamp = atoi(&buff[15]);
			xSemaphoreGive(mutTimestamp);
			xQueueSend(xQueueOutput, "maj timestamp - ok\r\n", (TickType_t) 10);
		}
	}else {
		xQueueSend(xQueueOutput, "maj timestamp - nok\r\n", (TickType_t) 10);
	}
}
*/
