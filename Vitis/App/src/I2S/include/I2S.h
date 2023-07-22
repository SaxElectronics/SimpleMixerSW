/*
 * header file to provide defines, typedefs and externs for operating the audio formatter
 */
#ifndef I2S_H
#define I2S_H
/*
 * includes
 */
#include "xparameters.h"
#include "xil_io.h"

/*
 * Xilinx IP Core Includes
 */
#include "xi2srx.h"
#include "xi2srx_hw.h"
#include "xi2stx.h"
#include "xi2stx_hw.h"

/*
 *  I2S user defines
 */

#define I2S_RX_DEVICE_ID	XPAR_XI2SRX_0_DEVICE_ID
#define I2S_RX_INTERRUPT_ID	XPAR_FABRIC_I2SRX_0_VEC_ID
#define I2S_RX_FS		48 //kHz
#define I2S_RX_MCLK		(384 * I2S_RX_FS)
#define I2S_RX_TIME_OUT 500000

#define I2S_TX_DEVICE_ID	XPAR_XI2STX_0_DEVICE_ID
#define I2S_TX_INTERRUPT_ID	XPAR_FABRIC_I2STX_0_VEC_ID
#define I2S_TX_FS		48 /* kHz */
#define I2S_TX_MCLK		(384 * I2S_TX_FS)
#define I2S_TX_TIME_OUT 500000

#define XI2S_RX_IRQSTS_SET_BIT0 0x00000001 // Bit 0 set to 1

#define XI2S_RX_VALIDITY_BIT_OFFSET    0x0C //!< Validity Bit Register


/*
 *	register defines
 */

//#define XPAR_I2S_RECEIVER_0_BASEADDR
// returns core configuration details
#define XPAR_I2S_RECEIVER_0_CORE_CONFIG 		0x04
// register to enable or disable the core
#define XPAR_I2S_RECEIVER_0_CORE_CONTROL		0x08
// Sets validity bit on output stream data
#define XPAR_I2S_RECEIVER_0_VALIDITY_REG		0x0C
// interrupts the enable/disable register
#define XPAR_I2S_RECEIVER_0_INTERRUPT_CONTROL	0x10
// interrupt status register
#define XPAR_I2S_RECEIVER_0_INTERRUPT_STATUS 	0x14
// Register to program the SCK divider value
#define XPAR_I2S_RECEIVER_0_TIMING_CONTROL 		0x20
// Channel 0/1 Control: Channel 0/1 control register
#define XPAR_I2S_RECEIVER_0_CHANNEL01_CONTROL		0x30
// Channel 2/3 Control: Channel 2/3 control register
#define XPAR_I2S_RECEIVER_0_CHANNEL23_CONTROL		0x34
// Channel 4/5 Control: Channel 4/5 control register
#define XPAR_I2S_RECEIVER_0_CHANNEL45_CONTROL		0x38
// Channel 6/7 Control: Channel 6/7 control register
#define XPAR_I2S_RECEIVER_0_CHANNEL67_CONTROL		0x3C
// AES Channel Status 0: Register to specify the LSB 32-bit of the AES Channel Status
#define XPAR_I2S_RECEIVER_0_AESCHANNEL_STATUS0		0x50
// AES Channel Status 1: Register to specify the next LSB 32-bit of the AES Channel Status
#define XPAR_I2S_RECEIVER_0_AESCHANNEL_STATUS1		0x54
// AES Channel Status 2: Register to specify the 32-bit of the AES Channel Status
#define XPAR_I2S_RECEIVER_0_AESCHANNEL_STATUS2		0x58
// AES Channel Status 3: Register to specify the 32-bit of the AES Channel Status
#define XPAR_I2S_RECEIVER_0_AESCHANNEL_STATUS3		0x5C
// AES Channel Status 4: Register to specify the 32-bit of the AES Channel Status
#define XPAR_I2S_RECEIVER_0_AESCHANNEL_STATUS4		0x60
// AES Channel Status 5: Register to specify the 32-bit of the AES Channel Status
#define XPAR_I2S_RECEIVER_0_AESCHANNEL_STATUS5		0x64


/* I2s Rx declarations */
extern XI2s_Rx I2sRxInstance;		/* Instance of the I2S receiver device */
extern u32 I2sRxIntrAesComplete;
extern u32 I2sRxIntrOvfDetected;
extern u32 I2sRxIntrCount;
extern u32 I2sRxIntrAesCntr;

/* I2s Tx declarations */
extern XI2s_Tx I2sTxInstance;		/* Instance of the I2s Transmitter device */
extern u32 I2sTxIntrAesComplete;
extern u32 I2sTxIntrUvfDetected;
extern u32 I2sTxIntrSyncErr;
extern u32 I2sTxIntrAesChStsUpd;
extern u32 I2sTxIntrCount;
extern u32 I2sTxIntrAesCntr;

/* typedefs */
typedef struct I2S_HwConfig
{
	/* I2S core configuration register */
	u32 ConfigReg;
	/* Audio Data Width 16 or 24 bit */
	u32 DataWidth;
	/* Number of Channels supported */
	u32 NumberOfChannels;
	/* Master or Slave Operating Mode */
	u32 IsMaster;
	/* I2S control register */
	u32 ControlReg;
	/* core is enabled */
	u32 IsEnabled;
	/* Left-Right Justification enabled */
	u32 RightJustification;
	/* LRClock32bit */
	u32 LRClock32bit;

}I2S_HwConfig;

/*
 * function prototypes
 */
extern int I2S_Init(void); // initialize the I2S IP core
extern void I2sTxAesBlockCmplIntrHandler(void *CallBackRef);
extern void I2sRxAesBlockCmplIntrHandler(void *CallBackRef);
extern void I2STx_GetHwConfig(XI2s_Tx *I2SInstancePtr, I2S_HwConfig* I2SHwConfigPtr );
extern void I2SRx_GetHwConfig(XI2s_Rx *I2SInstancePtr, I2S_HwConfig* I2SHwConfigPtr );


#endif // I2S_H
