#include "debug.h"
#include "uart.h"
#include "Digilent_config.h"
#include <stdio.h>
#include <plib.h>

//four routines for debugging purposes
//1. dbgOutputVal(unsigned int outVal)
    //outVal <= 127 --> routine verify this
    //output to 8 PIC i/o lines --> write value to 7 out of 8 lines --> toggle 8th line to single new value written
    //used by state machine to output sensor value read from message queue
void dbgOutputVal(unsigned int outVal)
{
    if(outVal <= 127)
    {
        //output to i/o lines
    }
    else
    {
        //Error message??
    }
}

//2. dbgUARTVal(unsigned char outVal)
    //value written to UART
    //call in state machine to output average of five sensors
void dbgUARTVal(unsigned char outVal)
{
    initUART(UART1, 10000000, 9600);
    UARTSendString(UART1, outVal);
}

//3. dbgOutputLoc(unsigned int outVal)
    //outVal <= 127 --> routine verify this
    //output to different set of 8 PIC i/o lines
    //called in different parts of code --> each part uses unique value
    //define different constant for each value --> in debug.h
    //when called, called by i.e. dbgOutputLoc(DLOC_UART_ISR_BEGIN)
    //call it w/unique constant at:
        //1. every task --> entering task, before "while(1)", before sending/receiving from queue, after sending/receiving from queue
        //2. every ISR --> entering ISR, before leaving ISR, before sending/receiving from queue, after sending/receiving from queue
void dbgOutputLoc(unsigned int outVal)
{
    if(outVal <= 127)
    {
        
    }
    else
    {
        //Error message??
    }
}

//4. create "stop everything we have a bad error routine" --> you name it and its arguments
    //everything in code stops (but this routine) --> but continue to output unique value indicating everything stopped --> use #3 or blink LED
void dbgError()
{
    
}