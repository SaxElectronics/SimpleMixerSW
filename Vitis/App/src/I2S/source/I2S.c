
/*
 * I2S.c: Provide functions to initialize and operate the I2S interface
 *
 * This file contains functions to initialize the audio formatter, to configure/reconfigure
 * and operate it properly.
 *
 */

/*
 * includes
 */

#include "I2S.h"
#include "xi2srx.h"
#include "xparameters.h"
#include "xi2srx.h"
#include "xi2srx_hw.h"
#include "stdbool.h"

/*
 * global variables
 */
XI2s_Rx I2S_Rx_Instance;
XI2srx_Config * pI2S_Rx_Config;
u32 Master_Clk;
u32 SamplingFreq;
// Initialize the I2S receiver


void I2S_Init(void)
{
	Master_Clk = 49152;
	SamplingFreq = 48000;
	u32  XstStatus;

	pI2S_Rx_Config = XI2s_Rx_LookupConfig(XPAR_I2S_RECEIVER_0_DEVICE_ID);
	XstStatus = XI2s_Rx_CfgInitialize(&I2S_Rx_Instance,pI2S_Rx_Config, XPAR_I2S_RECEIVER_0_BASEADDR);
	if (XST_INVALID_VERSION == XstStatus)
	{
        xil_printf("I2S Receiver: Invalid version! \r\n");
	}
	else if (XST_DEVICE_NOT_FOUND == XstStatus)
	{
        xil_printf("I2S Receiver: Device not found! \r\n");
	};
	XI2s_Rx_IntrEnable(&I2S_Rx_Instance,XI2S_RX_GINTR_EN_MASK);
	XstStatus = XI2s_Rx_SetChMux(&I2S_Rx_Instance, XI2S_RX_CHID0, XI2S_RX_CHMUX_XI2S_01);
	if (XST_SUCCESS != XstStatus)
	{
	    xil_printf("I2S Receiver: Setting MUX Channels failed! \r\n");
	};
	XstStatus = XI2s_Rx_SetSclkOutDiv(&I2S_Rx_Instance,Master_Clk, SamplingFreq);
	if (XST_SUCCESS != XstStatus)
	{
        xil_printf("I2S Receiver: Setting SCKL Divider failed! \r\n");
	};

	XI2s_Rx_Enable(&I2S_Rx_Instance, true);
	Xil_Out32 ( (XPAR_XAUDIOFORMATTER_0_BASEADDR + 0x10), 1 ); // run the audio formatter
	u32 AudioFormatterRunStop = Xil_In32(XPAR_XAUDIOFORMATTER_0_BASEADDR + 0x10); // check if audio formatter is ran
}
