#ifndef _UART_RECEIVE_THREAD_H
#define _UART_RECEIVE_THREAD_H

#include "ISR_to_uart_queue.h"

#include <string.h>

void UART_RECEIVE_THREAD_Initialize ( void );

void UART_RECEIVE_THREAD_Tasks( void );

#endif /* _UART_RECEIVE_THREAD_H */