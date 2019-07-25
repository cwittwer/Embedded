#include "pixy_thread.h"
#include "parser.h"

int state = 0;

void vTimerCallbackSend( TimerHandle_t tHandle )
{
    dbgOutputLoc(SOFTWARE_TIMER);
    if(state == 0)
    {
        main_message temp;
        temp.get = true;
        main_to_uart_push(temp);
    }
    
    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, 3);
}

void vTimerCallbackParse( TimerHandle_t tHandle )
{
    if(state == 0)
    {
        main_response res = uart_to_main_pop();
        parsed_data state_data = json_parser(res.mess);

        if(strcmp(state_data.parsed_title, "state") == 0)
        {
             if(strcmp(state_data.parsed_value, "pr_search") == 0)
                state = 1;
            else
                state = 0;
        }
    }
}

void PIXY_THREAD_Initialize ( void )
{
    create_queue();
    create_main_to_uart_queue();
    create_uart_to_main_queue();
    initPorts();
    
     xTimerSend = xTimerCreate(
            "Send Timer",
            pdMS_TO_TICKS(TIMER_PERIOD),
            pdTRUE,
            (void *) 1,
            vTimerCallbackSend
            );
    
    xTimerStart(xTimerSend, 0);
    
    xTimerParse = xTimerCreate(
            "Parse Timer",
            pdMS_TO_TICKS(1100),
            pdTRUE,
            (void *) 1,
            vTimerCallbackParse
            );
    
    xTimerStart(xTimerParse, 0);
       
    SYS_INT_SourceDisable(INT_SOURCE_USART_4_TRANSMIT);
    SYS_INT_SourceEnable(INT_SOURCE_USART_4_RECEIVE);
    SYS_INT_SourceEnable(INT_SOURCE_USART_4_ERROR);
    
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_RECEIVE);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_TRANSMIT);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_4_ERROR);
    
    dbgOutputLoc(PIXY_INITIALIZED);
}

void PIXY_THREAD_Tasks ( void )
{
    dbgOutputLoc(PIXY_THREAD_ENTER);
    
    state_values data;
    data.state = INITIAL;
    data.saved_byte = 0x00;
    data.new_byte = 0x00;
    data.pixel_width = 0;
    data.pixel_height = 0;
    data.signature = 0x00;
    data.distance = 0;
    
    int total_distance = 0;
    int avg_distance = 0;
    int count = 0;
    
    dbgOutputLoc(PIXY_THREAD_WHILE);
    
    while(1)
    {     
        dbgOutputLoc(PIXY_THREAD_BEFORE_Q_RX);

        int pop = q_pop();

        dbgOutputLoc(PIXY_THREAD_AFTER_Q_RX);
        
        if(state == 1)
        {
            dbgOutputVal(220);
            data.new_byte = pop;
            data = pixy_state(data);

            if(data.distance != 0)
            {
                total_distance = total_distance + data.distance;
                data.distance = 0;

                count = count + 1;
                dbgOutputVal(230);
            }    

            dbgOutputVal(240);
            if(count == 5)
            {
                dbgOutputVal(250);
                dbgOutputLoc(PIXY_THREAD_SEND_DISTANCE);
                avg_distance = total_distance / 5;
                total_distance = 0;
                count = 0;
                
                state = 0;
                
                main_message temp;
                strcpy(temp.mess, "{\"title\" : \"state\", \"value\" : \"pickup\"}");
                temp.get = false;
                main_to_uart_push(temp);

                dbgOutputVal(avg_distance);
                   //send distance to arm rover
            }
                
                
        }
       
    }
}