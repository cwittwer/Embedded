#include "main_thread.h"
#include "parser.h"

static bool getRequest = true;
static bool sendData = false;

void vTimerCallback( TimerHandle_t tHandle )
{
    main_message temp;
    strcpy(temp.mess, "{\"title\" : \"state\", \"value\" : \"7\"}");
    temp.get = getRequest;
    if(sendData)
        getRequest = !getRequest;
    main_to_uart_push(temp);
    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, 3);
}

//length, message number

void MAIN_THREAD_Initialize ( void )
{
    initPorts();
    
    create_main_to_uart_queue();
    create_uart_to_main_queue();
    
    //Software timer initialization
    xTimer = xTimerCreate(
            "WiFly Timer",
            pdMS_TO_TICKS(TIMER_PERIOD),
            pdTRUE,
            (void *) 1,
            vTimerCallback
            );
    
    xTimerStart(xTimer, 0);
    
    dbgOutputLoc(MAIN_INITIALIZED);
}

void MAIN_THREAD_Tasks ( void )
{
    dbgOutputLoc(MAIN_ENTER);
    //some struct that holds the send/receive message
    
    while(1)
    {
        dbgOutputLoc(MAIN_WHILE);
        
        main_response res = uart_to_main_pop();
        
        parsed_data data = json_parser(res.mess);
        
        if(strcmp(data.parsed_title, "state")){
            if(strcmp(data.parsed_value, "next"))
                sendData = true;
        }
    }
}

