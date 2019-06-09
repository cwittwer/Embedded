#ifndef SENSOR_QUEUE_H
#define	SENSOR_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"

#define QLENGTH 10

QueueHandle_t xQ;

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