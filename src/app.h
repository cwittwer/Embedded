#ifndef _APP_H
#define _APP_H

#include "debug.h"
#include "my_queue.h"
#include "pixy_state.h"
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

void APP_Initialize ( void );

void APP_Tasks( void );

#endif /* _APP_H */