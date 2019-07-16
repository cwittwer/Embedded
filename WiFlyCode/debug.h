#ifndef DEBUG_H
#define	DEBUG_H

#include "system_config.h"
#include "system_definitions.h"

//Initialization location codes
#define INIT_PORTS_ENTER 0x01
#define INIT_PORTS_EXIT 0x02
#define MAIN_TO_UART_QUEUE_CREATED 0x03
#define MAIN_RECEIVE_QUEUE_CREATED 0x04
#define UART_TO_ISR_QUEUE_CREATED 0x05
#define UART_TO_MAIN_QUEUE_CREATED 0x06

//Main location codes
#define MAIN_INITIALIZED 0x10
#define MAIN_ENTER 0x11
#define MAIN_WHILE 0x12
#define MAIN_TO_UART_PUSH 0x13
#define MAIN_TO_UART_POP 0x14
#define MAIN_RECEIVE_Q_PUSH 0x15
#define MAIN_RECEIVE_Q_POP 0x16

//USART location codes
#define UART_INITIALIZED 0x20
#define UART_ENTER 0x21
#define UART_WHILE 0x22
#define UART_TO_ISR_PUSH 0x23
#define UART_TO_ISR_POP 0x24
#define UART_TO_MAIN_PUSH 0x25
#define UART_TO_MAIN_POP 0x26

//UART ISR location codes
#define UART_ISR_ENTER 0x30
#define UART_ISR_SEND 0x31
#define UART_NEW_MESSAGE 0x32
#define UART_OLD_MESSAGE 0x33
#define UART_SENDING_MESSAGE 0x34
#define UART_MESSAGE_END 0x35
#define UART_ISR_RECEIVE 0x36
#define UART_ISR_ERROR 0x37
#define UART_ISR_EXIT 0x38

//Timer location codes


//Error
#define QUEUE_CREATION_ERROR 0x70
#define QUEUE_SEND_ERROR 0x71
#define QUEUE_RECEIVE_ERROR 0x72

#define ERROR_STATE 0xFF

//Other codes
#define MAX_MESSAGE_LENGTH (unsigned int) 80
#define TIMER_PERIOD (unsigned int) 100
#define MASK 0x0FF

void initPorts();
void dbgOutputVal(unsigned int outVal);
void dbgOutputLoc(unsigned int outVal);
void dbgError(unsigned int outVal);

#endif	/* DEBUG_H */