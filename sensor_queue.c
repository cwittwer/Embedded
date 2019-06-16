#include "sensor_queue.h"

void create_queue()
{
    dbgOutputLoc(SENSOR_QUEUE_CREATE_QUEUE_ENTER);
    
    xQ = xQueueCreate(QLENGTH, sizeof(message));
    if(xQ == NULL)
        dbgError("Queue Creation Error");//Error: no queue created
    
    dbgOutputLoc(SENSOR_QUEUE_CREATE_QUEUE_EXIT);
}

message q_pop(message m)
{  
    if(xQueueReceive(xQ, &m, portMAX_DELAY) != pdTRUE)
        dbgError("No message received");//Error: no message received
    
    return m;
}

void q_push(message m, BaseType_t * pxHigherPriorityTaskWoken)
{
    if(xQueueSendFromISR(xQ, &m, pxHigherPriorityTaskWoken) != pdTRUE)
        dbgError("No message sent"); //Error: no message sent; Queue may be full
}

message ADCConverter(unsigned int data)
{
    dbgOutputLoc(SENSOR_QUEUE_ADC_CONVERTER_ENTER);
    
    unsigned int distance = lookupTable[data >> 3];//Reduce 1024 options down to 128
    message mess = {distance, {'c','e','n','t','i','m','e','t','e','r'}};
    
    dbgOutputLoc(SENSOR_QUEUE_ADC_CONVERTER_EXIT);
    
    return mess;
}