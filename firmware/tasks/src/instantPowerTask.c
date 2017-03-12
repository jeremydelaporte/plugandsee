
#include "instantPowerTask.h"
#include "smartOutletConfig.h"

#include "adc.h"

static uint32_t instPower=0;
static uint32_t instPowerTmp=0;
static uint8_t i=0;

extern SemaphoreHandle_t xSemaphoreInstPower;
extern uint32_t lastInstPowerValue;

void instantPowerTask(void *pvParameters) {
#ifdef DBG_INSTANT_POWER_TASK
	print_string("instantPowerTask task launched\r\n");
#endif
	ADCInit(15);

	for(;;) {
		vTaskDelay(1/portTICK_PERIOD_MS);

		if(i < 20) {
			instPowerTmp = ADCRead(ACS712);
			//instPowerTmp = (float)(ADCRead(ACS712)*3.3)/4095; // We first convert in Volts
			if(instPowerTmp > instPower) {
				instPower = instPowerTmp;
			}
			i++;
		} else {
			//instPower = (((instPower*5)/2.8542)/1.4142); // Now, we convert in A rms
			if(xSemaphoreInstPower != NULL) {
				if(xSemaphoreTake(xSemaphoreInstPower, portMAX_DELAY) == pdTRUE) {
					//lastInstPowerValue = (uint32_t)instPower*230;
					lastInstPowerValue = instPower+1;
					xSemaphoreGive(xSemaphoreInstPower);
				}
			}
			i = 0;
			instPower = 0;
		}
	}
}
