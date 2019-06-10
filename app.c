#include "app.h"

void APP_Initialize ( void )
{
    create_queue();
    initPorts();
    DRV_TMR0_Initialize();
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_2);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_TIMER_2);
    PLIB_TMR_Start(TMR_ID_2);
    
    DRV_ADC_Open();
    DRV_ADC_Start();
    usartHandle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_WRITE);
}

void APP_Tasks ( void )
{
    int sum = 0;
    int st = 0;
    message mes;
    while(1){
        mes = q_pop(mes);
        sum = sensor_state(mes.val, sum, st);
        st = (st+1)%5;
    }
}
