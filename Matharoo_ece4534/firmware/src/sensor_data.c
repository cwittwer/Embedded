#include "sensor_data.h"

void SendDataToMsgQueue()
{
    while(!DRV_ADC_SamplesAvailable(0));

    // Read from buffer 0 and get a 32 bit integer which gets converted to meaningfule distance value
    unsigned int distance = ADCConverter(DRV_ADC_SamplesRead(0));
    ISRSendMsgToQueue(&distance, pdFALSE);
    uint8_t C = 'c';
    uint8_t M = 'm';
    ISRSendMsgToQueue(&C, pdFALSE);
    ISRSendMsgToQueue(&M, pdFALSE);
}

unsigned int ADCConverter(int data)
{
    unsigned int distance;
    //need to get sensor info from sensor website for conversion
}