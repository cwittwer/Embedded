#ifndef SENSOR_QUEUE_H
#define	SENSOR_QUEUE_H

#include "queue.h"

QueueHandle_t xQ;

struct message
{
    int val;
};

void create_queue();
void q_pop(message &m);
void q_push(message &m);

#endif	/* SENSOR_QUEUE_H */