#ifndef _MAIN_THREAD_H
#define _MAIN_THREAD_H

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <FreeRTOS.h>
#include <timers.h>

#include "main_to_uart_queue.h"
#include "uart_to_main_queue.h"

TimerHandle_t xTimer;

void MAIN_THREAD_Initialize ( void );

void MAIN_THREAD_Tasks( void );

#endif /* _MAIN_THREAD_H */