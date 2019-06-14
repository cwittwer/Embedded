#include "debug.h"

void initPorts(){
    dbgOutputLoc(INIT_PORTS_ENTER);
    
    TRISE = 0x00FF;
    TRISD = 0x00FF;
    
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, 0x00FF);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, 0x00FF);
    
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, 0);
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, 0);
    
    dbgOutputLoc(INIT_PORTS_EXIT);
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
    // Output the given character
    while(PLIB_USART_TransmitterBufferIsFull(USART_ID_4)){}
    PLIB_USART_TransmitterByteSend(USART_ID_4, outVal);
}

void dbgError(){
    vTaskSuspendAll(); //suspends all tasks without stopping the interrupt
    taskENTER_CRITICAL(); //Disables interrupts
    dbgOutputVal(ERROR_CODE);
    PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_A, 3);//Turn off the LED
    while(1); //stay in error state
}

void sendToUART(int outVal){
    char unitCent[10] = {'c','e','n','t','i','m','e','t','e','r'};
    char str[5];
    sprintf(str, "%d", outVal);
    int i = 0;
    while(i < sizeof(str)/sizeof(str[0])){
        if(str[i] != NULL && str[i] != 0xA5)
            dbgUARTVal(str[i]);
        ++i;
    }
    i = 0;
    while(i<10){
        dbgUARTVal(unitCent[i]);
        ++i;
    }
}