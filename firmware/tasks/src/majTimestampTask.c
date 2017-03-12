
#include "majTimestampTask.h"

extern uint32_t timestamp;
extern SemaphoreHandle_t xSemaphoreTimestamp;

void majTimestampTask(void *pvParameters) {
#ifdef DBG_MAJ_TIMESTAMP_TASK
	print_string("majTimestampTask task launched\r\n");
#endif

	for(;;) {
		vTaskDelay(1000/portTICK_PERIOD_MS);
		if(xSemaphoreTimestamp != NULL) {
			if(xSemaphoreTake(xSemaphoreTimestamp, portMAX_DELAY) == pdTRUE) {
				timestamp++;
				xSemaphoreGive(xSemaphoreTimestamp);
			}
		}
	}
}
