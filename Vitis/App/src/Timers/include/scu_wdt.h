#ifndef SCU_WDT_H_
#define SCU_WDT_H_

/* The private watchdog is used to generate run time stats. */
#include "xscuwdt.h"
#include "xscuwdt_hw.h"
extern XScuWdt xWatchDogInstance;


#define GET_WATCHDOG_COUNTER_VALUE_INVERTED() ( ( 0xffffffffUL - XScuWdt_ReadReg( xWatchDogInstance.Config.BaseAddr, XSCUWDT_COUNTER_OFFSET ) ) >> 1 )


#endif
