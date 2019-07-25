#ifndef MAIN_TO_UART_QUEUE_H
#define	MAIN_TO_UART_QUEUE_H

#include "FreeRTOS.h"
#include "queue.h"
#include "debug.h"

#define MAIN_TO_UART_QLENGTH 10
#define MAIN_TO_UART_MLENGTH 48

static QueueHandle_t main_to_uart_handle;

typedef struct
{
    bool get;
    char mess[MAIN_TO_UART_MLENGTH];
} main_message;

void create_main_to_uart_queue();
main_message main_to_uart_pop();
void main_to_uart_push(main_message m);
unsigned int main_to_uart_waiting();

#endif	/* MAIN_TO_UART_QUEUE_H */