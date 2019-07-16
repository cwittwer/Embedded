#include "uart_send_thread.h"
#include "system/int/sys_int.h"

/*
* Creates the GET HTTP Request to get data from the server
*
* Parameters:
* result    : The HTTP request string
* source    : The pic-based-endpoint that is creating the request. For example, for the dump rover, source will be "dumprover".
* portNo    : The port no of the server to send to
*/
void create_GET_String(char * result, char * source, int portNo) {
    char portString[10];
    sprintf(portString, "%d", portNo);
    strcpy(result, "GET /");
    strcat(result, source);
    strcat(result, " HTTP/1.1\r\nHost: 192.168.0.10:");
    strcat(result, portString);
    strcat(result, "\r\n\r\n");
}

/*
* Creates the POST HTTP Request to send json data to the server
*
* Parameters:
* result    : The HTTP request string
* source    : The pic-based-endpoint that is creating the request. For example, for the dump rover, source will be "dumprover".
* content   : The json object that is being sent to the server
* portNo    : The port no of the server to send to
*/
void create_POST_String(char * result, char * source, char * content, int portNo) {
    char portString[10];
    sprintf(portString, "%d", portNo);
    int content_length = strlen(content);
    char content_length_string[10];
    sprintf(content_length_string, "%d", content_length);
    strcpy(result, "POST /");
    strcat(result, source);
    strcat(result, " HTTP/1.1\r\nHost: 192.168.0.10:");
    strcat(result, portString);
    strcat(result, "\r\nContent-Type : application/json\r\nContent-Length: ");
    strcat(result, content_length_string);
    strcat(result, "\r\n\r\n");
    strcat(result, content);
    strcat(result, "\r\n\r\n");
}

char * format_message(char c[MAX_MESSAGE_LENGTH])
{
    char * res;
    if(strcmp(c, "get")){
        create_GET_String(res, "Loadcell", 5000);
    } else
        create_POST_String(res, "Loadcell", c, 5000);
    return res;
}

void UART_SEND_THREAD_Initialize ( void )
{
    //DRV_USART0_Initialize();
    create_uart_to_ISR_queue();
    
    //usart initialize
    SYS_INT_SourceDisable(INT_SOURCE_USART_1_TRANSMIT);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_RECEIVE);
    SYS_INT_SourceEnable(INT_SOURCE_USART_1_ERROR);
    
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_TRANSMIT);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_RECEIVE);
    SYS_INT_SourceStatusClear(INT_SOURCE_USART_1_ERROR);
    
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, 0x0FF);
    
    dbgOutputLoc(UART_INITIALIZED);
}

void UART_SEND_THREAD_Tasks ( void )
{
    dbgOutputLoc(UART_ENTER);
    
    while(1)
    {
        dbgOutputLoc(UART_WHILE);

        //Pop the message and format an http get/push message
        main_message mainMess = main_to_uart_pop();
        char * req = mainMess.mess;

        //char * str = "GET /Loadcell HTTP/1.1\r\nHost: 192.168.0.10:5000\r\n\r\n";
        
        char str[MAX_MESSAGE_LENGTH];
        //if(strcmp(req, "get"))
            create_GET_String(str, "Loadcell", 5000);

        //Push the formatted message into the send queue byte by byte
        int index = 0;
        int len = strlen(str);

        while(index < len){
            uart_to_ISR_push(str[index]);
            SYS_INT_SourceEnable(INT_SOURCE_USART_1_TRANSMIT);
            ++index;
        }
    }
}