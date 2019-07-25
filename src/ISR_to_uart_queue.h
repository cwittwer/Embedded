#ifndef ISR_TO_UART_QUEUE_H
#define	ISR_TO_UART_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

#define ISR_TO_UART_QLENGTH MAX_MESSAGE_LENGTH

static QueueHandle_t ISR_to_uart_handle;

void create_ISR_to_uart_queue();
char ISR_to_uart_pop();
void ISR_to_uart_push(char m, BaseType_t * const pxHigherPriorityTaskWoken);
unsigned int ISR_to_uart_waiting();

#endif	/* ISR_TO_UART_QUEUE_H */