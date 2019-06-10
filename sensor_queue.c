#include "sensor_queue.h"
#include "debug.h"

void create_queue()
{
    dbgOutputLoc(SENSOR_QUEUE_CREATE_QUEUE_ENTER);
    
    xQ = xQueueCreate(QLENGTH, sizeof(message));
    if(xQ == NULL)
    {
        //Error: no queue created
        dbgError();
    }
    
    dbgOutputLoc(SENSOR_QUEUE_CREATE_QUEUE_EXIT);
}

message q_pop(message m)
{
    dbgOutputLoc(SENSOR_QUEUE_Q_POP_ENTER);
    
    if(xQueueReceive(xQ, &m, portMAX_DELAY) != pdTRUE)
    {
        //Error: no message received
        dbgError();
    }
    
    dbgOutputLoc(SENSOR_QUEUE_Q_POP_EXIT);
    
    return m;
}

void q_push(message m)
{
    dbgOutputLoc(SENSOR_QUEUE_Q_PUSH_ENTER);
    
    if(xQueueSendFromISR(xQ, &m, pdFALSE) != pdTRUE)
    {
        //Error: no message sent; Queue may be full
        dbgError();
    }
    
    dbgOutputLoc(SENSOR_QUEUE_Q_PUSH_EXIT);
}

message ADCConverter(unsigned int data)
{
    dbgOutputLoc(SENSOR_QUEUE_ADC_CONVERTER_ENTER);
    
    unsigned int distance;
    distance = lookupTable[data >> 3];
    message mess = {distance, {'c','e','n','t','i','m','e','t','e','r'}};
    
    dbgOutputLoc(SENSOR_QUEUE_ADC_CONVERTER_EXIT);
    
    return mess;
}