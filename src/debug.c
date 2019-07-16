#include "debug.h"

void initPorts()
{
    dbgOutputLoc(INIT_PORTS_ENTER);
    
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, 0X00FF);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_B, 0xFFFF);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, 0x00FF);
    
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, 0);
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_B, 0);
    
    dbgOutputLoc(INIT_PORTS_EXIT);
}

void dbgOutputVal(unsigned int outVal)
{
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_B, outVal);  
}

void dbgOutputLoc(unsigned int outVal)
{
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);
}

void dbgError(/*char err[]*/)
{
  /*  vTaskSuspendAll(); //suspends all tasks without stopping the 
    SYS_INT_Disable();
    taskENTER_CRITICAL(); //Disables interrupts
    //Send the error code to the UART
    int i = 0;
    while(i < strlen(err))
    {
        dbgUARTVal(err[i]);
        ++i;
    }
    
    PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, 3);//Turn off the LED
    dbgOutputLoc(ERROR_STATE);
    while(1); //stay in error state*/
}
