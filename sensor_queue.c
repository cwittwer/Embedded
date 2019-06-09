#include "sensor_queue.h"

void create_queue(){
    xQ = xQueueCreate(QLENGTH, sizeof(message));
    if(xQ == NULL){
        //Error: no queue created
        dbgError();
    }
}

message q_pop(message m){
    if(xQueueReceive(xQ, &m, portMAX_DELAY) != pdTRUE){
        //Error: no message received
        dbgError();
    }
    return m;
}

void q_push(message m){
    if(xQueueSendFromISR(xQ, &m, pdFALSE) != pdTRUE){
        //Error: no message sent; Queue may be full
        dbgError();
    }
}

message ADCConverter(unsigned int data){
    unsigned int distance;
    if(data >= 1023) {
        distance = 11;
    } else if(data >= 894) {
        distance = 13;
    } else if(data >= 766) {
        distance = 16;
    } else if(data >= 657) {
        distance = 20;
    } else if(data >= 545) {
        distance = 23;
    } else if(data >= 506) {
        distance = 26;
    } else if(data >= 475) {
        distance = 29;
    } else if(data >= 450) {
        distance = 32;
    } else if(data >= 427) {
        distance = 35;
    } else if(data >= 409) {
        distance = 38;
    } else if(data >= 393) {
        distance = 42;
    } else if(data >= 379) {
        distance = 45;
    } else if(data >= 366) {
        distance = 50;
    } else if(data >= 355) {
        distance = 53;
    } else if(data >= 345) {
        distance = 59;
    } else if(data >= 337) {
        distance = 62;
    } else if(data >= 330) {
        distance = 65;
    } else if(data >= 315) {
        distance = 68;
    } else if(data >= 309) {
        distance = 71;
    } else if(data >= 303) {
        distance = 74;
    }else if(data >= 294) {
        distance = 77;
    } else if(data >= 289) {
        distance = 80;
    } else if(data >= 285) {
        distance = 83;
    } else if(data >= 281) {
        distance = 86;
    } else if(data >= 274) {
        distance = 92;
    } else if(data >= 271) {
        distance = 101;
    } else if(data >= 268) {
        distance = 104;
    } else if(data >= 266) {
        distance = 107;
    } else if(data >= 261) {
        distance = 110;
    } else if(data >= 256) {
        distance = 116;
    } else if(data >= 254) {
        distance = 119;
    } else if(data >= 252) {
        distance = 122;
    } else if(data >= 250) {
        distance = 125;
    } else {
        distance = 127;
    }
    message mess = {distance, {'c','e','n','t','i','m','e','t','e','r'}};
    return mess;
}