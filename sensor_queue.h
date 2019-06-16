#ifndef SENSOR_QUEUE_H
#define	SENSOR_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

typedef struct{
    unsigned int val;
    char unit[10];
} message;

#define QLENGTH 10

static QueueHandle_t xQ;

static unsigned int lookupTable[128] = {4589,1963,1183,814,613,488,419,352,311,272,240,214,193,175,160,149,139,129,120,113,108,102,98,93,90,86,84,81,80,77,75,72,70,68,66,64,63,61,60,58,57,55,54,52,51,49,48,47,46,45,44,43,42,41,40,39,38,37,37,36,35,35,34,33,33,32,32,31,30,30,29,29,28,28,28,27,27,26,26,26,25,25,24,24,24,23,23,23,23,22,22,22,21,21,21,21,20,20,20,20,19,19,19,19,18,18,18,18,18,17,17,17,17,17,17,16,16,16,16,16,16,15,15,15,15,15,15,15};

void create_queue();
message q_pop(message m);
void q_push(message m, BaseType_t * pxHigherPriorityTaskWoken);

//Function to transform raw sensor data to meaningful units
message ADCConverter(unsigned int);

#endif	/* SENSOR_QUEUE_H */