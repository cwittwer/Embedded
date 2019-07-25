#include "uart_to_main_queue.h"

void create_uart_to_main_queue()
{
    uart_to_main_handle = xQueueCreate(UART_TO_MAIN_QLENGTH, sizeof(main_response));
    if(uart_to_main_handle == NULL)
        dbgError(QUEUE_CREATION_ERROR);//Error: no queue created
    
    dbgOutputLoc(UART_TO_MAIN_QUEUE_CREATED);
}

main_response uart_to_main_pop()
{  
    main_response temp;
    
    if(xQueueReceive(uart_to_main_handle, &temp, portMAX_DELAY) != pdTRUE)
        //dbgError(QUEUE_RECEIVE_ERROR);//Error: no message received
    
    dbgOutputLoc(UART_TO_MAIN_POP);
    
    return temp;
}

void uart_to_main_push(main_response m)
{
    if(xQueueSend(uart_to_main_handle, &m, portMAX_DELAY) != pdTRUE)
        dbgError(QUEUE_SEND_ERROR); //Error: no message sent; Queue may be full
    
    dbgOutputLoc(UART_TO_MAIN_PUSH);
}

unsigned int uart_to_main_waiting()
{
    return uxQueueMessagesWaiting(uart_to_main_handle);
}
