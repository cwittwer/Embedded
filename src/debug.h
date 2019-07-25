#ifndef DEBUG_H
#define	DEBUG_H

#include "system_config.h"
#include "system_definitions.h"

//Initialization location codes
#define PIXY_QUEUE_CREATE_QUEUE_ENTER 0x01
#define PIXY_QUEUE_CREATE_QUEUE_EXIT 0x02
#define INIT_PORTS_ENTER 0x03
#define INIT_PORTS_EXIT 0x04

#define MAIN_TO_UART_QUEUE_CREATED 0x05
#define UART_TO_ISR_QUEUE_CREATED 0x06
#define ISR_TO_UART_QUEUE_CREATED 0x07
#define UART_TO_MAIN_QUEUE_CREATED 0x08

//App task location codes
#define PIXY_INITIALIZED 0x10
#define PIXY_THREAD_ENTER 0x11
#define PIXY_THREAD_WHILE 0x12
#define PIXY_THREAD_BEFORE_Q_RX 0x13
#define PIXY_THREAD_AFTER_Q_RX 0x14
#define PIXY_STATE_ENTER 0x15
#define PIXY_STATE_EXIT 0x16
#define PIXY_THREAD_SEND_DISTANCE 0x17

#define SOFTWARE_TIMER 0x19

//ISR location codes
#define PIXY_ISR_ENTER 0x20
#define PIXY_ISR_BEFORE_Q_TX 0x21
#define PIXY_ISR_AFTER_Q_TX 0x22
#define PIXY_ISR_EXIT 0x23

#define MAIN_TO_UART_PUSH 0x27
#define MAIN_TO_UART_POP 0x28

//Pixy state location codes
#define PIXY_INITIAL 0x30
#define PIXY_SYNC 0x31
#define PIXY_CHECKSUM1 0x32
#define PIXY_CHECKSUM2 0x33
#define PIXY_SIGNATURE1 0x34
#define PIXY_SIGNATURE2 0x35
#define PIXY_XCENTER1 0x36
#define PIXY_XCENTER2 0x37
#define PIXY_YCENTER1 0x38
#define PIXY_YCENTER2 0x39
#define PIXY_WIDTH1 0x40
#define PIXY_WIDTH2 0x41
#define PIXY_HEIGHT1 0x42
#define PIXY_HEIGHT2 0x43

//USART send thread location codes
#define UART_SEND_INITIALIZED 0x50
#define UART_SEND_ENTER 0x51
#define UART_SEND_WHILE 0x52
#define UART_TO_ISR_PUSH 0x53
#define UART_TO_ISR_POP 0x54

//USART receive thread location codes
#define UART_RECEIVE_INITIALIZED 0x60
#define UART_RECEIVE_ENTER 0x61
#define UART_RECEIVE_WHILE 0x62
#define ISR_TO_UART_PUSH 0x63
#define ISR_TO_UART_POP 0x64
#define UART_TO_MAIN_PUSH 0x65
#define UART_TO_MAIN_POP 0x66

//UART ISR location codes
#define UART_ISR_ENTER 0x70
#define UART_ISR_SEND 0x71
#define UART_NEW_MESSAGE 0x72
#define UART_OLD_MESSAGE 0x73
#define UART_SENDING_MESSAGE 0x74
#define UART_MESSAGE_END 0x75
#define UART_ISR_RECEIVE 0x76
#define UART_ISR_ERROR 0x77
#define UART_ISR_EXIT 0x78

#define PIXY_ISR_TRANSMIT_ERROR 0x90
#define PIXY_ISR_ERROR 0x91
#define QUEUE_CREATE_ERROR 0x92
#define QUEUE_POP_ERROR 0x93
#define QUEUE_PUSH_ERROR 0x94
#define QUEUE_CREATION_ERROR 0x95
#define QUEUE_SEND_ERROR 0x96
#define QUEUE_RECEIVE_ERROR 0x97

#define ERROR_STATE 0xFF

//other codes
#define MAX_MESSAGE_LENGTH (unsigned int) 140
#define MAX_RESPONE_LENGTH (unsigned int) 40
#define TIMER_PERIOD (unsigned int) 1000
#define LIMIT ((unsigned int) 127)
#define MASK 0x0FF

void initPorts();
void dbgOutputVal(unsigned int outVal);
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outVal);
void dbgError(/*char err[]*/);

#endif	/* DEBUG_H */