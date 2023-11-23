/* Xilinx includes. */
#include "xparameters.h"
#include "xscutimer.h"
#include "xscuwdt.h"

#include "xscugic.h"
#include "xil_exception.h"
#include "xuartps_hw.h"
#include "limits.h"



/* The private watchdog is used as the timer that generates run time
stats.  This frequency means it will overflow quite quickly. */
XScuWdt xWatchDogInstance;

extern s32 XScuWdt_CfgInitialize(XScuWdt *InstancePtr,
		 XScuWdt_Config *ConfigPtr, u32 EffectiveAddress);


void WhatchDogTimer_Init( void )
{
	XScuWdt_Config *pxWatchDogInstance;
	uint32_t ulValue;
	const uint32_t ulMaxDivisor = 0xff, ulDivisorShift = 0x08;

	 pxWatchDogInstance = XScuWdt_LookupConfig( XPAR_SCUWDT_0_DEVICE_ID );
	 XScuWdt_CfgInitialize( &xWatchDogInstance, pxWatchDogInstance, pxWatchDogInstance->BaseAddr );

	 ulValue = XScuWdt_GetControlReg( &xWatchDogInstance );
	 ulValue |= ulMaxDivisor << ulDivisorShift;
	 XScuWdt_SetControlReg( &xWatchDogInstance, ulValue );

	 XScuWdt_LoadWdt( &xWatchDogInstance, UINT_MAX );
	 XScuWdt_SetTimerMode( &xWatchDogInstance );
	 XScuWdt_Start( &xWatchDogInstance );
}
