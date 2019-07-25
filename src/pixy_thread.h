#ifndef _PIXY_THREAD_H
#define _PIXY_THREAD_H

#include "debug.h"
#include "pixy_queue.h"
#include "pixy_state.h"
#include "main_to_uart_queue.h"
#include "uart_to_main_queue.h"

#include "FreeRTOS.h"
#include "timers.h"
#include "string.h"
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

TimerHandle_t xTimerSend;
TimerHandle_t xTimerParse;

void PIXY_THREAD_Initialize ( void );

void PIXY_THREAD_Tasks( void );

#endif /* _APP_H */