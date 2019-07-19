#ifndef _UART_SEND_THREAD_H
#define _UART_SEND_THREAD_H

#include "uart_to_ISR_queue.h"

#include <string.h>

void UART_SEND_THREAD_Initialize ( void );

void UART_SEND_THREAD_Tasks( void );

#endif /* _UART_SEND_THREAD_H */