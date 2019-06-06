#include "sensor_queue.h"
#include "debug.h"

void create_queue()
{
    xQ = xQueueCreate(10, sizeof(struct message));
    if(xQ == NULL)
        //Error: no queue created
        dbgOutputLoc(ERROR_CODE);
}

struct message q_pop(struct message m)
{
    if(xQueueReceive(xQ, &m, portMAX_DELAY) != pdTRUE)
        //Error: no message received
        dbgOutputLoc(ERROR_CODE);
    
    return m;
}

void q_push(struct message m)
{
    if(xQueueSendFromISR(xQ, &m, pdFALSE) != pdTRUE)
        //Error: no message sent
        dbgOutputLoc(ERROR_CODE);
}

void ISRSendMsgToQueue(void* msg, portBASE_TYPE* pxHigherPriorityTaskToken)
{
    dbgOutputLoc(ISR_ENTER);
    
    if(xQueueSendToBackFromISR(xQ, msg, pxHigherPriorityToken) != pdPASS)
        dbgOutputLoc(ERROR_CODE);
    else
    {
    
        dbgOutputLoc(ISR_BEFORE_Q_TX);

        //sent to queue

        dbgOutputLoc(ISR_AFTER_Q_TX);
    }
    
    dbgOutputLoc(ISR_EXIT);
}