/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

/*
 * platform includes
 */
#include <gpio_rgb_example.h>
#include <platform.h>
#include <ps7_init.h>
#include <stdio.h>
#include <xiicps_driver.h>
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"
#include "xil_cache.h"
#include "xgpio.h"

/*
 * own includes
 */
/* I2S Tx and Rx */
#include "I2S.h"
/* audio formatter */
#include "AudioFormatter.h"
/* verbose outputs */
#include "verbose.h"
/* interrupt controller */
#include "intc.h"
/* gpio interrupt init */
/* I2C includes */

/* OS Includes */
#include "Tasks_Init.h"
#include "FreeRTOS_main.h"


/*
 * global variables
 */
/************************** Constant Definitions *****************************/

/********************* Global Variable Definitions ***************************/
//static XAxiDma sAxiDma;




int main()
{

	/* init platform */
    init_platform();
    /* enable the PL */
    ps7_post_config();

    SET_VERBOSE_FLAG();
	VERBOSE("Initializing...");


	/* Initialize the GPIO driver */
//	Status = XGpio_Initialize(&Gpio, XPAR_GPIO_1_DEVICE_ID);
//	if (Status != XST_SUCCESS) {
//		xil_printf("Gpio Initialization Failed\r\n");
//		return XST_FAILURE;
//	}

	/* Initialize Audio Formatter */
	AudioFormatter_Init();
	/* Initialize I2S Transmitter and Receiver */
	I2S_Init();
	/* initialize rgb GPIOs */
	GPIO_rgb_Init();

	/* initialize I2C */
	I2C_main_init();

	/* initialize Interrupt Controller */
	InterrupController_Init();

	/* setup HW config for OS and create OS tasks */
	FreeRTOS_Main_Init();
    print("Hello from Simple Mixer App\n\r");
	print("Successfully ran the Simple Mixer application\n\r");
	print("Entering the OS loop\n\r");

	/* decide when to start the scheduler */
	FreeRTOS_StartScheduler();
	/* code lines after FreeRTOS_StartScheduler won't be reached */


    cleanup_platform();
}
