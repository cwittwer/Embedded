#include "sensor_state.h"
//#include "debug.h"

int sensor_state(int val, int sum, int st){
    dbgOutputVal(val);
    int ret = 0;
    switch(st){
        case(0):
            ret = sum + val;
            break;
        case(1):
            ret = sum + val;
            break;
        case(2):
            ret = sum + val;
            break;
        case(3):
            ret = sum + val;
            break;
        case(4):
            dbgUARTVal((sum + val)/5);//Sends avg to UART
            ret = 0;
            break;
        default:
            break;
    }
    return ret;
}