#include "sensor_queue.h"

void create_queue(){
    xQ = xQueueCreate(10, sizeof(struct message));
    if(xQ == NULL){
        //Error: no queue created
        dbgOutputLoc(ERROR_CODE);
    }
}

struct message q_pop(struct message m){
    if(xQueueReceive(xQ, &m, portMAX_DELAY) != pdTRUE){
        //Error: no message recieved
        dbgOutputLoc(ERROR_CODE);
    }
    return m;
}

void q_push(struct message m){
    if(xQueueSendFromISR(xQ, &m, pdFALSE) != pdTRUE){
        //Error: no message sent
        dbgOutputLoc(ERROR_CODE);
    }
}

void ISRSendMsgToQueue(void* msg, portBASE_TYPE* pxHigherPriorityTaskToken){
    if(xQueueSendToBackFromISR(xQ, msg, pxHigherPriorityToken) != pdPASS){
        //ERROR
    }
}