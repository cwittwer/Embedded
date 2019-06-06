#include "debug.h"

void ValueGPIODisplay(unsigned char outVal)
{
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_E, outVal);
}

void dbgOutputVal(unsigned char outVal)
{
    if(outVal <= 127)
    {
        PORTE = PORTE ^ 0x80; //Toggle the 8th bit
        ValueGPIODisplay(outVal);
    }
}

void dbgOutputLoc(unsigned int outVal)
{
    if(outVal == ERROR_CODE)
        dbgError();
    
    if(outVal <= 127)
        // Output to a different set of IO Pins
        // Pins need to be accessible when used with other boards
        ValueGPIODisplay(outVal);
}

void dbgUARTVal(unsigned char outVal)
{
    // Output the average of every five sensor values
    while(PLIB_USART_TransmitterBufferIsFull(USART_ID_1));
    PLIB_USART_TransmitterByteSend(USART_ID_1, outVal);
    while(PLIB_USART_TransmitterBufferIsFull(USART_ID_1));
}

void dbgError()
{
    vTaskSuspendAll(); //suspends all tasks without stopping the interrupt
    taskENTER_CRITICAL(); //Disables interrupts
    dbgOutputLoc(ERROR_STATE); //show we have encountered the error state
    while(1); //stay in error state
    
}