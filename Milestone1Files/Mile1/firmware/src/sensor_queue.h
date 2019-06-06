#ifndef SENSOR_QUEUE_H
#define	SENSOR_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"

QueueHandle_t xQ;

struct message
{
    int val;
};

void create_queue();
struct message q_pop(struct message m);
void q_push(struct message m);

#endif	/* SENSOR_QUEUE_H */