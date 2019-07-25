#include "main_to_uart_queue.h"

void create_main_to_uart_queue()
{
    main_to_uart_handle = xQueueCreate(MAIN_TO_UART_QLENGTH, sizeof(main_message));
    if(main_to_uart_handle == NULL)
        dbgError(QUEUE_CREATION_ERROR);//Error: no queue created
    
    dbgOutputLoc(MAIN_TO_UART_QUEUE_CREATED);
}

main_message main_to_uart_pop()
{  
    main_message temp;
    
    if(xQueueReceive(main_to_uart_handle, &temp, portMAX_DELAY) != pdTRUE)
        dbgError(QUEUE_RECEIVE_ERROR);//Error: no message received
    
    dbgOutputLoc(MAIN_TO_UART_POP);
    
    return temp;
}

void main_to_uart_push(main_message m)
{
    if(xQueueSend(main_to_uart_handle, &m, portMAX_DELAY) != pdTRUE)
        dbgError(QUEUE_SEND_ERROR); //Error: no message sent; Queue may be full
    
    dbgOutputLoc(MAIN_TO_UART_PUSH);
}

unsigned int main_send_q_waiting()
{
    return uxQueueMessagesWaiting(main_to_uart_handle);
}