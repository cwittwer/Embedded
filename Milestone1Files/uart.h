#ifndef UART_H
#define	UART_H

#include <plib.h>

#ifdef	__cplusplus
extern "C" {
#endif

    void initUART(UART_MODULE uart, unsigned int sourceClock, unsigned int dataRate);
    
    unsigned char UARTReceiveByte(UART_MODULE uart);
    
    void UARTSendByte(UART_MODULE uart, unsigned char byte_sent);
    
    void UARTSendString(UART_MODULE uart, const char* string);

#endif	/* UART_H */

