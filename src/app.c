#include "app.h"

void APP_Initialize ( void )
{
    create_queue();
    initPorts();
       
    SYS_INT_SourceDisable(INT_SOURCE_USART_1_TRANSMIT);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_RECEIVE);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_ERROR);
    
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_RECEIVE);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_TRANSMIT);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_ERROR);
    
    /*PLIB_USART_BaudRateSet(USART_ID_1, SYS_CLK_PeripheralFrequencyGet(CLK_BUS_PERIPHERAL_1), 9600);
    PLIB_USART_Enable(USART_ID_1);
    PLIB_USART_ReceiverEnable(USART_ID_1);*/
}

void APP_Tasks ( void )
{
    dbgOutputLoc(APP_ENTER);
    
    state_values val;
    val.state = INITIAL;
    
    dbgOutputLoc(APP_WHILE);
    
    while(1)
    {
        dbgOutputVal(0x11);
        
        PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, 3);
        
        //pop from queue and send data to server
        message pop;
        
        dbgOutputLoc(APP_BEFORE_Q_RX);
        
        pop = q_pop(pop);
        
        dbgOutputLoc(APP_AFTER_Q_RX);
        
        val.new_byte = pop.val;
        val = pixy_state(val);
    }
}