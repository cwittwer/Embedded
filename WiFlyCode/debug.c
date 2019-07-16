#include "debug.h"

void initPorts(){
    dbgOutputLoc(INIT_PORTS_ENTER);
    
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, MASK);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, MASK);
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, 0);
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, 0);
    
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, MASK);
    PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, 3);
    
    dbgOutputLoc(INIT_PORTS_EXIT);
}

void dbgOutputVal(unsigned int outVal){
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);  
}

void dbgOutputLoc(unsigned int outVal){
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, outVal);
}

void dbgError(unsigned int outVal){
    vTaskSuspendAll();                                  //suspends all tasks without stopping the 
    SYS_INT_Disable();
    taskENTER_CRITICAL();                               //Disables interrupts
    dbgOutputVal(outVal);                               //Send the error code to the UART
    PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, 3); //Turn off the LED
    dbgOutputLoc(ERROR_STATE);
    while(1);                                           //stay in error state
}