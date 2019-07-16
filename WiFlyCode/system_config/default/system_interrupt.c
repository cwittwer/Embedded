#include "system/common/sys_common.h"
#include "uart_send_thread.h"
#include "system_definitions.h"

//char *msg_ptr = "#";
//send_message temp;

void IntHandlerDrvUsartInstance0(void)
{
    dbgOutputLoc(UART_ISR_ENTER);
    
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_TRANSMIT))
    {
        dbgOutputLoc(UART_ISR_SEND);

        char pop = uart_to_ISR_pop(pxHigherPriorityTaskWoken);
        
        if(!PLIB_USART_TransmitterBufferIsFull(USART_ID_1)){
            PLIB_USART_TransmitterByteSend(USART_ID_1, pop);
            SYS_INT_SourceDisable(INT_SOURCE_USART_1_TRANSMIT);
            SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_TRANSMIT);
        }
    }
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_RECEIVE))
    {
        dbgOutputLoc(UART_ISR_RECEIVE);
        
        //while theres something in the receive, read/push a byte
        while(PLIB_USART_ReceiverDataIsAvailable(USART_ID_1))
        {
            char c = PLIB_USART_ReceiverByteReceive(USART_ID_1);
        }
                
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_RECEIVE);
    }
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_ERROR))
    {
        dbgOutputLoc(UART_ISR_ERROR);
        
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_ERROR);
    }
    
    portEND_SWITCHING_ISR(pxHigherPriorityTaskWoken);
    
    dbgOutputLoc(UART_ISR_EXIT);
}
