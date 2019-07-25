#include "system/common/sys_common.h"
#include "pixy_thread.h"
#include "uart_send_thread.h"
#include "uart_receive_thread.h"
#include "system_definitions.h"

void IntHandlerDrvUsartInstance0(void)
{
     dbgOutputLoc(UART_ISR_ENTER);
    
    BaseType_t pxHigherPriorityTaskWoken = pdFALSE;
    char pop;
    
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_1_TRANSMIT) && SYS_INT_SourceIsEnabled(INT_SOURCE_USART_1_TRANSMIT))
    {
        dbgOutputLoc(UART_ISR_SEND);
        
        if(!PLIB_USART_TransmitterBufferIsFull(USART_ID_1)){
            pop = uart_to_ISR_pop(&pxHigherPriorityTaskWoken);
            if(pop != NULL)
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
            ISR_to_uart_push(PLIB_USART_ReceiverByteReceive(USART_ID_1), &pxHigherPriorityTaskWoken);
                
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

void IntHandlerDrvUsartInstance1(void)
{
    dbgOutputLoc(PIXY_ISR_ENTER);
      
    uint8_t receive_byte = 0x00;
    
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_4_RECEIVE))
    {   
        while(PLIB_USART_ReceiverDataIsAvailable(USART_ID_4))
        {
            receive_byte = PLIB_USART_ReceiverByteReceive(USART_ID_4);
            int push;
            push = receive_byte;            
            
            dbgOutputLoc(PIXY_ISR_BEFORE_Q_TX);
            
            q_push(push);

            dbgOutputLoc(PIXY_ISR_AFTER_Q_TX);
        }
        
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_RECEIVE);
    }
    else if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_4_TRANSMIT) && SYS_INT_SourceIsEnabled(INT_SOURCE_USART_4_TRANSMIT))
    {
        //error
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_TRANSMIT);
        dbgError(PIXY_ISR_TRANSMIT_ERROR);
    }
    else if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_4_ERROR))
    {
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_ERROR);
     //   dbgError(ISR_ERROR);
    }
    
    dbgOutputLoc(PIXY_ISR_EXIT);
}