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





/*
 * function prototypes
 */
extern void I2S_Init(void); // initialize the I2S IP core

#endif // I2S_H
