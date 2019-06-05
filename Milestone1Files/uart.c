#include "uart.h"

void initUART(UART_MODULE uart, unsigned int sourceClock, unsigned int dataRate)
{
    UARTConfigure(uart, UART_ENABLE_PINS_TX_RX_ONLY);
    UARTSetLineControl(uart, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE | UART_STOP_BITS_1);
    UARTSetDataRate(uart, sourceClock, dataRate);
    UARTEnable(uart, UART_ENABLE | UART_PERIPHERAL | UART_RX | UART_TX);
}
    
unsigned char UARTReceiveByte(UART_MODULE uart)
{     
    while(!UARTReceivedDataIsAvailable(uart))
    {
    }
        
    return UARTGetDataByte(uart);
}
  
void UARTSendByte(UART_MODULE uart, unsigned char byte_sent)
{
    while(!UARTTransmitterIsReady(uart))
    {
    }
        
    UARTSendDataByte(uart, byte_sent);
}
    
void UARTSendString(UART_MODULE uart, const char* string)
{
    int i = 0;
    while(i < strlen(string))
    {
        while(!UARTTransmitterIsReady(uart))
        {
        }
        UARTSendByte(uart, string[i]);
        i++;
    }
}