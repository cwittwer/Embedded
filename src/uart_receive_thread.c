#include "uart_receive_thread.h"
#include "system/int/sys_int.h"

void UART_RECEIVE_THREAD_Initialize ( void )
{
    //DRV_USART0_Initialize();
    create_ISR_to_uart_queue();
    create_uart_to_main_queue();
    
    //usart initialize
    SYS_INT_SourceDisable(INT_SOURCE_USART_1_TRANSMIT);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_RECEIVE);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_ERROR);
    
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_TRANSMIT);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_RECEIVE);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_ERROR);
    
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, 0x0FF);
    
    dbgOutputLoc(UART_RECEIVE_INITIALIZED);
}

void UART_RECEIVE_THREAD_Tasks ( void )
{
    dbgOutputLoc(UART_RECEIVE_ENTER);
    
    char str[40];
    int index = 0;
    
    while(1)
    {
        dbgOutputLoc(UART_RECEIVE_WHILE);
        str[0] = ISR_to_uart_pop();
        if(str[0] == '{'){      //Start reading the chars as a response
            index = 0;
            while(str[index] != '}'){
                ++index;
                str[index] = ISR_to_uart_pop();
            }                   //Send the response back to the main thread
            str[index+1] = '\0';
            main_response res;
            res.len = index;
            strcpy(res.mess, str);
            uart_to_main_push(res);
        }
    }
}