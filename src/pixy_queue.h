#ifndef PIXY_QUEUE_H
#define	PIXY_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

#define QLENGTH 10

static QueueHandle_t pixyQ;

void create_queue();
int q_pop();
void q_push(int m);

unsigned int block_distance(unsigned char pixy_width, unsigned char pixy_height);
unsigned int dump_distance(unsigned char pixy_width, unsigned char pixy_height);

#endif	/* MY_QUEUE_H */