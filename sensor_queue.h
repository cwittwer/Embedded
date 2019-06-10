#ifndef SENSOR_QUEUE_H
#define	SENSOR_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"

#define QLENGTH 10

QueueHandle_t xQ;

static unsigned int lookupTable[128] = {4709,2063,1273,904,693,558,464,396,344,304,271,244,222,203,187,174,162,151,141,133,126,119,113,107,102,97,93,89,86,82,79,76,73,71,68,66,64,62,60,58,57,55,54,52,51,49,48,47,46,45,44,43,42,41,40,39,38,37,37,36,35,35,34,33,33,32,32,31,30,30,29,29,28,28,28,27,27,26,26,26,25,25,24,24,24,23,23,23,23,22,22,22,21,21,21,21,20,20,20,20,19,19,19,19,18,18,18,18,18,17,17,17,17,17,17,16,16,16,16,16,16,15,15,15,15,15,15,15};

typedef struct{
    unsigned int val;
    char unit[10];
} message;

void create_queue();
message q_pop(message m);
void q_push(message m);

//Function to transform raw sensor data to meaningful units
message ADCConverter(unsigned int);

#endif	/* SENSOR_QUEUE_H */