#include "uart_to_ISR_queue.h"

void create_uart_to_ISR_queue()
{
    uart_to_ISR_handle = xQueueCreate(UART_TO_ISR_QLENGTH, sizeof(char));
    if(uart_to_ISR_handle == NULL)
        dbgError(QUEUE_CREATION_ERROR);//Error: no queue created
    
    dbgOutputLoc(UART_TO_ISR_QUEUE_CREATED);
}

char uart_to_ISR_pop(BaseType_t * const pxHigherPriorityTaskWoken)
{  
    char temp;
    
    if(xQueueReceiveFromISR(uart_to_ISR_handle, &temp, pxHigherPriorityTaskWoken) != pdTRUE)
        dbgError(QUEUE_RECEIVE_ERROR);//Error: no message received
    
    dbgOutputLoc(UART_TO_ISR_POP);
    
    return temp;
}

void uart_to_ISR_push(char m)
{
    if(xQueueSend(uart_to_ISR_handle, &m, portMAX_DELAY) != pdTRUE)
        dbgError(QUEUE_SEND_ERROR); //Error: no message sent; Queue may be full
    
    dbgOutputLoc(UART_TO_ISR_PUSH);
}

unsigned int uart_to_ISR_waiting()
{
    return uxQueueMessagesWaiting(uart_to_ISR_handle);
}