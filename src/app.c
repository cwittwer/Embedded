#include "app.h"

void APP_Initialize ( void )
{
    create_queue();
    initPorts();
       
    SYS_INT_SourceDisable(INT_SOURCE_USART_4_TRANSMIT);
    SYS_INT_SourceEnable(INT_SOURCE_USART_4_RECEIVE);
    SYS_INT_SourceEnable(INT_SOURCE_USART_4_ERROR);
    
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_RECEIVE);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_TRANSMIT);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_ERROR);
}

void APP_Tasks ( void )
{
    dbgOutputLoc(APP_ENTER);
    
    state_values data;
    data.state = INITIAL;
    data.saved_byte = 0x00;
    data.new_byte = 0x00;
    data.pixel_width = 0;
    data.pixel_height = 0;
    data.distance = 0;
    
    int total_distance = 0;
    int avg_distance = 0;
    int count = 0;
    
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
        
//        dbgOutputVal(pop.val);
        
        data.new_byte = pop.val;
        data = pixy_state(data);
        
        if(data.distance != 0)
        {
            total_distance = total_distance + data.distance;
            data.distance = 0;
            
            count = count + 1;
        }
        
        if(count == 5)
        {
            dbgOutputLoc(APP_SEND_DISTANCE);
            avg_distance = total_distance / 5;
            total_distance = 0;
            count = 0;
            
            dbgOutputVal(avg_distance);
            
            //send distance to arm rover
        }
    }
}