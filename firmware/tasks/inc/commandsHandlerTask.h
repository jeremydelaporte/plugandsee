
#ifndef _TASKCOMMANDSHANDLER_H_
#define _TASKCOMMANDSHANDLER_H_

//#include "uart.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
/*#include "semphr.h"



#include <string.h>

#include "lpc177x_8x_uart.h"


#define PERIOD				(500)*/
//#define DBG_CMDS_HANDLER 1

/*extern QueueHandle_t xQueueInput;
extern QueueHandle_t xQueueOutput;

extern uint32_t timestamp;
extern SemaphoreHandle_t mutTimestamp;*/

void commandsHandlerTask(void *pvParameters);

void relayOn(void);
void relayOff(void);
void relayStatus(void);

void tempInside(void);
/*
void majTimestamp(uint8_t *buff);*/

#endif /* _TASKCOMMANDSHANDLER_H_ */
