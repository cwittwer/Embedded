#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"

void IntHandlerDrvUsartInstance0(void)
{
    dbgOutputLoc(ISR_ENTER);
      
    uint8_t receive_byte = 0x00;
    
    if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_4_RECEIVE))
    {   
        while(PLIB_USART_ReceiverDataIsAvailable(USART_ID_4))
        {
            receive_byte = PLIB_USART_ReceiverByteReceive(USART_ID_4);
            message push;
            push.val = receive_byte;            
            
            dbgOutputLoc(ISR_BEFORE_Q_TX);
            
            q_push(push);

            dbgOutputLoc(ISR_AFTER_Q_TX);
        }
        
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_RECEIVE);
    }
    else if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_4_TRANSMIT) && SYS_INT_SourceIsEnabled(INT_SOURCE_USART_4_TRANSMIT))
    {
        //error
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_TRANSMIT);
        dbgError(ISR_TRANSMIT_ERROR);
    }
    else if(SYS_INT_SourceStatusGet(INT_SOURCE_USART_4_ERROR))
    {
        SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_ERROR);
     //   dbgError(ISR_ERROR);
    }
    
    dbgOutputLoc(ISR_EXIT);
}
