#include "pixy_queue.h"
#include "debug.h"

void create_queue()
{ 
    dbgOutputLoc(PIXY_QUEUE_CREATE_QUEUE_ENTER);
    
    pixyQ = xQueueCreate(QLENGTH, sizeof(int));
    if(pixyQ == NULL)
    {
        //Error: no queue created
        dbgError(QUEUE_CREATE_ERROR);
    }
    
    dbgOutputLoc(PIXY_QUEUE_CREATE_QUEUE_EXIT);
}

int q_pop()
{
    int temp;
    
    if(xQueueReceive(pixyQ, &temp, portMAX_DELAY) != pdTRUE)
    {
        //Error: no message received
        dbgError(QUEUE_POP_ERROR);
    }
    
    return temp;
}

void q_push(int m)
{
    if(xQueueSendFromISR(pixyQ, &m, pdFALSE) != pdTRUE)
    {
        //Error: no message sent; Queue may be full
        dbgError(QUEUE_PUSH_ERROR);
    }
}

unsigned int block_distance(unsigned char pixy_width, unsigned char pixy_height)
{
    int focal_length = 263;
    int actual_width = 3;
    int actual_height = 4;
    
    int distance_width = (actual_width * focal_length) / pixy_width;
    int distance_height = (actual_height * focal_length) / pixy_height;
    unsigned int actual_distance = (unsigned int) ((distance_width + distance_height) / 2);
    
    return actual_distance;
}

unsigned int dump_distance(unsigned char pixy_width, unsigned char pixy_height)
{
    int focal_length = 315;
    int actual_width = 22;
    int actual_height = 8;
    
    int distance_width = (actual_width * focal_length) / pixy_width;
    int distance_height = (actual_height * focal_length) / pixy_height;
    unsigned int actual_distance = (unsigned int) ((distance_width + distance_height) / 2);
    
    return actual_distance;
}