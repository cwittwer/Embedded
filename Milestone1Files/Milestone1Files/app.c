#include "app.h"

void APP_Initialize ( void )
{
    create_queue();
}

void APP_Tasks ( void )
{
    int sum = 0;
    int st = 0;
    struct message mes;
    while(1){
        mes = q_pop(mes);
        sum = sensor_state(mes.val, sum, st);
        st = (st+1)%5;
    }
}
