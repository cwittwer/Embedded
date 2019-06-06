#ifndef DEBUG_H
#define	DEBUG_H

#include "system_config.h"
#include "system_definitions.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/peripheral.h"
#include "driver/usart/drv_usart.h"

#define APP_ENTER ((unsigned int) 0)
#define APP_WHILE ((unsigned int) 1)
#define APP_BEFORE_Q_RX ((unsigned int) 2)
#define APP_AFTER_Q_RX ((unsigned int) 3)

#define ISR_ENTER ((unsigned int) 4)
#define ISR_EXIT ((unsigned int) 5)
#define ISR_BEFORE_Q_TX ((unsigned char) 6)
#define ISR_AFTER_Q_TX ((unsigned char) 7)

#define ERROR_CODE ((unsigned int)0xFFFFFFFF)
#define ERROR_STATE ((unsigned char) 'E')

void dbgOutputVal(unsigned int outVal);
void dbgUARTVal(unsigned char outVal);
void dbgOutputLoc(unsigned int outVal);
void ValueGPIODisplay(unsigned char outVal);
void dbgError();

#endif	/* DEBUG_H */