#ifndef TTC_INIT_H		/* prevent circular inclusions */
#define TTC_INIT_H		/* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

#define TTC_DEVICE_ID 				XPAR_XTTCPS_0_DEVICE_ID // Replace with the actual device ID
#define TTC_TICK_RATE_HZ 			1000000 // 1 MHz for 1us step


#include "xil_types.h"
#include "xttcps.h"


extern XTtcPs Ttc0PsInstance; // The instance of the TTC


/* function prototypes */
extern void Ttc0InterruptHandler(void *CallBackRef);
extern int InitializeTTC(u16 DeviceId, u32 TickRateHz);
extern void FreeRTOS_CounterInit_TTC(void);
uint32_t GetMonotonicTtcTime(void);

#ifdef __cplusplus
}
#endif

#endif
