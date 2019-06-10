#include "sensor_state.h"
#include "debug.h"

int sensor_state(int val, int sum, int state)
{
    dbgOutputLoc(SENSOR_STATE_ENTER);
    
    dbgOutputVal(val);
    int ret = 0;
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
            dbgUARTVal((sum + val)/AVG_OF);//Sends avg to UART
            ret = 0;
            break;
        default:
            //
            dbgError();
            break;
    }
    
    dbgOutputLoc(SENSOR_STATE_EXIT);
    
    return ret;
}