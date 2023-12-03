/*
 * header file to provide defines, typedefs and externs for operating the audio formatter
 */
#ifndef __AUDIOFORMATTER_H_
#define __AUDIOFORMATTER_H_

/*
 * Xilinx includes
 */
#include "xparameters.h"
#include "xil_io.h"
/*
 * Xilinx Platform Includes
 */
#include "xaudioformatter.h"

/*
 * own includes
 */
#include "verbose.h"

#include "ISR_Tasks.h"

/*
 * own defines
 */

#define XAUDIO_FORMATTER_SW_VER "v1.00"
#define AF_DEVICE_ID	XPAR_XAUDIOFORMATTER_0_DEVICE_ID
#define AF_S2MM_INTERRUPT_ID \
	XPAR_FABRIC_AUDIO_FORMATTER_0_IRQ_S2MM_VEC_ID
#define AF_MM2S_INTERRUPT_ID \
	XPAR_FABRIC_AUDIO_FORMATTER_0_IRQ_MM2S_VEC_ID
#define AF_FS		48 /* kHz */
#define AF_MCLK		(384 * AF_FS)
#define AF_S2MM_TIMEOUT 0x80000000

/*
 * own defines for register access
 */
#define XAUD_CTRL_ACVCHNL_2_MASK       	BIT(20)
#define XAUD_CTRL_ACVCHNL_4_MASK   		BIT(21)
#define XAUD_CTRL_ACVCHNL_6_MASK   		(BIT(20) || BIT(21))
#define XAUD_CTRL_ACVCHNL_8_MASK   		BIT(22)
#define XAUD_CTRL_ACVCHNL_S_MASK   		(0xF << XAUD_CTRL_ACTIVE_CH_SHIFT)

#define XAUD_CTRL_ERR_IRQ_MASK       	BIT(12)
#define XAUD_CTRL_DMA_EN_MASK        	BIT(0)

#define XAUD_PERIOD_CFG_NOMBEROFPERIODS_MASK    0x7F
#define XAUD_PERIOD_CFG_PERIODSIZE_MASK    0xFFFF
#define XAUD_PERIOD_CFG_PERIODSIZE_SHIFT    0


#define XAUD_STS_TIMEOUT_ERR_MASK        BIT(19)
#define XAUD_STS_DECODE_ERR_MASK    BIT(18)
#define XAUD_STS_SLAVE_ERR_MASK      BIT(17)

#define XAUD_STS_ERRORS_MASK        (BIT(19) || BIT(18) || BIT(17))


#define XAUD_STS_DMA_HALT_MASK      BIT(0)


/*
 * - No support for non-aligned Buffer address. The Buffer address must be aligned to Memory Map width.
*  - Period size must be integer multiples of (32 bytes * # of valid channels). For example:
*  - Number of valid channels = 4
*  - Period size must at least be 4*8*(32 bits) = 4*32 bytes
*  - Period size must integer multiples of 4*32 bytes = 128 bytes, 256bytes, 384 bytes, etc.
*  - When calculating, use 32 as the the period size for PCM data widths of 20, 24 and 32, because they occupy 32 bits space in memory.
*  - No support for PCM sample data width conversion
 */
#define AF_NUMBER_OF_CHANNELS 2
#define PERIOD_SIZE_PER_CHANNEL 32

#define AF_CONVERT_BYTES_TO_AUDIOSAMPLES 	4 // 4 bytes per audio sample (24bit occupies 32bits in memory)
#define AF_NUMBER_OF_PERIODS 	2

//#define AF_BYTES_PER_PERIOD 	(2*2*8*32*2)
/* use the define below to make one period equal to one AES3 audio block containing 192 frames (with 2 audio samples each - 32bits) */
/* with two dma periods there will be 2 AES3 blocks of audio data */

#define AF_BYTES_PER_PERIOD					(384*4) // one AES3 audio block
#define AF_AUDIOSAMPLES_PER_PERIOD 			(AF_BYTES_PER_PERIOD/AF_CONVERT_BYTES_TO_AUDIOSAMPLES)
#define AUDIO_BUFFER_BASE_ADDRESS 0x20000000ULL

/*
 * typedefs
 */

typedef struct
{
	/* ChannelId MM2S or S2MM */
	XAudioFormatter_ChannelId ChannelId;
	/* Audio Formatter Control Register */
	u32 AF_Ctrl;
	/* Audio Formatter Period Config Register */
	u32 AF_PrdCfg;
	/* Audio Formatter Number of Channels */
	u32 NumberOfChannels;
	/* Audio Data Bits Width */
	u32 AudioDataBitsWidth;
	/* Number of Periods */
	u32 NumberOfPeriods;
	/* Period Size */
	u32 PeriodSize;
	/* Buff Addr */
   u64 BufferAddr;
} AudioFormatter_HwConfig;

typedef struct
{
	u32 s2mm_DMA_errors;
	u32 s2mm_DMA_TimeOut_error;
	u32 s2mm_DMA_Decode_error;
	u32 s2mm_DMA_Slave_error;
	u32 s2mm_DMA_halt;
	u32 s2mm_DMA_ctrl_state;
} s2mm_DMA_errors_t;


typedef struct
{
	u32 mm2s_DMA_TimeOut_error;
	u32 mm2s_DMA_Decode_error;
	u32 mm2s_DMA_Slave_error;
	u32 mm2s_DMA_errors;
	u32 mm2s_DMA_halt;
	u32 mm2s_DMA_ctrl_state;
} mm2s_DMA_errors_t;




typedef struct
{
	u32 AF_MM2S_IOC_counter;
	u32 AF_S2MM_IOC_counter;
	u32 I2sTxIntrAesCntr;
	u32 I2sRxIntrAesCntr;
} InterruptCounters_t;



/*
 * function prototypes
 */
extern void AudioFormatter_Init(void); // initialize the audio formater
extern u32 InitializeAudioFormatter(XAudioFormatter *AFInstancePtr);
extern void *XMM2SAFCallback(void *data);
extern void *XS2MMAFCallback(void *data);
extern void AF_ReadAudioSamples(XAudioFormatter *AFInstancePtr);
extern void AF_GenerateSineWaveAndWriteToBuff(void);
extern void AF_GetHwConfig(XAudioFormatter *AFInstancePtr, AudioFormatter_HwConfig* AFHwConfigPtr);
extern void AF_RestartDMAs(void);
extern void AF_ProcessAudioData(void);
extern void AF_WriteAudioData(void);
extern void AF_ReadAudioData(void);

extern u32 XAudioFormatter_GetStatusErrors(XAudioFormatter *InstancePtr, u32 mask);
extern u32 XAudioFormatter_getDMAStatus(XAudioFormatter *InstancePtr);

extern void ProcessI2SInterruptsAndDMA(void);

/* MM2S Callbacks */
extern void *XMM2SAFCallbackInterruptOnComplete(void *data);
extern void *XMM2SAFCallbackError(void *data);

/* S2MM Callbacks */
extern void *XS2MMAFCallbackInterruptOnComplete(void *data);
extern void *XS2MMAFCallbackTimeOut(void *data);
extern void *XS2MMAFCallbackError(void *data);


/* AF Tasks */
extern void XMM2SAFCallbackInterruptOnComplete_InTask(void *data);
extern void ProcessAudioPeriod(AudioData_t *audioData);



/*
 * variables declarations
 */
extern XAudioFormatter AFInstance;
extern XAudioFormatter *AFInstancePtr;

extern u32 S2MMAFIntrReceived;
extern u32 MM2SAFIntrReceived;

extern u32 s2mm_DMA_halt;
extern u32 mm2s_DMA_halt;


extern u32 s2mm_DMA_ctrl_state;
extern u32 mm2s_DMA_ctrl_state;

extern mm2s_DMA_errors_t mm2s_AF_errors;
extern s2mm_DMA_errors_t s2mm_AF_errors;

extern InterruptCounters_t AllInterruptCounters;

extern XAudioFormatterHwParams af_mm2s_hw_params;
extern XAudioFormatterHwParams af_s2mm_hw_params;

extern u32* AF_PeriodPtr_s2mm;
extern u32* AF_PeriodPtr_mm2s;

extern u32 TxBufAdr;
extern u32 RxBufAdr;

extern u32* AF_bufferPtr;
extern u32* AF_RxbufferPtr;
extern u32* AF_TxbufferPtr;

#endif // __AUDIOFORMATTER_H_
