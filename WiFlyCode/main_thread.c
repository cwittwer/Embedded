#include "main_thread.h"

void vTimerCallback( TimerHandle_t tHandle )
{
    main_message temp;
    strcpy(temp.mess, "get");
    temp.len = strlen(temp.mess);
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
    
    int i = 0;
    while(1)
    {
        dbgOutputLoc(MAIN_WHILE);
    }
}

