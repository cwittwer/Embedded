#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include "debug.h"
#include "sensor_queue.h"

void sendDataToMsgQueue();
unsigned int ADCConverter(int analogData);

#endif 