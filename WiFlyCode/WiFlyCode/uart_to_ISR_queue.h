#ifndef UART_TO_ISR_QUEUE_H
#define	UART_TO_ISR_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

#define UART_TO_ISR_QLENGTH MAX_MESSAGE_LENGTH

static QueueHandle_t uart_to_ISR_handle;

void create_uart_to_ISR_queue();
char uart_to_ISR_pop(BaseType_t * const pxHigherPriorityTaskWoken);
void uart_to_ISR_push(char m);
unsigned int uart_to_ISR_waiting();

#endif	/* UART_TO_ISR_QUEUE_H */