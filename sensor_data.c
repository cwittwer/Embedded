#include "sensor_data.h"

void SendDataToMsgQueue()
{
    while(!DRV_ADC_SamplesAvailable());

    // Read from buffer 0 and get a 32 bit integer which gets converted to meaningful distance value
    unsigned int distance = ADCConverter(DRV_ADC_SamplesRead(0));
    struct message dist_mess = {distance};
    q_push(dist_mess);
    
    uint8_t C = 'c';
    struct message C_mess = {C};
    q_push(C_mess);
    
    uint8_t M = 'm';
    struct message M_mess = {M};
    q_push(M_mess);
}

