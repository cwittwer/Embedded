#include "sensor_queue.h"

void create_queue(){
    xQ = xQueueCreate(10, sizeof(message));
    if(xQ == NULL){
        //Error: no queue created
    }
}

message mQ_pop(message m){
    if(xQueueReceive(xQ, &m, portMAX_DELAY) != pdTrue){
        //Error: no message recieved
    }
    return m;
}

void mQ_push(message m){
    if(xQueueSendFromISR(xQ, &m, pdFalse) != pdTrue){
        //Error: no message sent
    }
}