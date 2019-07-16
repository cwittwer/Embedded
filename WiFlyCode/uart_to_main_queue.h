#ifndef UART_TO_MAIN_QUEUE_H
#define	UART_TO_MAIN_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

#define UART_TO_MAIN_QLENGTH 10
#define UART_TO_MAIN_MLENGTH 48

static QueueHandle_t uart_to_main_handle;

typedef struct
{
    unsigned int len;
    char mess[UART_TO_MAIN_MLENGTH];
} main_response;

void create_uart_to_main_queue();
main_response uart_to_main_pop();
void uart_to_main_push(main_response m);
unsigned int uart_to_main_waiting();

#endif	/* UART_TO_MAIN_QUEUE_H */