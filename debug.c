#include "debug.h"

void initPorts(){
    TRISE = 0xFF;
    TRISD = 0xFF;
    
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, 0x00FF);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, 0x00FF);
    
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, 0);
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, 0);
}

void dbgOutputVal(unsigned int outVal){
    if(outVal > LIMIT){//Too large
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, LIMIT);
    }
    else
    {
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);  
    }
}

void dbgOutputLoc(unsigned int outVal){
    if(outVal > LIMIT){//Too large
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, LIMIT);
    }
    else
    {
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, outVal);
    }
}

void dbgUARTVal(unsigned char outVal){
    // Output the average of every five sensor values
    while(PLIB_USART_TransmitterBufferIsFull(USART_ID_1));
    PLIB_USART_TransmitterByteSend(USART_ID_1, outVal);
    // TODO - test this
    //while(PLIB_USART_TransmitterBufferIsFull(USART_ID_1));
}

void dbgError(){
    vTaskSuspendAll(); //suspends all tasks without stopping the interrupt
    taskENTER_CRITICAL(); //Disables interrupts
    EventGPIODisplay(ERROR_CODE);
    PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, 3);//Turn off the LED
    while(1); //stay in error state
}

void EventGPIODisplay(unsigned int outVal) {
    //Writes to PORTE, which corresponds to pins 30-37, 30 to RE7, 37 to RE0
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);
}