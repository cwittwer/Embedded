#ifndef DEBUG_H
#define	DEBUG_H

#include "system_config.h"
#include "system_definitions.h"

//Initialization location codes
#define MY_QUEUE_CREATE_QUEUE_ENTER 0x01
#define MY_QUEUE_CREATE_QUEUE_EXIT 0x02
#define INIT_PORTS_ENTER 0x03
#define INIT_PORTS_EXIT 0x04

//App task location codes
#define APP_ENTER 0x10
#define APP_WHILE 0x11
#define APP_BEFORE_Q_RX 0x12
#define APP_AFTER_Q_RX 0x13
#define PIXY_STATE_ENTER 0x14
#define PIXY_STATE_EXIT 0x15

//ISR location codes
#define ISR_ENTER 0x20
#define ISR_BEFORE_Q_TX 0x21
#define ISR_AFTER_Q_TX 0x22
#define ISR_EXIT 0x23

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

#define ERROR_STATE 0xFF

#define LIMIT ((unsigned int) 127)
#define MASK 0x0FF

void initPorts();
void dbgOutputVal(unsigned int outVal);
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outVal);
void dbgError(/*char err[]*/);

#endif	/* DEBUG_H */