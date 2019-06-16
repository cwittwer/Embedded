#ifndef _APP_H
#define _APP_H

#include "sensor_state.h"
#include "sensor_queue.h"
#include "debug.h"
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define BAUD_RATE ((unsigned int) 9600)

void APP_Initialize ( void );

void APP_Tasks( void );

#endif /* _APP_H */
