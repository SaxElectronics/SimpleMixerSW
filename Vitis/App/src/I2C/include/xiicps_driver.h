/******************************************************************************
* Copyright (C) 2011 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

#ifndef IICPS_INTR_MASTER_EXAMPLE_H		/* prevent circular inclusions */
#define IICPS_INTR_MASTER_EXAMPLE_H		/* by using protection macros */


/***************************** Include Files **********************************/
#include "xparameters.h"
#include "xiicps.h"
#include "xiicps_hw.h"

#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"


#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"


/*
 * typedefs
 */
typedef struct {
    u32 CompleteRecvCount;
    u32 CompleteSendCount;
    u32 TimeoutErrorCount;
    u32 ReceiveErrorCount;
    u32 ArbLostErrorCount;
    u32 NackReceivedErrorCount;
    u32 SlaveNotReadyErrorCount;
    u32 RxOverflowErrorCount;
    u32 TxOverflowErrorCount;
    u32 RxUnderflowErrorCount;
    u32 TotalErrorCount;
} I2C_InterruptStats;



typedef struct {
    int slave_address;
    int buffer_size;
    u8 *send_buffer;
    u8 *recv_buffer;
} I2C_Params;

int IicPsSelfTestExample(u16 DeviceId);


/************************** Function Prototypes *******************************/

int IicPsMasterIntrExample(u16 DeviceId);

void I2C_InterruptHandler(void *CallBackRef, u32 Event);
int I2C_Init(u16 DeviceId);

extern int I2C_main_init(void);
extern int I2C_CyclicFunction();
extern int I2C_SendTestMessage(void);


/************************** Constant Definitions ******************************/

/*
 * The following constants map to the XPAR parameters created in the
 * xparameters.h file. They are defined here such that a user can easily
 * change all the needed parameters in one place.
 */
#define IIC_DEVICE_ID		XPAR_PS7_I2C_0_DEVICE_ID
#define IIC_INT_VEC_ID		XPAR_XIICPS_0_INTR

/*
 * The slave address to send to and receive from.
 */
#define IIC_SLAVE_ADDR		0x29
#define IIC_SCLK_RATE		100000


/*
 * The following constant controls the length of the buffers to be sent
 * and received with the IIC.
 */
#define TEST_BUFFER_SIZE   	250
#define NUMBER_OF_SIZES		18

/**************************** Type Definitions ********************************/

extern XIicPs Iic;			/* Instance of the IIC Device */

/*
 * The following counters are used to determine when the entire buffer has
 * been sent and received.
 */
extern volatile u32 SendComplete;
extern volatile u32 RecvComplete;
extern volatile u32 SendCompleteCntr;
extern volatile u32 RecvCompleteCntr;
extern volatile u32 TotalErrorCount;

extern u8 SendBuffer[TEST_BUFFER_SIZE];    /* Buffer for Transmitting Data */
extern u8 RecvBuffer[TEST_BUFFER_SIZE];    /* Buffer for Receiving Data */
extern I2C_Params i2c_params;


extern void I2C_ClearHoldBit(u32 BaseAddr);


#endif
