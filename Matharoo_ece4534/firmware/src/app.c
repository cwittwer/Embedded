#include "app.h"
#include "debug.h"

void APP_Initialize ( void )
{
    create_queue();
}

void APP_Tasks ( void )
{
    dbgOutputLoc(APP_ENTER);
    
    int sum = 0;
    int st = 0;
    struct message mes;
    
    dbgOutputLoc(APP_WHILE);
    
    while(1)
    {
        dbgOutputLoc(APP_BEFORE_Q_RX);
        
        mes = q_pop(mes);
        
        dbgOutputLoc(APP_AFTER_Q_RX);
        
        sum = sensor_state(mes.val, sum, st);
        st = (st+1)%5;
    }
}