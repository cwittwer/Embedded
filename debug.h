#ifndef DEBUG_H
#define	DEBUG_H

#include "system_config.h"
#include "system_definitions.h"

//Initialization location codes
#define SENSOR_QUEUE_CREATE_QUEUE_ENTER 0x01
#define SENSOR_QUEUE_CREATE_QUEUE_EXIT 0x02
#define INIT_PORTS_ENTER 0x03
#define INIT_PORTS_EXIT 0x04

//App task location codes
#define APP_ENTER 0x10
#define APP_WHILE 0x11
#define APP_BEFORE_Q_RX 0x12
#define APP_AFTER_Q_RX 0x13
#define SENSOR_STATE_ENTER 0x14
#define SENSOR_STATE_EXIT 0x15

//ISR location codes
#define ISR_ENTER 0x20
#define SENSOR_QUEUE_ADC_CONVERTER_ENTER 0x21
#define SENSOR_QUEUE_ADC_CONVERTER_EXIT 0x22
#define ISR_BEFORE_Q_TX 0x23
#define ISR_AFTER_Q_TX 0x24
#define ISR_EXIT 0x25

#define ERROR_STATE 0xFF

#define LIMIT ((unsigned int) 127)
#define MASK 0x0FF

void initPorts();
void dbgOutputVal(unsigned int outVal);
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outVal);
void dbgError(char err[]);

#endif	/* DEBUG_H */