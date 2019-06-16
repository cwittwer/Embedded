#include "sensor_state.h"

int sensor_state(int val, int sum, int state)
{
    dbgOutputLoc(SENSOR_STATE_ENTER);
    
    dbgOutputVal(val);
    int ret = 0;
    switch(state){
        case(FIRST_VAL):
        case(SECOND_VAL):
        case(THIRD_VAL):
        case(FOURTH_VAL):
            ret = sum + val;
            break;
        case(FIFTH_VAL):
            sendToUART((int)(sum + val)/5);
            ret = 0;
            break;
        default:
            dbgError("Invalid State");
            break;
    }
    dbgOutputLoc(SENSOR_STATE_EXIT);
    
    return ret;
}