#ifndef MY_QUEUE_H
#define	MY_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

typedef struct
{
    unsigned int val;
    char unit[10];
} message;

#define QLENGTH 10

static QueueHandle_t xQ;

void create_queue();
message q_pop(message m);
void q_push(message m);

unsigned int block_distance(unsigned char pixy_width, unsigned char pixy_height);

#endif	/* MY_QUEUE_H */