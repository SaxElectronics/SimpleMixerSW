
/*
 * AudioFormatter.c: Provide functions to initialize and operate the audio formatter
 *
 * This file contains functions to initialize the audio formatter, to configure/reconfigure
 * and operate it properly.
 *
 */

#include "math.h"

/*
 * Xilinx Platform Includes
 */
#include "xaudioformatter.h"

/*
 * own includes
 */
#include "AudioFormatter.h"
#include "I2S.h"

/* Here is a list of currently activated AF interrupt handlers */
/*
 * S2MM Function Handlers:
 * ---------------------------
 * XS2MMAFCallbackInterruptOnComplete -  when an Audio Block is received this interrupt handler gets called
 * XS2MMAFCallbackTimeOut			  -  when a timeout is exceeded, this interrupt handler gets called
 * XS2MMAFCallbackError				  -  if an error occurs during the S2MM read, this interrupt handler is called
 */


/*
 * MM2S Function Handlers:
 * ---------------------------
 * XMM2SAFCallbackInterruptOnComplete -  when an Audio Block is received this interrupt handler gets called
 *
 */

/*
 * global variables
 */
XAudioFormatter AFInstance;
XAudioFormatter *AFInstancePtr = &AFInstance;

/* S2MM Interrupt Status */
u32 S2MMAFIntrReceived;
u32 AF_S2MM_IOC_counter;
u32 S2MMAFIntrTimeOut;
u32 S2MMAFIntrError;

/* MM2S Interrupt Status */
u32 MM2SAFIntrReceived;
u32 AF_MM2S_IOC_counter;

u32 MM2SAFIntrTimeOut;
u32 MM2SAFIntrError;

/* Debugging Variables */
u32 S2MM_NoChannels;
u32 S2MM_PCMDataBitsWidth;
u32 S2MM_PCMNoPeriods;

u32 MM2S_NoChannels;
u32 MM2S_PCMDataBitsWidth;
u32 MM2S_PCMNoPeriods;

u32 s2mm_NumberOfBytestransfered;
u32 mm2s_NumberOfBytestransfered;

u32 s2mm_DMA_errors;
u32 s2mm_DMA_TimeOut_error;
u32 s2mm_DMA_Decode_error;
u32 s2mm_DMA_Slave_error;
u32 s2mm_DMA_halt;
u32 s2mm_DMA_ctrl_state;

s2mm_DMA_errors_t s2mm_AF_errors;

u32 mm2s_DMA_TimeOut_error;
u32 mm2s_DMA_Decode_error;
u32 mm2s_DMA_Slave_error;
u32 mm2s_DMA_errors;
u32 mm2s_DMA_halt;
u32 mm2s_DMA_ctrl_state;

mm2s_DMA_errors_t mm2s_AF_errors;

//typedef struct {u64 buf_addr; u32 active_ch; u32 bits_per_sample; u32 periods; u32 bytes_per_period;
//} XAudioFormatterHwParams;
/* 8*64 = 512 bytes buffer size */
//u8 ChStatBuff[XAUD_CHSTAT_NUMBER_OF_BYTES];
u32 RxBuf[AF_NUMBER_OF_PERIODS * AF_AUDIOSAMPLES_PER_PERIOD];
u32 TxBuf[AF_NUMBER_OF_PERIODS * AF_AUDIOSAMPLES_PER_PERIOD];
uint32_t audio_sample_in_period_l[AF_AUDIOSAMPLES_PER_PERIOD/2], audio_sample_in_period_r[AF_AUDIOSAMPLES_PER_PERIOD/2];
uint32_t audio_sample_in_period_lr[AF_AUDIOSAMPLES_PER_PERIOD];

u32* ptrToRxBuf = RxBuf;
u32* ptrToTxBuf = TxBuf;

float audio_sample_l = 0;
float audio_sample_r = 0;


int samplingRate = 48000; // Sampling rate in Hz
double frequency = 440.0; // Frequency of the "A" note in Hz

int durationSeconds = 10; // Duration of the audio stream in seconds
int numSamples = 48000 * 10;

static uint32_t audio_sample_in_period_test_tone[48000 * 10] = {0}; // Buffer to store left channel audio samples

static u32 current_period_s2mm;
static u32 current_period_mm2s;

u32* AF_bufferPtr;
u32* AF_RxbufferPtr;
u32* AF_TxbufferPtr;

u32* AF_PeriodPtr_s2mm;
u32* AF_PeriodPtr_mm2s;

u32 TxBufAdr;
u32 RxBufAdr;

AudioFormatter_HwConfig HwConfig_S2MM;
AudioFormatter_HwConfig HwConfig_MM2S;

XAudioFormatterHwParams af_mm2s_hw_params = {
		/* buf_addr */
		0x0000000000000000UL,
		/* active_ch */
		2,
		/* bits_per_sample */
		BIT_DEPTH_24,
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
		BIT_DEPTH_24,
		/* periods */
		AF_NUMBER_OF_PERIODS,
		/* bytes_per_period */
		/* 8*32*2 would equal 128*4 FIFO buffer size in I2S */
		AF_BYTES_PER_PERIOD};



const double PI = 3.141592653589793238463;

#define XAUD_CHSTAT_NUMBER_OF_BYTES  24
int curren_period_idx = 0;

u32 	lSample = 0;
u32 	rSample = 0;

/*
 * function prototypes
 */

u32 InitializeAudioFormatter(XAudioFormatter *AFInstancePtr);
/* S2MM Callback functions */
void *XS2MMAFCallbackInterruptOnComplete(void *data);
void *XS2MMAFCallbackTimeOut(void *data);
void *XS2MMAFCallbackError(void *data);

/* MM2S Callback functions */
void *XMM2SAFCallbackInterruptOnComplete(void *data);
void *XMM2SAFCallbackError(void *data);
void *XMM2SAFCallbackTimeOut(void *data);

void AF_ReadAudioSamples(XAudioFormatter *AFInstancePtr);

u32 XAudioFormatter_GetStatusErrors(XAudioFormatter *InstancePtr, u32 mask);

InterruptCounters_t AllInterruptCounters;



/**
 * @brief Processes I2S receive and transmit interrupt status and handles DMA operations.
 *
 * This function monitors the I2S and Audio Formatter for both receive and transmit interrupts.
 * Based on the status of the interrupts and DMA HALT states, it updates counters and manages
 * the audio data processing. This function can be integrated into an RTOS task or called cyclically.
 */
void ProcessI2SInterruptsAndDMA(void)
{


    AFInstancePtr->ChannelId = XAudioFormatter_S2MM;
    s2mm_DMA_halt = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_DMA_HALT_MASK);
    s2mm_DMA_ctrl_state = XAudioFormatter_getDMAStatus(&AFInstance);
    s2mm_AF_errors.s2mm_DMA_ctrl_state = s2mm_DMA_ctrl_state;
    s2mm_AF_errors.s2mm_DMA_halt = s2mm_DMA_halt;
    I2sRxIntrAesComplete = 1;

    /* What to do when both Rx and S2MM interrupts received? */
    if ((I2sRxIntrAesComplete == 1 && S2MMAFIntrReceived == 1) && (!s2mm_DMA_halt))
    {
        I2sRxIntrCount++;

        // Potential operations on audio data can be added here

        /* Reset variables for next run */
        I2sRxIntrAesComplete = 0;
        S2MMAFIntrReceived = 0;
    }

    AFInstancePtr->ChannelId = XAudioFormatter_MM2S;
    mm2s_DMA_halt = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_DMA_HALT_MASK);
    mm2s_DMA_ctrl_state = XAudioFormatter_getDMAStatus(&AFInstance);
    I2sTxIntrAesComplete = 1;

    /* What to do when both Tx and MM2S interrupts received? */
    if ((I2sTxIntrAesComplete == 1 && MM2SAFIntrReceived == 1) && (!mm2s_DMA_halt))
    {
        I2sTxIntrCount++;

        // Potential operations on audio data can be added here

        /* Reset variables for next run */
        I2sTxIntrAesComplete = 0;
        MM2SAFIntrReceived = 0;
    }
}


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

	if (AFInstancePtr->s2mm_presence == 1) {
//		XScuGic_Connect
//		Status = XScuGic_Connect(&Intc, AF_S2MM_INTERRUPT_ID,
//			(XInterruptHandler)XAudioFormatterS2MMIntrHandler,
//			(void *)AFInstancePtr);
		if (Status == XST_SUCCESS) {
		//	XScuGic_Enable(&Intc, AF_S2MM_INTERRUPT_ID);
		} else {
			xil_printf("Failed to register AF interrupt handler");
			return XST_FAILURE;
		}
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
		XAudioFormatterDMAStart(AFInstancePtr);
		/* Read the current configuration of the S2MM module */
		AF_GetHwConfig(AFInstancePtr, &HwConfig_S2MM);
	}
	if (AFInstancePtr->mm2s_presence == 1) {
//		Status = XScuGic_Connect(&Intc, AF_MM2S_INTERRUPT_ID,
//			(XInterruptHandler)XAudioFormatterMM2SIntrHandler,
//			(void *)AFInstancePtr);
//		if (Status == XST_SUCCESS) {
//			XScuGic_Enable(&Intc, AF_MM2S_INTERRUPT_ID);
//		} else {
//			xil_printf("Failed to register AF interrupt handler");
//			return XST_FAILURE;
//		}
		AFInstancePtr->ChannelId = XAudioFormatter_MM2S;
		/* MM2S Interrupt on Complete Callback Function */
		XAudioFormatter_SetMM2SCallback(AFInstancePtr,
			XAudioFormatter_IOC_Handler, XMM2SAFCallbackInterruptOnComplete,
			(void *)AFInstancePtr);
		XAudioFormatter_InterruptEnable(AFInstancePtr,
			XAUD_CTRL_IOC_IRQ_MASK);
		/* MM2S Error Callback function */
//		XAudioFormatter_SetMM2SCallback(AFInstancePtr,
//				XAudioFormatter_ERROR_Handler, XMM2SAFCallbackError,
//					(void *)AFInstancePtr);
//		XAudioFormatter_InterruptEnable(AFInstancePtr,
//						XAUD_CTRL_ERR_IRQ_MASK);
		/* Set Audio Sampling Frequency and Master clock */
		XAudioFormatterSetFsMultiplier(AFInstancePtr, AF_MCLK, AF_FS);
		XAudioFormatterSetHwParams(AFInstancePtr, &af_mm2s_hw_params);
		XAudioFormatterDMAStart(AFInstancePtr);
		/* Read the current configuration of the MM2S module */
		AF_GetHwConfig(AFInstancePtr, &HwConfig_MM2S);
	}
	return Status;
}



int32_t SampleSaturate (float inSample) {

    /*
     * Max sample value can be +/- 2^31. So before back-conversion from float to int_32 we need to saturate the sample (otherwise distorted sound might appear)
     */

    if (inSample > 2147400000.0f) inSample = 2147400000.0f;
    if (inSample < -2147400000.0f) inSample = -2147400000.0f;
    return (int32_t) roundf(inSample);
}


/*****************************************************************************/
/**
 *
 * This function is called from the interrupt handler of audio formatter core.
 * After the first S2MM interrupt is received the interrupt_flag is set here.
 *
 * @return
 *
 * @note	This function assumes a Microblaze or ARM system and no
 *	operating system is used.
 *
*******************************************************************************/
void *XS2MMAFCallbackInterruptOnComplete(void *data)
{
	XAudioFormatter *AFInstancePtr = (XAudioFormatter *)data;
	/* clear interrupt flag */
	S2MMAFIntrReceived = 1;
	AF_S2MM_IOC_counter++;
	AllInterruptCounters.AF_S2MM_IOC_counter++;

	AFInstancePtr->ChannelId = XAudioFormatter_S2MM;
	AF_RxbufferPtr = (u32*)  (uintptr_t) (  (af_s2mm_hw_params.buf_addr )  );

	/* Stop the S2MM DMA */
	//XAudioFormatterDMAStop(&AFInstance);
	s2mm_DMA_errors = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_ERRORS_MASK);
	s2mm_DMA_TimeOut_error = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_TIMEOUT_ERR_MASK);
	s2mm_DMA_Decode_error = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_DECODE_ERR_MASK);
	s2mm_DMA_Slave_error = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_SLAVE_ERR_MASK);




	/* get the number of bytes transfered to memory */
	s2mm_NumberOfBytestransfered = XAudioFormatterGetDMATransferCount(&AFInstance);
    xil_printf("Audio Formatter current channel ID: %d\r\n",(XAudioFormatter_ChannelId) AFInstancePtr->ChannelId);

//	xil_printf(" Xilinx Audio Formatter DMA number of bytes transfered %s\r\n",
//			(int)s2mm_NumberOfBytestransfered);

	//AF_ProcessAudioData();
	AF_ReadAudioData();
	AF_WriteAudioData();


//	    }

	/* start the MM2S transfer */
	/* transfer data to the I2S transmitter */
	//AFInstancePtr->ChannelId = XAudioFormatter_MM2S;
	//XAudioFormatterDMAStop(&AFInstance);
	return(data);
}



/*****************************************************************************/
/**
 *
 * This function does the audio processing. It reads from the AF S2MM Buffer
 * processes the audio and writes the data to AF MM2S Buffer
 *
 * @return
 *
 * @note	This function assumes a Microblaze or ARM system and no
 *	operating system is used.
 *
*******************************************************************************/
void AF_ProcessAudioData(void)
{
/* reset if last period reached */
	if (current_period_s2mm >= AF_NUMBER_OF_PERIODS)
	{
		current_period_s2mm = 0;
	}
	if (current_period_mm2s >= AF_NUMBER_OF_PERIODS)
	{
		current_period_mm2s = 0;
	}
	// Check if the pointer is outside the buffer range
	if (ptrToRxBuf < RxBuf || ptrToRxBuf >= RxBuf + AF_NUMBER_OF_PERIODS * AF_AUDIOSAMPLES_PER_PERIOD) {
		// Pointer is outside the buffer range, reset it to the beginning of the buffer
		ptrToRxBuf = RxBuf;
	}
	// Check if the pointer is outside the buffer range
	if (ptrToTxBuf < TxBuf || ptrToTxBuf >= TxBuf + AF_NUMBER_OF_PERIODS * AF_AUDIOSAMPLES_PER_PERIOD) {
		// Pointer is outside the buffer range, reset it to the beginning of the buffer
		ptrToTxBuf = TxBuf;
	}
    uint32_t sample;
   // bufferPtr = &af_mm2s_hw_params.buf_addr;
	  // Loop through all periods
	   // Loop through all periods
//	    for (period = 0; period < AF_NUMBER_OF_PERIODS; period++)
//	    {

			AF_RxbufferPtr = (u32*)  (uintptr_t) (  (af_s2mm_hw_params.buf_addr )  );
			AF_TxbufferPtr = (u32*)  (uintptr_t) (  (af_mm2s_hw_params.buf_addr )  );

	        // get the pointer to the next sample
    		AF_RxbufferPtr += current_period_s2mm * AF_AUDIOSAMPLES_PER_PERIOD;
    		AF_TxbufferPtr += current_period_mm2s * AF_AUDIOSAMPLES_PER_PERIOD;

	        // Loop through all samples in the period
	        /* this pointer will be used inside one period */
	        AF_PeriodPtr_s2mm = AF_RxbufferPtr;
	        AF_PeriodPtr_mm2s = AF_TxbufferPtr;

	        for (sample = 0; sample < AF_AUDIOSAMPLES_PER_PERIOD; sample+=2)
	        {
	            // Read audio samples for left and right channels from the buffer
//	            uint32_t *audio_sample_ptr = (uint32_t*)(uint64_t)AF_bufferPtr + sample * AF_NUMBER_OF_CHANNELS;
	        	audio_sample_in_period_l[sample/2] = *AF_PeriodPtr_s2mm;
	        	audio_sample_in_period_lr[sample] = *AF_PeriodPtr_s2mm;
	        	audio_sample_l = *AF_PeriodPtr_s2mm;
	        	* ptrToRxBuf = *AF_PeriodPtr_s2mm;
	        	ptrToRxBuf++;
	            AF_PeriodPtr_s2mm++;
	            audio_sample_in_period_r[sample/2] = *AF_PeriodPtr_s2mm;
	        	audio_sample_in_period_lr[sample+1] = *AF_PeriodPtr_s2mm;
	        	audio_sample_r = *AF_PeriodPtr_s2mm;
	        	* ptrToRxBuf = *AF_PeriodPtr_s2mm;
	        	ptrToRxBuf++;
	            AF_PeriodPtr_s2mm++;

	            *AF_PeriodPtr_mm2s = audio_sample_in_period_l[sample/2];
	            * ptrToTxBuf =  *AF_PeriodPtr_mm2s;
	            ptrToTxBuf++;
				AF_PeriodPtr_mm2s++;
				*AF_PeriodPtr_mm2s = audio_sample_in_period_r[sample/2];
	            * ptrToTxBuf =  *AF_PeriodPtr_mm2s;
	            ptrToTxBuf++;
				AF_PeriodPtr_mm2s++;

	            //xil_printf("Audio Formatter audio sample left: %d\r\n", (int)audio_sample_in_period_l[sample]);
				//xil_printf("Audio Formatter audio sample right: %d\r\n", (int)audio_sample_in_period_r[sample]);


	            // Process the audio samples or store them as needed
	            // ...
	        }
	        current_period_s2mm++;
	        current_period_mm2s++;
}


/*****************************************************************************/
/**
 *
 * This function reads the audio data from the s2mm buffer per DMA period
 *
 * @return
 *
 * @note	This function assumes a Microblaze or ARM system and no
 *	operating system is used.
 *
*******************************************************************************/
void AF_ReadAudioData(void)
{
	/* reset if last period reached */
	if (current_period_s2mm >= AF_NUMBER_OF_PERIODS)
	{
		current_period_s2mm = 0;
	}
	// Check if the pointer is outside the buffer range
	if (ptrToRxBuf < RxBuf || ptrToRxBuf >= RxBuf + AF_NUMBER_OF_PERIODS * AF_AUDIOSAMPLES_PER_PERIOD) {
		// Pointer is outside the buffer range, reset it to the beginning of the buffer
		ptrToRxBuf = RxBuf;
	}
    uint32_t sample;
	AF_RxbufferPtr = (u32*)  (uintptr_t) (  (af_s2mm_hw_params.buf_addr )  );

	AF_RxbufferPtr += current_period_s2mm * AF_AUDIOSAMPLES_PER_PERIOD;

	// Loop through all samples in the period
	/* this pointer will be used inside one period */
	AF_PeriodPtr_s2mm = AF_RxbufferPtr;

	for (sample = 0; sample < AF_AUDIOSAMPLES_PER_PERIOD; sample+=2)
	{
		// Read audio samples for left and right channels from the buffer
//	            uint32_t *audio_sample_ptr = (uint32_t*)(uint64_t)AF_bufferPtr + sample * AF_NUMBER_OF_CHANNELS;
		audio_sample_in_period_l[sample/2] = *AF_PeriodPtr_s2mm;
		audio_sample_in_period_lr[sample] = *AF_PeriodPtr_s2mm;
		audio_sample_l = *AF_PeriodPtr_s2mm;
		* ptrToRxBuf = *AF_PeriodPtr_s2mm;
		ptrToRxBuf++;
		AF_PeriodPtr_s2mm++;
		audio_sample_in_period_r[sample/2] = *AF_PeriodPtr_s2mm;
		audio_sample_in_period_lr[sample+1] = *AF_PeriodPtr_s2mm;
		audio_sample_r = *AF_PeriodPtr_s2mm;
		* ptrToRxBuf = *AF_PeriodPtr_s2mm;
		ptrToRxBuf++;
		AF_PeriodPtr_s2mm++;

		//xil_printf("Audio Formatter audio sample left: %d\r\n", (int)audio_sample_in_period_l[sample]);
		//xil_printf("Audio Formatter audio sample right: %d\r\n", (int)audio_sample_in_period_r[sample]);


		// Process the audio samples or store them as needed
		// ...
		}
		current_period_s2mm++;
}


/*****************************************************************************/
/**
 *
 * This function reads the audio data from the s2mm buffer per DMA period
 *
 * @return
 *
 * @note	This function assumes a Microblaze or ARM system and no
 *	operating system is used.
 *
*******************************************************************************/
void AF_WriteAudioData(void)
{
	/* reset if last period reached */
	if (current_period_mm2s >= AF_NUMBER_OF_PERIODS)
	{
		current_period_mm2s = 0;
	}
	// Check if the pointer is outside the buffer range
	if (ptrToTxBuf < TxBuf || ptrToTxBuf >= TxBuf + AF_NUMBER_OF_PERIODS * AF_AUDIOSAMPLES_PER_PERIOD) {
		// Pointer is outside the buffer range, reset it to the beginning of the buffer
		ptrToTxBuf = TxBuf;
	}

    uint32_t sample;
	AF_TxbufferPtr = (u32*)  (uintptr_t) (  (af_mm2s_hw_params.buf_addr )  );

	AF_TxbufferPtr += current_period_mm2s * AF_AUDIOSAMPLES_PER_PERIOD;

	// Loop through all samples in the period
	/* this pointer will be used inside one period */
	AF_PeriodPtr_mm2s = AF_TxbufferPtr;

	for (sample = 0; sample < AF_AUDIOSAMPLES_PER_PERIOD; sample+=2)
	{

		*AF_PeriodPtr_mm2s = audio_sample_in_period_l[sample/2];
		* ptrToTxBuf =  *AF_PeriodPtr_mm2s;
		ptrToTxBuf++;
		AF_PeriodPtr_mm2s++;
		*AF_PeriodPtr_mm2s = audio_sample_in_period_r[sample/2];
		* ptrToTxBuf =  *AF_PeriodPtr_mm2s;
		ptrToTxBuf++;
		AF_PeriodPtr_mm2s++;

		//xil_printf("Audio Formatter audio sample left: %d\r\n", (int)audio_sample_in_period_l[sample]);
		//xil_printf("Audio Formatter audio sample right: %d\r\n", (int)audio_sample_in_period_r[sample]);


		// Process the audio samples or store them as needed
		// ...
	}
	current_period_mm2s++;
}


/*****************************************************************************/
/**
 *
 * This function is called from the interrupt handler of audio formatter core.
 * When a S2MM timeout error occurs.
 *
 * @return
 *
 * @note	This function assumes a Microblaze or ARM system and no
 *	operating system is used.
 *
*******************************************************************************/
void *XS2MMAFCallbackTimeOut(void *data)
{
	XAudioFormatter *AFInstancePtr = (XAudioFormatter *)data;
	/* clear interrupt flag */
	S2MMAFIntrTimeOut = 1;
	AFInstancePtr->ChannelId = XAudioFormatter_S2MM;
	xil_printf("S2MM timeout occured!\r\n");
	//AF_ReadAudioSamples(&AFInstance);
	XAudioFormatterDMAStop(&AFInstance);

	return(data);
}

/*****************************************************************************/
/**
 *
 * This function is called from the interrupt handler of audio formatter core,
 * when a S2MM error occurs.
 *
 * @return
 *
 * @note	This function assumes a Microblaze or ARM system and no
 *	operating system is used.
 *
*******************************************************************************/
void *XS2MMAFCallbackError(void *data)
{
	XAudioFormatter *AFInstancePtr = (XAudioFormatter *)data;
	/* clear interrupt flag */
	S2MMAFIntrError = 1;
	AFInstancePtr->ChannelId = XAudioFormatter_S2MM;
	xil_printf("S2MM timeout occured!\r\n");

	//AF_ReadAudioSamples(&AFInstance);
	XAudioFormatterDMAStop(&AFInstance);
	return(data);
}
/*****************************************************************************/
/**
 *
 * This function gets the current config of the audio formatter MM2S or S2MM module
 *
 * @param	AFInstancePtr is a pointer to audio formatter driver instance
 *
 * @param	AudioFormatter_HwConfig is a pointer to the hardware config structure
 * 	/ Channel Id M2SS or S2MM
 * 	XAudioFormatter_ChannelId ChannelId;
 *	/ Audio Formatter Control Register /
 *	u32 AF_Ctrl;
 *	/ Audio Formatter Period Config Register /
 *	u32 AF_PrdCfg;
 *	/ Audio Formatter Number of Channels /
 *	u32 NumberOfChannels;
 *	/ Audio Data Bits Width /
 *	u32 AudioDataBitsWidth;
 *	/ Number of Periods /
 *	u32 NumberOfPeriods;
 *	/ Period Size /
 *	u32 PeriodSize;
 *
 * @return
 *
 * @note
 *
*******************************************************************************/
void AF_GetHwConfig(XAudioFormatter *AFInstancePtr, AudioFormatter_HwConfig* AFHwConfigPtr )
{
	u32 offset;
	AFHwConfigPtr->ChannelId = AFInstancePtr->ChannelId;
	if (AFHwConfigPtr->ChannelId == XAudioFormatter_S2MM)
	{
		offset = XAUD_FORMATTER_S2MM_OFFSET;
		VERBOSE("AF Instance is S2MM.\n");
	}
	else if ((AFHwConfigPtr->ChannelId == XAudioFormatter_MM2S))
	{
		offset = XAUD_FORMATTER_MM2S_OFFSET;
		VERBOSE("AF Instance is MM2S.\n");
	}
	else
	{
		offset = 0;
	}

	/* read out the number of channels, Data Bits Width, Number of Periods */
	AFHwConfigPtr->AF_Ctrl = XAudioFormatter_ReadReg(AFInstancePtr->BaseAddress,
			offset + XAUD_FORMATTER_CTRL);
	AFHwConfigPtr->NumberOfChannels = AFHwConfigPtr->AF_Ctrl & XAUD_CTRL_ACVCHNL_S_MASK; /* read out number of active channels */
	/* shift right with appropriate bit position to get the number of channels */
	AFHwConfigPtr->NumberOfChannels >>= XAUD_CTRL_ACTIVE_CH_SHIFT;
	VERBOSE("Number of Channels is: ");
	VERBOSE("%d",(AFHwConfigPtr->NumberOfChannels));
	u32 bits_per_sample = (AFHwConfigPtr->AF_Ctrl & (XAUD_CTRL_DATA_WIDTH_MASK << XAUD_CTRL_DATA_WIDTH_SHIFT) );
	bits_per_sample >>=  XAUD_CTRL_DATA_WIDTH_SHIFT;
	switch (bits_per_sample) {
			case BIT_DEPTH_8:
				AFHwConfigPtr->AudioDataBitsWidth = 8; /* 8 Bits*/
				break;
			case BIT_DEPTH_16:
				AFHwConfigPtr->AudioDataBitsWidth = 16; /* 16 Bits*/
				break;
			case BIT_DEPTH_20:
				AFHwConfigPtr->AudioDataBitsWidth = 20; /* 20 Bits*/
				break;
			case BIT_DEPTH_24:
				AFHwConfigPtr->AudioDataBitsWidth = 24; /* 24 Bits*/
				break;
			case BIT_DEPTH_32:
				AFHwConfigPtr->AudioDataBitsWidth = 32; /* 32 Bits*/
				break;
		}
	/* Get Period Config Register Content */
	AFHwConfigPtr->AF_PrdCfg = XAudioFormatter_ReadReg(AFInstancePtr->BaseAddress,
			offset + XAUD_FORMATTER_PERIOD_CONFIG);
	/* Get number of periods */
	AFHwConfigPtr->NumberOfPeriods = (AFHwConfigPtr->AF_PrdCfg & (XAUD_PERIOD_CFG_NOMBEROFPERIODS_MASK << XAUD_PERIOD_CFG_PERIODS_SHIFT ));
	AFHwConfigPtr->NumberOfPeriods>>= XAUD_PERIOD_CFG_PERIODS_SHIFT;
	VERBOSE("Number of Periods is: ");
	VERBOSE("%d",(AFHwConfigPtr->NumberOfPeriods));
	AFHwConfigPtr->PeriodSize = (AFHwConfigPtr->AF_PrdCfg & (XAUD_PERIOD_CFG_PERIODSIZE_MASK << XAUD_PERIOD_CFG_PERIODSIZE_SHIFT) );
	AFHwConfigPtr->PeriodSize >>= XAUD_PERIOD_CFG_PERIODSIZE_SHIFT;
	VERBOSE("Period Size is: ");
	VERBOSE("%d",(AFHwConfigPtr->PeriodSize));

}
/*****************************************************************************/
/**
 *
 * This function will read the audio samples
 *
 * @return
 *
 * @note
 *
*******************************************************************************/
void AF_ReadAudioSamples(XAudioFormatter *AFInstancePtr)
{

	u32 LSB_AudioAddress = XAudioFormatter_ReadReg(AFInstancePtr->BaseAddress,
				XAUD_FORMATTER_S2MM_OFFSET + XAUD_FORMATTER_BUFF_ADDR_LSB);
	if (LSB_AudioAddress)
	{
		xil_printf("LSB Audio Address from Receiver read.\r\n");
	}
	u32 MSB_AudioAddress = XAudioFormatter_ReadReg(AFInstancePtr->BaseAddress,
					XAUD_FORMATTER_S2MM_OFFSET + XAUD_FORMATTER_BUFF_ADDR_MSB);
	if (MSB_AudioAddress)
	{
		xil_printf("LSB Audio Address from Receiver read.\r\n");
	}
	/* copy the channel status information into the buffer */
//	XSdiAud_GetChStat(AFInstancePtr, &ChStatBuff[0]);
}

/*****************************************************************************/
/**
 *
 * This function generates a sine A
 *
 * @return
 *
 * @note
 *
*******************************************************************************/
void AF_GenerateSineWaveAndWriteToBuff(void)
{


	for (int i = 0; i < numSamples; i++) {
		double t = i / (double)samplingRate; // Time in seconds
		double sample = sin(2 * PI * frequency * t);
		// Map the sample value to the desired range for 24-bit PCM
		int pcmSample = (int)(sample * 8388607); // 24-bit signed PCM value
		audio_sample_in_period_test_tone[i] = pcmSample; // Store the PCM sample in the buffer
	}

}
/*****************************************************************************/
/**
 *
 * This function reset the interrupt flag status and start DMA again
 *
 * @return
 *
 * @note
 *
*******************************************************************************/
void AF_RestartDMAs(void)
{
	/* check if interrupt has been received and DMA stopped*/
	if (S2MMAFIntrReceived == 1U)
	{
		S2MMAFIntrReceived = 0U;
		AFInstancePtr->ChannelId = XAudioFormatter_S2MM;
		XAudioFormatterDMAStart(&AFInstance);
	}

	/* check if interrupt has been received and DMA stopped*/
	if (MM2SAFIntrReceived == 1U)
	{
		MM2SAFIntrReceived = 0U;
		AFInstancePtr->ChannelId = XAudioFormatter_MM2S;
		XAudioFormatterDMAStart(&AFInstance);
	}

}

/*****************************************************************************/
/**
 *
 * This function is called from the interrupt handler of audio formatter core.
 * After the first MM2S interrupt is received the interrupt_flag is set here.
 *
 * @return
 *
 * @note	This function assumes a Microblaze or ARM system and no
 *	operating system is used.
 *
*******************************************************************************/
void *XMM2SAFCallbackInterruptOnComplete(void *data)
{
	XAudioFormatter *AFInstancePtr = (XAudioFormatter *)data;
	/* clear interrupt flag */
	MM2SAFIntrReceived = 1;
	AF_MM2S_IOC_counter++;
	AllInterruptCounters.AF_MM2S_IOC_counter++;

	/* do not start automatically a next MM2S transfer */
	AFInstancePtr->ChannelId = XAudioFormatter_MM2S;
	AF_TxbufferPtr = (u32*)  (uintptr_t) (  (af_mm2s_hw_params.buf_addr )  );

	/* stop the S2MM transfer */
	//XAudioFormatterDMAStop(&AFInstance);
	mm2s_DMA_errors = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_ERRORS_MASK);
	mm2s_DMA_TimeOut_error = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_TIMEOUT_ERR_MASK);
	mm2s_DMA_Decode_error = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_DECODE_ERR_MASK);
	mm2s_DMA_Slave_error = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_SLAVE_ERR_MASK);

	mm2s_AF_errors.mm2s_DMA_Decode_error = mm2s_DMA_Decode_error;
	mm2s_AF_errors.mm2s_DMA_Slave_error = mm2s_DMA_Slave_error;
	mm2s_AF_errors.mm2s_DMA_TimeOut_error = mm2s_DMA_TimeOut_error;

	//AF_WriteAudioData();

//	if ( (AFInstancePtr->ChannelId) == XAudioFormatter_MM2S)
//	{
//		AF_bufferPtr = (u32*) (uintptr_t) (af_mm2s_hw_params.buf_addr )  ;
//	}
//	/* get the number of bytes transfered to memory */
//	mm2s_NumberOfBytestransfered = XAudioFormatterGetDMATransferCount(&AFInstance);
//
//	mm2s_DMA_errors = XAudioFormatter_GetStatusErrors(&AFInstance, XAUD_STS_ERRORS_MASK);
//
//	xil_printf("Audio Formatter current channel ID: %d\r\n",(XAudioFormatter_ChannelId) AFInstancePtr->ChannelId);
//
//		xil_printf(" Xilinx Audio Formatter DMA number of bytes transfered %s\r\n",
//				(int)mm2s_NumberOfBytestransfered);
//	/* reset if last period reached */
//	if (current_period_mm2s > AF_NUMBER_OF_PERIODS)
//	{
//		current_period_mm2s = 0;
//	}
//	/* enable the I2S Tx core*/
//	//XI2s_Tx_Enable(&I2sTxInstance, 0x1);
//
//	// get the pointer to the next sample
//	AF_bufferPtr += current_period_mm2s * AF_AUDIOSAMPLES_PER_PERIOD;
//	// Loop through all samples in the period
//	/* this pointer will be used inside one period */
//	AF_PeriodPtr_mm2s = AF_bufferPtr;
//    uint32_t sample;
//
//	for (sample = 0; sample < AF_AUDIOSAMPLES_PER_PERIOD; sample+=2)
//	{
//		// Read audio samples for left and right channels from the buffer
////	            uint32_t *audio_sample_ptr = (uint32_t*)(uint64_t)AF_bufferPtr + sample * AF_NUMBER_OF_CHANNELS;
//		*AF_PeriodPtr_mm2s = audio_sample_in_period_l[sample/2];
//		AF_PeriodPtr_mm2s++;
//		*AF_PeriodPtr_mm2s = audio_sample_in_period_r[sample/2];
//		AF_PeriodPtr_mm2s++;
//
//		xil_printf("DMA sent audio sample left: %d\r\n", (int)audio_sample_in_period_l[sample]);
//		xil_printf("DMA sent audio sample right: %d\r\n", (int)audio_sample_in_period_r[sample]);
//
//
//		// Process the audio samples or store them as needed
//		// ...
//	}
//	current_period_mm2s++;

	return(data);
}
/*****************************************************************************/
/**
 *
 * This function is called from the interrupt handler of audio formatter core.
 * If an error occurs the function is called
 *
 * @return
 *
 * @note	This function assumes a Microblaze or ARM system and no
 *	operating system is used.
 *
*******************************************************************************/
void *XMM2SAFCallbackError(void *data)
{
	XAudioFormatter *AFInstancePtr = (XAudioFormatter *)data;
	/* clear interrupt flag */
	MM2SAFIntrError = 1;
	AFInstancePtr->ChannelId = XAudioFormatter_MM2S;
	XAudioFormatterDMAStop(&AFInstance);
	return(data);
}
/*****************************************************************************/
/**
 *
 * This function is called from the interrupt handler of audio formatter core.
 * If an error occurs the function is called
 *
 * @return
 *
 * @note	This function assumes a Microblaze or ARM system and no
 *	operating system is used.
 *
*******************************************************************************/
void *XMM2SAFCallbackTimeOut(void *data)
{
	XAudioFormatter *AFInstancePtr = (XAudioFormatter *)data;
	if (AFInstancePtr != NULL)
	{
	/* clear interrupt flag */
	MM2SAFIntrTimeOut = 1;
	}
	//AFInstancePtr->ChannelId = XAudioFormatter_MM2S;
	//XAudioFormatterDMAStop(&AFInstance);
	return(data);
}



/*****************************************************************************/
/**
*
* This function reads out Audio Formatter status errors
*
* @param	InstancePtr is a pointer to the XAudioFormatter instance.
* @param	offset this is the offset to S2MM or MM2S.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
u32 XAudioFormatter_GetStatusErrors(XAudioFormatter *InstancePtr, u32 mask)
{
	u32 offset;
	u32 val;

	//Xil_AssertVoid(InstancePtr != NULL);
	//Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

	if (InstancePtr->ChannelId == XAudioFormatter_S2MM) {
		offset = XAUD_FORMATTER_S2MM_OFFSET;
	}
	if (InstancePtr->ChannelId == XAudioFormatter_MM2S) {
		offset = XAUD_FORMATTER_MM2S_OFFSET;
	}
	val = XAudioFormatter_ReadReg(InstancePtr->BaseAddress,
		XAUD_FORMATTER_STS + offset);
	val = val & mask;
	return(val);
}

/*****************************************************************************/
/**
*
* This function gets the DMA state, returns 1 if DMA is running and 0 if stopped
*
* @param	InstancePtr is a pointer to the XAudioFormatter instance.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
u32 XAudioFormatter_getDMAStatus(XAudioFormatter *InstancePtr)
{
	u32 val;
	u32 offset;


	if (InstancePtr->ChannelId == XAudioFormatter_S2MM) {
		offset = XAUD_FORMATTER_S2MM_OFFSET;
	}
	if (InstancePtr->ChannelId == XAudioFormatter_MM2S) {
		offset = XAUD_FORMATTER_MM2S_OFFSET;
	}
	val = XAudioFormatter_ReadReg(InstancePtr->BaseAddress,
	    XAUD_FORMATTER_CTRL + offset);
	u32 status = (val & XAUD_CTRL_DMA_EN_MASK) ? 1 : 0;
	return(status);
}
