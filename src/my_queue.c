#include "my_queue.h"
#include "debug.h"

void create_queue()
{ 
    dbgOutputLoc(MY_QUEUE_CREATE_QUEUE_ENTER);
    
    xQ = xQueueCreate(QLENGTH, sizeof(message));
    if(xQ == NULL)
    {
        //Error: no queue created
        dbgError(QUEUE_CREATE_ERROR);
    }
    
    dbgOutputLoc(MY_QUEUE_CREATE_QUEUE_EXIT);
}

message q_pop(message m)
{
    if(xQueueReceive(xQ, &m, portMAX_DELAY) != pdTRUE)
    {
        //Error: no message received
        dbgError(QUEUE_POP_ERROR);
    }
    
    return m;
}

void q_push(message m)
{
    if(xQueueSendFromISR(xQ, &m, pdFALSE) != pdTRUE)
    {
        //Error: no message sent; Queue may be full
        dbgError(QUEUE_PUSH_ERROR);
    }
}

unsigned int block_distance(unsigned char pixy_width, unsigned char pixy_height)
{
    int focal_length = 375;
    int actual_width = 3;
    int actual_height = 4;
    
    int distance_width = (actual_width * focal_length) / pixy_width;
    int distance_height = (actual_height * focal_length) / pixy_height;
    unsigned int actual_distance = (unsigned int) ((distance_width + distance_height) / 2);
    
    return actual_distance;
}