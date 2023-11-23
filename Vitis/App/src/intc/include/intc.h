/******************************************************************************
 * @file intc.h
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

#ifndef INTC_H_
#define INTC_H_

#include "xstatus.h"
#include "xscugic.h"
#include "xil_exception.h"
/* gpio interrupt handler */
#include <gpio_rgb_example.h>

/* Xilinx includes. */
#include "xscutimer.h"
#include "xscugic.h"
#include "FreeRTOS_tick_config.h"

#define RETURN_ON_FAILURE(x) if ((x) != XST_SUCCESS) return XST_FAILURE;

/*
 * Structure for interrupt id, handler and callback reference
 */
typedef struct {
	u8 id;
	XInterruptHandler handler;
	void *pvCallbackRef;
	u32 priority;       // Priority of the interrupt
	u32 triggerType;    // Trigger type of the interrupt
} ivt_t;


/****************** Static Global Variable Definitions ***********************/
//#define XPAR_FABRIC_AUDIO_FORMATTER_0_IRQ_MM2S_INTR 61U
//#define XPAR_FABRIC_AUDIO_FORMATTER_0_IRQ_S2MM_INTR 62U
//#define XPAR_FABRIC_I2S_TRANSMITTER_0_IRQ_INTR 63U
//#define XPAR_FABRIC_I2S_RECEIVER_0_IRQ_INTR 64U
//#define XPAR_FABRIC_AXI_GPIO_1_IP2INTC_IRPT_INTR 65U
 /* interrupt vector tables*/
/* includes all interrupts processed by the PS7 */
// Interrupt Priorities
#define GPIO_INTR_PRIORITY          			XPAR_FABRIC_AXI_GPIO_2_IP2INTC_IRPT_INTR
#define I2S_TX_INTR_PRIORITY        			XPAR_FABRIC_I2S_TRANSMITTER_0_IRQ_INTR
#define I2S_RX_INTR_PRIORITY        			XPAR_FABRIC_I2S_RECEIVER_0_IRQ_INTR
#define AUDIO_FMT_S2MM_INTR_PRIORITY 			XPAR_FABRIC_AUDIO_FORMATTER_0_IRQ_S2MM_INTR
#define AUDIO_FMT_MM2S_INTR_PRIORITY 			XPAR_FABRIC_AUDIO_FORMATTER_0_IRQ_MM2S_INTR
#define IIC_INTR_PRIORITY           			IIC_INT_VEC_ID
#define TTC0_INTR_PRIORITY						XPAR_XTTCPS_0_INTR
// ... other priorities ...


#define XSCUGIC_INT_CFG_EDGE_SENSITIVE 	0x3 // rising edge

XStatus fnInitInterruptController(XScuGic *psIntc);
void fnEnableInterrupts(XScuGic *psIntc, const ivt_t *prgsIvt, unsigned int csIVectors);

extern volatile u8 xIsGICInitialized;

extern void InterrupController_Init(void);


/* interrupt controller to be accessed by other modules */
extern XScuGic xInterruptController;

#endif /* INTC_H_ */
