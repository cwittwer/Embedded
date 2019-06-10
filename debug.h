#ifndef DEBUG_H
#define	DEBUG_H

#include "system_config.h"
#include "system_definitions.h"
//#include "peripheral/ports/plib_ports.h"
//#include "peripheral/peripheral.h"
//#include "driver/usart/drv_usart.h"

#define APP_ENTER ((unsigned int) 0)
#define APP_WHILE ((unsigned int) 1)
#define APP_BEFORE_Q_RX ((unsigned int) 2)
#define APP_AFTER_Q_RX ((unsigned int) 3)

#define ISR_ENTER ((unsigned int) 4)
#define ISR_EXIT ((unsigned int) 5)
#define ISR_BEFORE_Q_TX ((unsigned int) 6)
#define ISR_AFTER_Q_TX ((unsigned int) 7)

#define SENSOR_STATE_ENTER ((unsigned int) 8)
#define SENSOR_STATE_EXIT ((unsigned int) 9)

#define SENSOR_QUEUE_CREATE_QUEUE_ENTER ((unsigned int) 10)
#define SENSOR_QUEUE_CREATE_QUEUE_EXIT ((unsigned int) 11)

#define SENSOR_QUEUE_Q_POP_ENTER ((unsigned int) 12)
#define SENSOR_QUEUE_Q_POP_EXIT ((unsigned int) 13)

#define SENSOR_QUEUE_Q_PUSH_ENTER ((unsigned int) 14)
#define SENSOR_QUEUE_Q_PUSH_EXIT ((unsigned int) 15)

#define SENSOR_QUEUE_ADC_CONVERTER_ENTER ((unsigned int) 16)
#define SENSOR_QUEUE_ADC_CONVERTER_EXIT ((unsigned int) 17)

#define ERROR_CODE ((unsigned int)0xFFFFFFF)
#define ERROR_STATE ((unsigned int) 66)

#define LIMIT ((unsigned int) 127)

void initPorts();
void dbgOutputVal(unsigned int outVal);
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outVal);
void ValueGPIODisplay(unsigned int outVal);
void dbgError();
void EventGPIODisplay(unsigned int outVal);

#endif	/* DEBUG_H */