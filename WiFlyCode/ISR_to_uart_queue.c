#include "ISR_to_uart_queue.h"

void create_ISR_to_uart_queue()
{
    ISR_to_uart_handle = xQueueCreate(ISR_TO_UART_QLENGTH, sizeof(char));
    if(ISR_to_uart_handle == NULL)
        dbgError(QUEUE_CREATION_ERROR);//Error: no queue created
    
    dbgOutputLoc(ISR_TO_UART_QUEUE_CREATED);
}

char ISR_to_uart_pop()
{  
    char temp;
    
    if(xQueueReceive(ISR_to_uart_handle, &temp, portMAX_DELAY) != pdTRUE)
        dbgError(QUEUE_RECEIVE_ERROR);//Error: no message received
    
    dbgOutputLoc(ISR_TO_UART_POP);
    
    return temp;
}

void ISR_to_uart_push(char m, BaseType_t * const pxHigherPriorityTaskWoken)
{
    if(xQueueSendFromISR(ISR_to_uart_handle, &m, pxHigherPriorityTaskWoken) != pdTRUE)
        dbgError(QUEUE_SEND_ERROR); //Error: no message sent; Queue may be full
    
    dbgOutputLoc(ISR_TO_UART_PUSH);
}

unsigned int ISR_to_uart_waiting()
{
    return uxQueueMessagesWaiting(ISR_to_uart_handle);
}