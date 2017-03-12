
#include "liveModeTask.h"
#include "smartOutletConfig.h"

#include "uart.h"

#include <stdio.h>
#include <string.h>

extern uint8_t fanion;

extern SemaphoreHandle_t xSemaphore;
extern SemaphoreHandle_t xSemaphoreInstPower;
extern SemaphoreHandle_t xSemaphoreTimestamp;

extern uint32_t lastInstPowerValue;
extern uint32_t timestamp;

uint8_t trame[50];

void sendTrame(uint8_t *trame) {
	uint8_t length;

	UARTSend(&fanion, 1);
	length = strlen((char *)trame)-1; // We do not take into account the '\n' in our protocol
	UARTSend(&length, 1);
	print_string(trame);
}

void liveModeTask(void *pvParameters) {
#ifdef DBG_LIVE_MODE_TASK
	print_string("liveModeTask task launched\r\n");
#endif

	float tempMock = 30.2; // To be removed
	uint32_t energyMock = 12; // To be removed

	uint32_t InstPowerToSend=0;
	uint32_t timestampToSend=0;

	vTaskSuspend(NULL);

	for(;;) {
		vTaskDelay(2000/portTICK_PERIOD_MS);

		if(xSemaphore != NULL) {
			if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {

				if(xSemaphoreInstPower != NULL) {
					if(xSemaphoreTake(xSemaphoreInstPower, portMAX_DELAY) == pdTRUE) {
						InstPowerToSend = lastInstPowerValue;
						xSemaphoreGive(xSemaphoreInstPower);

						if(xSemaphoreTimestamp != NULL) {
							if(xSemaphoreTake(xSemaphoreTimestamp, portMAX_DELAY) == pdTRUE) {
								timestampToSend = timestamp;
								xSemaphoreGive(xSemaphoreTimestamp);

								memset(trame, 0x00, 50);
								snprintf((char *)trame, 50, "live mode p %u %u\n", (unsigned int)timestampToSend, (unsigned int)InstPowerToSend);
								sendTrame(trame);

								memset(trame, 0x00, 50);
								snprintf((char *)trame, 50, "live mode t %u 29.4\n", (unsigned int)timestampToSend);
								sendTrame(trame);

								memset(trame, 0x00, 50);
								snprintf((char *)trame, 50, "live mode e %u %u\n", (unsigned int)timestampToSend, (unsigned int)energyMock);
								sendTrame(trame);

								//tempMock += 1.0;
								energyMock++;
							}
						}
					}
				}
				xSemaphoreGive(xSemaphore);
			}
		}
	}
}
