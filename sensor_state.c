#include "sensor_state.h"

int sensor_state(int val, int sum, int state)
{
    dbgOutputLoc(SENSOR_STATE_ENTER);
    
    dbgOutputVal(val);
    int ret = 0;
    int avg = 0;
    switch(state){
        case(FIRST_VAL):
            ret = sum + val;
            break;
        case(SECOND_VAL):
            ret = sum + val;
            break;
        case(THIRD_VAL):
            ret = sum + val;
            break;
        case(FOURTH_VAL):
            ret = sum + val;
            break;
        case(FIFTH_VAL):
            sendToUART((int)(sum + val)/AVG_OF);
            ret = 0;
            break;
        default:
            dbgError();
            break;
    }
    dbgOutputLoc(SENSOR_STATE_EXIT);
    
    return ret;
}