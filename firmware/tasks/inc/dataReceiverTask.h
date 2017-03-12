
#ifndef _DATARECEIVER_
#define _DATARECEIVER_

//#include "uart.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

//#define DBG_DATA_RECEIVER 0

void dataReceiverTask(void *pvParameters);

#endif /* _DATARECEIVER_ */
