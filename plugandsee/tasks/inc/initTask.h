
#ifndef _INIT_
#define _INIT_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

//#define DBG_INIT 1

void initTask(void *pvParameters);

#endif /* _INIT_ */
