#include "debug.h"

void initPorts(){
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_E, 0x00FF);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_D, 0x00FF);
    
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, 0);
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_D, 0);
//    PLIB_PORTS_DirectionOuputSet(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1, 0x01);
//    PLIB_PORTS_DirectionOuputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6, 0x02 >> 1);
//    /* Pin 48 - Corresponds to bit 2*/
//    PLIB_PORTS_DirectionOuputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8, 0x04 >> 2);
//    /* Pin 49 - Corresponds to bit 3*/
//    PLIB_PORTS_DirectionOuputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11,0x08 >> 3);
//    /* Pin 50 - Corresponds to bit 4*/
//    PLIB_PORTS_DirectionOuputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7, 0x10 >> 4);
//    /* Pin 51 - Corresponds to bit 5*/
//    PLIB_PORTS_DirectionOuputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8, 0x20 >> 5);
//    /* Pin 52 - Corresponds to bit 6*/
//    PLIB_PORTS_DirectionOuputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_6, 0x40 >> 6);
//    /* Pin 53 - Corresponds to bit 7 which will be toggled*/
//    PLIB_PORTS_DirectionOuputSet(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_9);
}

void ValueGPIODisplay(unsigned int outVal){
   /* Pin 46 - Corresponds to bit 0*/
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_F, PORTS_BIT_POS_1, (outVal & 0x01));
    /* Pin 47 - Corresponds to bit 1*/
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_6, (outVal & 0x02) >> 1);
    /* Pin 48 - Corresponds to bit 2*/
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_8, (outVal & 0x04) >> 2);
    /* Pin 49 - Corresponds to bit 3*/
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_11,(outVal & 0x08) >> 3);
    /* Pin 50 - Corresponds to bit 4*/
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_7, (outVal & 0x10) >> 4);
    /* Pin 51 - Corresponds to bit 5*/
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_8, (outVal & 0x20) >> 5);
    /* Pin 52 - Corresponds to bit 6*/
    PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_6, (outVal & 0x40) >> 6);
    /* Pin 53 - Corresponds to bit 7 which will be toggled*/
    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_G, PORTS_BIT_POS_9);
}

void dbgOutputVal(unsigned int outVal){
    if(outVal <= LIMIT){
//        ValueGPIODisplay(outVal);
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);
    }
}

void dbgOutputLoc(unsigned int outVal){
    if(outVal <= LIMIT){
        // Output to a different set of IO Pins
        // Pins need to be accessible when used with other boards
//        EventGPIODisplay(outVal);
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
    while(1); //stay in error state
}

void EventGPIODisplay(unsigned int outVal) {
    //Writes to PORTE, which corresponds to pins 30-37, 30 to RE7, 37 to RE0
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);
}