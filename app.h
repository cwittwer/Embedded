#ifndef _APP_H
#define _APP_H

#include "sensor_state.h"
#include "sensor_queue.h"
#include "debug.h"
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

static DRV_HANDLE usartHandle;
DRV_USART_BUFFER_HANDLE bufHandle;

void APP_Initialize ( void );

void APP_Tasks( void );

#endif /* _APP_H */
