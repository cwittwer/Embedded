#include "system/common/sys_common.h"
#include "app.h"
#include "system_definitions.h"

void IntHandlerDrvTmrInstance0(void)
{
    dbgOutputLoc(ISR_ENTER);
    
    DRV_ADC_Start();
    while(!DRV_ADC_SamplesAvailable()){}
    uint32_t adcVal = DRV_ADC_SamplesRead(0);
    DRV_ADC_Stop();
    
    // Read from buffer 0 and get a 32 bit integer which gets converted to meaningful distance value
    message dist;
    dist = ADCConverter(adcVal);
    
    dbgOutputLoc(ISR_BEFORE_Q_TX);
    
    q_push(dist);
    
    dbgOutputLoc(ISR_AFTER_Q_TX);
    
    PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, 3);
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_2);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_TIMER_2);

    dbgOutputLoc(ISR_EXIT);
}
