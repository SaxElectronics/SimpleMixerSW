/******************************************************************************
 * @file iic.c
 * Interrupt system initialization.
 *
 * @author Elod Gyorgy
 *
 * @date 2015-Jan-3
 *
 * @copyright
 * (c) 2015 Copyright Digilent Incorporated
 * All Rights Reserved
 *
 * This program is free software; distributed under the terms of BSD 3-clause
 * license ("Revised BSD License", "New BSD License", or "Modified BSD License")
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name(s) of the above-listed copyright holder(s) nor the names
 *    of its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 * @desciption
 * Contains interrupt controller initialization function.
 *
 * <pre>
 * MODIFICATION HISTORY:
 *
 * Ver   Who          Date     Changes
 * ----- ------------ ----------- -----------------------------------------------
 * 1.00  Elod Gyorgy  2015-Jan-3 First release
 *
 * </pre>
 *
 *****************************************************************************/

#include "intc.h"
#include "xparameters.h"
#include <platform.h>
#include <ps7_init.h>
#include <stdio.h>
#include "xil_printf.h"
#include <xiicps_driver.h>

/* I2S Tx and Rx */
#include "I2S.h"
/* audio formatter */
#include "AudioFormatter.h"
/* verbose */
#include "verbose.h"
/* OS */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

#define INTC_DEVICE_ID XPAR_SCUGIC_0_DEVICE_ID

XScuGic xInterruptController;
// Define a flag for GIC initialization
u8 volatile xIsGICInitialized = FALSE;


const ivt_t ivt[] =
{
	{XPAR_FABRIC_AXI_GPIO_2_IP2INTC_IRPT_INTR, (XInterruptHandler)GpioHandler, &Gpio, GPIO_INTR_PRIORITY, XSCUGIC_INT_CFG_EDGE_SENSITIVE},
			{XPAR_FABRIC_I2S_TRANSMITTER_0_IRQ_INTR, (XInterruptHandler)XI2s_Tx_IntrHandler, &I2sTxInstance, I2S_TX_INTR_PRIORITY, XSCUGIC_INT_CFG_EDGE_SENSITIVE},
			{XPAR_FABRIC_I2S_RECEIVER_0_IRQ_INTR, (XInterruptHandler)XI2s_Rx_IntrHandler, &I2sRxInstance, I2S_RX_INTR_PRIORITY, XSCUGIC_INT_CFG_EDGE_SENSITIVE},
			{XPAR_FABRIC_AUDIO_FORMATTER_0_IRQ_S2MM_INTR, (XInterruptHandler)XAudioFormatterS2MMIntrHandler, &AFInstance, AUDIO_FMT_S2MM_INTR_PRIORITY, XSCUGIC_INT_CFG_EDGE_SENSITIVE},
	{XPAR_FABRIC_AUDIO_FORMATTER_0_IRQ_MM2S_INTR, (XInterruptHandler)XAudioFormatterMM2SIntrHandler, &AFInstance, AUDIO_FMT_MM2S_INTR_PRIORITY, XSCUGIC_INT_CFG_EDGE_SENSITIVE},
	{IIC_INT_VEC_ID, (XInterruptHandler)XIicPs_MasterInterruptHandler, &Iic, IIC_INTR_PRIORITY, XSCUGIC_INT_CFG_EDGE_SENSITIVE},
    {XPAR_SCUTIMER_INTR, (XInterruptHandler)FreeRTOS_Tick_Handler, &xTimer, portLOWEST_USABLE_INTERRUPT_PRIORITY << portPRIORITY_SHIFT, XSCUGIC_INT_CFG_EDGE_SENSITIVE},

	//... other entries ...
};



XStatus fnInitInterruptController(XScuGic *psIntc);
void fnEnableInterrupts(XScuGic *psIntc, const ivt_t *prgsIvt, unsigned int csIVectors);


void InterrupController_Init(void)
{
	XStatus Status, fInitSuccess;

	// Initialize the interrupt controller
	Status = fnInitInterruptController(&xInterruptController);
	if(Status != XST_SUCCESS) {
		VERBOSE("err:irpt");
		fInitSuccess = XST_FAILURE;
		if (fInitSuccess==XST_FAILURE)
			{VERBOSE("init:failed");}
		//goto endinit;
	}

	// Enable all interrupts in our interrupt vector table
	// Make sure all driver instances using this IVT are initialized first
	fnEnableInterrupts(&xInterruptController, &ivt[0], sizeof(ivt)/sizeof(ivt[0]));

}

XStatus fnInitInterruptController(XScuGic *psIntc)
{
	XScuGic_Config *psIntcConfig;

	psIntcConfig = XScuGic_LookupConfig(INTC_DEVICE_ID);
	if (psIntcConfig == NULL)
	{
		return XST_FAILURE;
	}

	// Init driver instance
	RETURN_ON_FAILURE(XScuGic_CfgInitialize(psIntc, psIntcConfig, psIntcConfig->CpuBaseAddress));


	Xil_ExceptionInit();
	// Register the interrupt controller handler with the exception table.
	// This is in fact the ISR dispatch routine, which calls our ISRs
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
				(Xil_ExceptionHandler)XScuGic_InterruptHandler,
				psIntc);
	Xil_ExceptionEnable();

	 // Mark GIC as initialized
	xIsGICInitialized = TRUE;
	return XST_SUCCESS;
}

/*
 * This function enables interrupts and connects interrupt service routines declared in
 * an interrupt vector table
 */
void fnEnableInterrupts(XScuGic *psIntc, const ivt_t *prgsIvt, unsigned int csIVectors)
{
	unsigned int isIVector;

	Xil_AssertVoid(psIntc != NULL);
	Xil_AssertVoid(psIntc->IsReady == XIL_COMPONENT_IS_READY);

	/* Hook up interrupt service routines from IVT */
	for (isIVector = 0; isIVector < csIVectors; isIVector++)
	{
		XScuGic_Connect(psIntc, prgsIvt[isIVector].id, prgsIvt[isIVector].handler, prgsIvt[isIVector].pvCallbackRef);

		// Set the priority and trigger type
		XScuGic_SetPriorityTriggerType(psIntc, prgsIvt[isIVector].id, prgsIvt[isIVector].priority, prgsIvt[isIVector].triggerType);

		/* Enable the interrupt vector at the interrupt controller */
		XScuGic_Enable(psIntc, prgsIvt[isIVector].id);
	}
}
