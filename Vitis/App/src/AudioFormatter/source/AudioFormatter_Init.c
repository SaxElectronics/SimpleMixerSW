

#include "AudioFormatter.h"


AudioFormatter_HwConfig HwConfig_S2MM;
AudioFormatter_HwConfig HwConfig_MM2S;

XAudioFormatterHwParams af_mm2s_hw_params = {
		/* buf_addr */
		0x000000000000C00UL,
		/* active_ch */
		2,
		/* bits_per_sample */
		BIT_DEPTH_32,
		/* periods */
		AF_NUMBER_OF_PERIODS,
		/* bytes_per_period */
		/* period size must be multiples of 32* NumberOfChannels */
		/* 8*32*2 would equal 128*4 FIFO buffer size in I2S */
		AF_BYTES_PER_PERIOD};
XAudioFormatterHwParams af_s2mm_hw_params = {
		/* buf_addr */
		0x0000000000000000UL,
		/* active_ch */
		2,
		/* bits_per_sample */
		BIT_DEPTH_32,
		/* periods */
		AF_NUMBER_OF_PERIODS,
		/* bytes_per_period */
		/* 8*32*2 would equal 128*4 FIFO buffer size in I2S */
		AF_BYTES_PER_PERIOD};



/*****************************************************************************/
/**
 * This function is the main init function of the audio formatter
 * using Interrupts.
 *
 * @param	None.
 *
 * @return	XST_SUCCESS to indicate success, else XST_FAILURE to indicate a
 *		Failure.
 *
 * @note	None.
 *
******************************************************************************/
void AudioFormatter_Init(void)
{

	//af_mm2s_hw_params.buf_addr = (u64)(u32)(&TxBuf[0]);
	//af_s2mm_hw_params.buf_addr = (u64)(u32)(&RxBuf[0]);
	TxBufAdr = (u32) af_mm2s_hw_params.buf_addr;
	RxBufAdr = (u32) af_s2mm_hw_params.buf_addr;

	AF_RxbufferPtr = (u32*)  (uintptr_t) (  (af_s2mm_hw_params.buf_addr )  );
	AF_TxbufferPtr = (u32*)  (uintptr_t) (  (af_mm2s_hw_params.buf_addr )  );

	u32 Status;
	XAudioFormatter *AFInstancePtr = &AFInstance;

	xil_printf("\r\n-----------------------------------------------\r\n");
	xil_printf(" Xilinx Audio Formatter Example Design %s\r\n",
		XAUDIO_FORMATTER_SW_VER);
	xil_printf("	(c) 2018 by Xilinx Inc.\r\n");

	Status = InitializeAudioFormatter(AFInstancePtr);
	if (Status == XST_FAILURE)
	{
	xil_printf("\nAudio Formatter Init failed\n");
	}

}

/*****************************************************************************/
/**
 * This function does the lookup and intialization of the audio formatter.
 *
 * @param	AFInstancePtr is a pointer to audio formatter driver instance
 *
 * @return	XST_SUCCESS if the call is successful, otherwise XST_FAILURE.
 *
 * @note	None.
 *
******************************************************************************/
u32 InitializeAudioFormatter(XAudioFormatter *AFInstancePtr)
{
	u32 Status;
//	u32 offset;
//	XAudioFormatter_Config *AFConfig;
	/*
	 * Lookup and Initialize the audio formatter so that it's ready to use.
	 */
	XAudioFormatter_Config *CfgPtr = NULL;

	CfgPtr = XAudioFormatter_LookupConfig(AF_DEVICE_ID);
	if (CfgPtr == NULL) {
		//InstancePtr->IsReady = 0;
		return XST_DEVICE_NOT_FOUND;
	}
	Status= XAudioFormatter_CfgInitialize(AFInstancePtr, CfgPtr);

	// Status = XAudioFormatter_Initialize(&AFInstance, AF_DEVICE_ID);
	if (Status != XST_SUCCESS)
		return XST_FAILURE;

	if (AFInstancePtr->s2mm_presence == 1)
	{

		if (Status == XST_SUCCESS) {
		//	XScuGic_Enable(&Intc, AF_S2MM_INTERRUPT_ID);
		} else {
			xil_printf("Failed to register AF interrupt handler");
			return XST_FAILURE;
		}
		/* change instance to point to AF S2MM */
		AFInstancePtr->ChannelId = XAudioFormatter_S2MM;
		/* Set Callback function for Interrupt On Complete handler */
		XAudioFormatter_SetS2MMCallback(AFInstancePtr,
			XAudioFormatter_IOC_Handler, XS2MMAFCallbackInterruptOnComplete,
			(void *)AFInstancePtr);
		XAudioFormatter_InterruptEnable(AFInstancePtr,
			XAUD_CTRL_IOC_IRQ_MASK);
		/* Set Callback function for TimeOut handler */
		XAudioFormatter_SetS2MMCallback(AFInstancePtr,
				XAudioFormatter_TIMEOUT_Handler, XS2MMAFCallbackTimeOut,
				(void *)AFInstancePtr);
		XAudioFormatter_InterruptEnable(AFInstancePtr,
				XAUD_CTRL_TIMEOUT_IRQ_MASK);
		/* Set Callback function for Error handler */
		XAudioFormatter_SetS2MMCallback(AFInstancePtr,
				XAudioFormatter_ERROR_Handler, XS2MMAFCallbackError,
				(void *)AFInstancePtr);
		XAudioFormatter_InterruptEnable(AFInstancePtr,
				XAUD_CTRL_ERR_IRQ_MASK);
		XAudioFormatterSetS2MMTimeOut(AFInstancePtr, AF_S2MM_TIMEOUT);
		/* Set Audio Sampling Frequency and Master clock */
		XAudioFormatterSetHwParams(AFInstancePtr, &af_s2mm_hw_params);
		/* Start the Core */
		XAudioFormatterDMAStart(AFInstancePtr);
		/* Read the current configuration of the S2MM module */
		AF_GetHwConfig(AFInstancePtr, &HwConfig_S2MM);
	}
	if (AFInstancePtr->mm2s_presence == 1)
	{
		/* change instance to point to AF MM2S */

		AFInstancePtr->ChannelId = XAudioFormatter_MM2S;
		/* MM2S Interrupt on Complete Callback Function */
		XAudioFormatter_SetMM2SCallback(AFInstancePtr,
			XAudioFormatter_IOC_Handler, XMM2SAFCallbackInterruptOnComplete,
			(void *)AFInstancePtr);
		XAudioFormatter_InterruptEnable(AFInstancePtr,
			XAUD_CTRL_IOC_IRQ_MASK);
		/* MM2S Error Callback function */
		XAudioFormatter_SetMM2SCallback(AFInstancePtr,
				XAudioFormatter_ERROR_Handler, XMM2SAFCallbackError,
					(void *)AFInstancePtr);
		XAudioFormatter_InterruptEnable(AFInstancePtr,
						XAUD_CTRL_ERR_IRQ_MASK);
		/* Set Audio Sampling Frequency and Master clock */
		XAudioFormatterSetFsMultiplier(AFInstancePtr, AF_MCLK, AF_FS);
		XAudioFormatterSetHwParams(AFInstancePtr, &af_mm2s_hw_params);
		/* Start the Core */
		XAudioFormatterDMAStart(AFInstancePtr);
		/* Read the current configuration of the MM2S module */
		AF_GetHwConfig(AFInstancePtr, &HwConfig_MM2S);
	}
	return Status;
}
