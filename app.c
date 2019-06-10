#include "app.h"

void APP_Initialize ( void )
{
    create_queue();
    initPorts();
    DRV_TMR0_Initialize();
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_2);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_TIMER_2);
    PLIB_TMR_Start(TMR_ID_2);
    
    DRV_ADC_Initialize();
    DRV_ADC_Open();
    usartHandle = DRV_USART_Open(DRV_USART_INDEX_0, DRV_IO_INTENT_WRITE);
}

void APP_Tasks ( void )
{
    dbgOutputLoc(APP_ENTER);
    
    int sum = 0;
    int st = 0;
    message mes;
    
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
