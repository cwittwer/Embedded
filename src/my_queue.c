#include "my_queue.h"
#include "debug.h"

void create_queue()
{ 
    dbgOutputLoc(MY_QUEUE_CREATE_QUEUE_ENTER);
    
    xQ = xQueueCreate(QLENGTH, sizeof(message));
    if(xQ == NULL)
    {
        //Error: no queue created
        dbgError();
    }
    
    dbgOutputLoc(MY_QUEUE_CREATE_QUEUE_EXIT);
}

message q_pop(message m)
{
    if(xQueueReceive(xQ, &m, portMAX_DELAY) != pdTRUE)
    {
        //Error: no message received
        dbgError();
    }
    
    return m;
}

void q_push(message m)
{
    if(xQueueSendFromISR(xQ, &m, pdFALSE) != pdTRUE)
    {
        //Error: no message sent; Queue may be full
        dbgError();
    }
}

short combine_bytes(char first_byte, char second_byte)
{
    return (((short) second_byte << 8) | first_byte);
}

int block_distance(short width, short height)
{
    return 0;
}