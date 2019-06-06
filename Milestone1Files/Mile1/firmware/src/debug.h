#ifndef DEBUG_H
#define	DEBUG_H

#include "system_config.h"
#include "system_definitions.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/peripheral.h"
#include "driver/usart/drv_usart.h"

#define TASK_ENTER ((unsigned char) '0')
#define INF_WHILE ((unsigned char) '1')
#define TASK_BEFORE_Q_TX ((unsigned char) '2')
#define TASK_BEFORE_Q_RX ((unsigned char) '3')
#define TASK_AFTER_Q_TX ((unsigned char) '4')
#define TASK_aFTER_Q_RX ((unsigned char) '5')

#define ISR_ENTER ((unsigned char) '6')
#define ISR_EXIT ((unsigned char) '7')
#define ISR_BEFORE_Q_TX ((unsigned char) '8')
#define ISR_BEFORE_Q_RX ((unsigned char) '9')
#define ISR_AFTER_Q_TX ((unsigned char) 'A')
#define ISR_AFTER_Q_RX ((unsigned char) 'B')

#define ERROR_CODE ((unsigned int)0xFFFFFFFF)
#define ERROR_STATE ((unsigned char) 'E')

void dbgOutputVal(unsigned int outVal);
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outVal);
void ValueGPIODisplay(unsigned char outVal);
void dbgError();

#endif	/* DEBUG_H */