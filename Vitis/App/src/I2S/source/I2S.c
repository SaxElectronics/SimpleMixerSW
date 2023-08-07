
/*
 * I2S.c: Provide functions to initialize and operate the I2S interface
 *
 * This file contains functions to initialize the audio formatter, to configure/reconfigure
 * and operate it properly.
 *
 */

/*
 * standrad includes
 */
#include "stdbool.h"

/*
 * Xilinx Platform Includes
 */
#include "xparameters.h"
#include "xstatus.h"
#include "xil_io.h"


/* include own header */
#include "I2S.h"
#include "verbose.h"
#include "AudioFormatter.h"

/*
 * global variables
 */
/* Rx */
XI2s_Rx I2sRxInstance;		/* Instance of the I2S receiver device */
XI2s_Rx *I2sRxInstancePtr = &I2sRxInstance;
XI2srx_Config * pI2S_Rx_Config;
u32 I2sRxIntrAesComplete; /* AES Block Complete Interrupt Received*/
u32 I2sRxIntrOvfDetected; /* Overflow Rx Interrupt Received*/
u32 I2sRxIntrCount =0;
u32 I2sRxIntrAesCntr = 0;

I2S_HwConfig I2sRx_HwConfig;

/* Tx */
XI2s_Tx I2sTxInstance;		/* Instance of the I2s Transmitter device */
XI2s_Tx *I2sTxInstancePtr = &I2sTxInstance;
u32 I2sTxIntrAesComplete;
u32 I2sTxIntrAesCntr = 0;

u32 I2sTxIntrUvfDetected;
u32 I2sTxIntrSyncErr;
u32 I2sTxIntrAesChStsUpd;
u32 I2sTxIntrCount =0;

I2S_HwConfig I2sTx_HwConfig;


/*
 * Global Variables
 */
u32 Master_Clk;
u32 SamplingFreq;

/************************** Function Prototypes *******************************/
/* I2S Rx */
void I2sRxAesBlockCmplIntrHandler(void *CallBackRef);
void I2sRxOvrflwIntrHandler(void *CallBackRef);
u32 InitializeI2sRx(XI2s_Rx *I2sRxInstancePtr);

/* I2S Tx */
void I2sTxUnderflowIntrHandler(void *CallBackRef);
void I2sTxAesGetChStsHandler(void *CallBackRef);
void I2sTxAesBlockErrIntrHandler(void *CallBackRef);
void I2sTxAesBlockCmplIntrHandler(void *CallBackRef);
u32 InitializeI2sTx(XI2s_Tx *I2sTxInstancePtr);
extern u32 XI2s_Rx_GetChMux(XI2s_Rx *InstancePtr, XI2s_Rx_ChannelId ChID);
extern u32 XI2s_Tx_GetChMux(XI2s_Tx *InstancePtr, XI2s_Tx_ChannelId ChID);
void XI2s_Rx_SetValidity(XI2s_Rx *InstancePtr, u8 Enable);

/*****************************************************************************/
/**
 * This function initializes the I2S receiver and then
 * sets it up such that a periodic interrupt is generated.
 *
 * This function uses interrupt driven mode of the I2S receiver.
 *
 * @param	I2sRxInstancePtr is a pointer to the XI2s_Rx driver Instance
 * @param	DeviceId is the XPAR_<i2s_rx_instance>_DEVICE_ID value from
 *		xparameters.h
 * @param	IntrId is XPAR_<INTC_instance>_<i2s_rx_instance>_INTERRUPT_INTR
 *		value from xparameters.h
 *
 * @return	XST_SUCCESS if the Test is successful, otherwise XST_FAILURE
 *
 *****************************************************************************/
int I2S_Init(void)
{
	u32 Status;

	Master_Clk = I2S_RX_MCLK;
	SamplingFreq = I2S_RX_FS;
	xil_printf("I2s Receiver Initialization \r\n");
	/*
	 * Initialize I2s Receiver.
	 */
	Status = InitializeI2sRx(&I2sRxInstance);
	if (Status != XST_SUCCESS)
	{
		xil_printf("I2s Receiver Initialization FAILED. \r\n");
		return(XST_FAILURE);
	}
	xil_printf("I2s Transmitter Initialization \r\n");
	/*
	 * Initialize I2s Transmitter.
	 */
	InitializeI2sTx(&I2sTxInstance);
	if (Status != XST_SUCCESS)
	{
		xil_printf("I2s Transmitter Initialization FAILED. \r\n");
		return(XST_FAILURE);
	}
	return Status;
}
/*****************************************************************************/
/**
 * This function does the lookup and intialization of the I2S receiver.
 *
 * @param	I2sRxInstancePtr is a pointer to the I2sRx driver instance
 *
 * @return	XST_SUCCESS if the call is successful, otherwise XST_FAILURE.
 *
 * @note	None.
 *
******************************************************************************/
u32 InitializeI2sRx(XI2s_Rx *I2sRxInstancePtr)
{
	/*
	 * Lookup and Initialize the I2S receiver so that it's ready to use.
	 */
	u32 Status;
	XI2srx_Config *I2SRxConfig;
	I2SRxConfig = XI2s_Rx_LookupConfig(I2S_RX_DEVICE_ID);
	if (I2SRxConfig == NULL)
		return XST_FAILURE;

	Status = XI2s_Rx_CfgInitialize(&I2sRxInstance, I2SRxConfig,
			I2SRxConfig->BaseAddress);
	if (Status != XST_SUCCESS)
		return XST_FAILURE;

//	Status = XScuGic_Connect(&Intc,	I2S_RX_INTERRUPT_ID,
//		(XInterruptHandler)XI2s_Rx_IntrHandler,
//		(void *)I2sRxInstancePtr);
//	if (Status == XST_SUCCESS) {
//		XScuGic_Enable(&Intc, I2S_RX_INTERRUPT_ID);
//	} else {
//		xil_printf("ERR:: Unable to register i2s rx interrupt handler");
//		return XST_FAILURE;
//	}

//	Xil_ExceptionEnable();
	/* set the Rx handlers */
	XI2s_Rx_SetHandler(I2sRxInstancePtr, XI2S_RX_HANDLER_AES_BLKCMPLT,
			&I2sRxAesBlockCmplIntrHandler,
			(void *)I2sRxInstancePtr);
	XI2s_Rx_SetHandler(I2sRxInstancePtr, XI2S_RX_HANDLER_AUD_OVRFLW,
			&I2sRxOvrflwIntrHandler, (void *)I2sRxInstancePtr);
	XI2s_Rx_SetSclkOutDiv(I2sRxInstancePtr, I2S_RX_MCLK, I2S_RX_FS);
	/* mux channel 0 to reiceive audio from I2S channels 0 and 1 */
	XI2s_Rx_SetChMux(I2sRxInstancePtr, 0x0, XI2S_RX_CHMUX_XI2S_01);
	/* enable interrupts */
	XI2s_Rx_IntrEnable(I2sRxInstancePtr, XI2S_RX_GINTR_EN_MASK);
	XI2s_Rx_IntrEnable(I2sRxInstancePtr, XI2S_RX_INTR_AES_BLKCMPLT_MASK);
	XI2s_Rx_IntrEnable(I2sRxInstancePtr, XI2S_RX_INTR_AUDOVRFLW_MASK);
	/* enable left, right justification */
	XI2s_Rx_JustifyEnable(I2sRxInstancePtr, false);
	/* set left justification */
	XI2s_Rx_Justify(I2sRxInstancePtr, (XI2s_Rx_Justification) 0U);
	/* enable logging for Rx */
	XI2s_Rx_LogEnable(I2sRxInstancePtr);
	/* enable core operations */
	XI2s_Rx_Enable(I2sRxInstancePtr, TRUE);

	/* Read the set up of the Rx core */
	I2SRx_GetHwConfig(I2sRxInstancePtr, &I2sRx_HwConfig);
	return Status;
}
/*****************************************************************************/
/**
 * This function does the lookup and intialization of the I2S transmitter.
 *
 * @param	I2sTxInstancePtr is a pointer to the I2sTx driver instance
 *
 * @return	XST_SUCCESS if the call is successful, otherwise XST_FAILURE.
 *
 * @note	None.
 *
******************************************************************************/
u32 InitializeI2sTx(XI2s_Tx *I2sTxInstancePtr)
{
	/*
	 * Lookup and Initialize the I2S transmitter so that it's ready to use.
	 */
	u32 Status;
	XI2stx_Config *I2STxConfig;
	I2STxConfig = XI2s_Tx_LookupConfig(I2S_TX_DEVICE_ID);
	if (I2STxConfig == NULL) {
		return XST_FAILURE;
	}

	Status = XI2s_Tx_CfgInitialize(I2sTxInstancePtr, I2STxConfig,
		I2STxConfig->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
//	Status = XScuGic_Connect(&Intc,	I2S_TX_INTERRUPT_ID,
//		(XInterruptHandler)XI2s_Tx_IntrHandler,
//		(void *)I2sTxInstancePtr);
//	if (Status == XST_SUCCESS) {
//		XScuGic_Enable(&Intc, I2S_TX_INTERRUPT_ID);
//	} else {
//		xil_printf("ERR:: Unable to register i2s tx interrupt handler");
//		return XST_FAILURE;
//	}
	/* set AES Block complete interrupt handler */
	XI2s_Tx_SetHandler(I2sTxInstancePtr, XI2S_TX_HANDLER_AES_BLKCMPLT,
			&I2sTxAesBlockCmplIntrHandler,
			(void *)I2sTxInstancePtr);
	/* set AES Block Error interrupt handler */
	XI2s_Tx_SetHandler(I2sTxInstancePtr, XI2S_TX_HANDLER_AES_BLKSYNCERR,
			&I2sTxAesBlockErrIntrHandler,
			(void *)I2sTxInstancePtr);
	/* set AES get channel status interrupt handler */
	XI2s_Tx_SetHandler(I2sTxInstancePtr, XI2S_TX_HANDLER_AES_CHSTSUPD,
			&I2sTxAesGetChStsHandler,
			(void *)I2sTxInstancePtr);
	/* set underflow interrupt handler */
	XI2s_Tx_SetHandler(I2sTxInstancePtr, XI2S_TX_HANDLER_AUD_UNDRFLW,
			&I2sTxUnderflowIntrHandler,
			(void *)I2sTxInstancePtr);
	/* set sampling frequency and master clock*/
	XI2s_Tx_SetSclkOutDiv(I2sTxInstancePtr, I2S_TX_MCLK, I2S_TX_FS);
	/* mux channel 0 to axi stream audio channel 0,1*/
	XI2s_Tx_SetChMux(I2sTxInstancePtr, 0, XI2S_TX_CHMUX_AXIS_01);
	/* enable global interrupt */
	XI2s_Tx_IntrEnable(I2sTxInstancePtr, XI2S_TX_GINTR_EN_MASK);
	/* enable AES block complete interrupt */
	XI2s_Tx_IntrEnable(I2sTxInstancePtr, XI2S_TX_INTR_AES_BLKCMPLT_MASK);
	/* enable underflow error interrupt */
	XI2s_Tx_IntrEnable(I2sTxInstancePtr, XI2S_TX_INTR_AUDUNDRFLW_MASK);
	/* enable underflow error interrupt */
	XI2s_Tx_IntrEnable(I2sTxInstancePtr, XI2S_TX_INTR_AES_BLKSYNCERR_MASK);

	/* enable left, right justification */
	XI2s_Tx_JustifyEnable(I2sTxInstancePtr, false);
	/* set left justification */
	XI2s_Tx_Justify(I2sTxInstancePtr, (XI2s_Rx_Justification) 0U);
	/* enable logging for Tx */
	XI2s_Tx_LogEnable(I2sTxInstancePtr);
	/* enable the core*/
	XI2s_Tx_Enable(I2sTxInstancePtr, TRUE);
	/* Read the set up of the Rx core */
	I2STx_GetHwConfig(I2sTxInstancePtr, &I2sTx_HwConfig);
	return(XST_SUCCESS);
}
/*****************************************************************************/
/**
 * This function is the handler which performs processing for the I2s
 * Transmitter.
 * It is called from an interrupt context when the I2s Transmitter receives a
 * AES Block Error Interrupt.
 *
 * This handler provides an example of how to handle I2s Transmitter interrupts
 * but is application specific.
 *
 * @param	CallBackRef is a pointer to the callback function
 *
 * @return	None.
 *
 * @note	None.
 *
******************************************************************************/
void I2sTxAesBlockErrIntrHandler(void *CallBackRef)
{
	XI2s_Tx *InstancePtr = (XI2s_Tx *)CallBackRef;
	if (InstancePtr!=NULL)
	{
	/* Set the interrupt received flag. */
	I2sTxIntrSyncErr = 1;
	}
}
/*****************************************************************************/
/**
 * This function is the handler which performs processing for the I2s
 * Transmitter.
 * It is called from an interrupt context when the I2s Transmitter receives a
 * AES Block Complete Interrupt.
 *
 * This handler provides an example of how to handle I2s Transmitter interrupts
 * but is application specific.
 *
 * @param	CallBackRef is a pointer to the callback function
 *
 * @return	None.
 *
 * @note	None.
 *
******************************************************************************/
void I2sTxAesBlockCmplIntrHandler(void *CallBackRef)
{
	XI2s_Tx *InstancePtr = (XI2s_Tx *)CallBackRef;
	if (InstancePtr!=NULL)
	{
	/* Set the interrupt received flag. */
	I2sTxIntrAesComplete = 1;
	I2sTxIntrAesCntr++;
	/* display log buffer */
	//XI2s_Tx_LogDisplay(InstancePtr);
	/* stop the transfer of data from MM2S */
	//AFInstancePtr->ChannelId = XAudioFormatter_S2MM;
	//XAudioFormatterDMAStart(&AFInstance);
	/* enable the I2S Tx core*/
	//XI2s_Tx_Enable(&I2sTxInstance, 0x1);
	}
}
/*****************************************************************************/
/**
* This function is the handler which performs processing for the I2S
* receiver.
* It is called from an interrupt context when the I2S receiver receives a
* AES Block Complete Interrupt.
*
* This handler provides an example of how to handle I2S receiver interrupts
* but is application specific.
*
* @param	CallBackRef is a pointer to the callback function
*
* @return	None.
*
* @note	None.
*
******************************************************************************/
void I2sRxAesBlockCmplIntrHandler(void *CallBackRef)
{
		XI2s_Rx *I2sRxInstancePtr = (XI2s_Rx *)CallBackRef;
		/* Set the interrupt received flag. */
		if (I2sRxInstancePtr != NULL)
		{
			I2sRxIntrAesComplete = 1;
			I2sRxIntrAesCntr++;
			//XI2s_Rx_SetValidity(I2sRxInstancePtr, 1U);

			/* display log buffer */
			//XI2s_Rx_LogDisplay(I2sRxInstancePtr);
			/* read the interrupt status */
			u32 intrsts_regval = XI2s_Rx_ReadReg(I2sRxInstancePtr->Config.BaseAddress, XI2S_RX_IRQSTS_OFFSET);
			/* Clear AES block received interrupt status register */
			XI2s_Rx_WriteReg(I2sRxInstancePtr->Config.BaseAddress, XI2S_RX_IRQSTS_OFFSET, intrsts_regval | XI2S_RX_IRQSTS_SET_BIT0);
			//u32 validitybit_regval = XI2s_Rx_ReadReg(I2sRxInstancePtr->Config.BaseAddress, XI2S_RX_VALIDITY_BIT_OFFSET);

			/* start the S2MM DMA transfer */
			//AFInstance.ChannelId = XAudioFormatter_S2MM;
			//XAudioFormatterDMAStart(&AFInstance);
		}
}
/*****************************************************************************/
/**
* This function is the handler which performs processing for the I2S
* receiver.
* It is called from an interrupt context when the I2S receiver receives a
* Underflow Interrupt.
*
* This handler provides an example of how to handle I2S receiver interrupts
* but is application specific.
*
* @param	CallBackRef is a pointer to the callback function
*
* @return	None.
*
* @note	None.
*
******************************************************************************/
void I2sRxOvrflwIntrHandler(void *CallBackRef)
{
		XI2s_Rx *I2sRxInstancePtr = (XI2s_Rx *)CallBackRef;
		/* Set the interrupt received flag. */
		if (I2sRxInstancePtr!= NULL)
		{
			I2sRxIntrOvfDetected = 1;
		}
}
/*****************************************************************************/
/**
 * This function is the handler which performs processing for the I2s
 * Transmitter.
 * It is called from an interrupt context when the I2s Transmitter receives a
 * AES Channel Status Updated Interrupt.
 *
 * This handler provides an example of how to handle I2s Transmitter interrupts
 * but is application specific.
 *
 * @param	CallBackRef is a pointer to the callback function
 *
 * @return	None.
 *
 * @note	None.
 *
******************************************************************************/
void I2sTxAesGetChStsHandler(void *CallBackRef)
{
	XI2s_Tx *InstancePtr = (XI2s_Tx *)CallBackRef;
	if (InstancePtr != NULL)
	{
	/* Set the interrupt received flag. */
	I2sTxIntrAesChStsUpd = 1;
	}
}

/*****************************************************************************/
/**
 * This function is the handler which performs processing for the I2s
 * Transmitter.
 * It is called from an interrupt context when the I2s Transmitter receives a
 * Underflow Interrupt.
 *
 * This handler provides an example of how to handle I2s Transmitter interrupts
 * but is application specific.
 *
 * @param	CallBackRef is a pointer to the callback function
 *
 * @return	None.
 *
 * @note	None.
 *
******************************************************************************/
void I2sTxUnderflowIntrHandler(void *CallBackRef)
{
	XI2s_Tx *InstancePtr = (XI2s_Tx *)CallBackRef;
	if (InstancePtr!=NULL)
	{
	/* Set the interrupt received flag. */
	I2sTxIntrUvfDetected = 1;
	}
}

/*****************************************************************************/
/**
 *
 * This function gets the current config of the I2S receiver module. It reads the
 * control and the config registers and stores important settings into separate variables
 *
 * @param	I2SInstancePtr is a pointer to I2S Rx driver instance
 *
 * @param	I2S_HwConfig is a pointer to the hardware config structure
 *
 * @return
 *
 * @note
 *
*******************************************************************************/

void I2SRx_GetHwConfig(XI2s_Rx *I2SInstancePtr, I2S_HwConfig* I2SHwConfigPtr )
{
	/* read out Control Register */
	I2SHwConfigPtr->ControlReg = XI2s_Rx_ReadReg(I2SInstancePtr->Config.BaseAddress,
				XI2S_RX_CORE_CTRL_OFFSET);
	/* read out Config Register */
	I2SHwConfigPtr->ConfigReg = XI2s_Rx_ReadReg(I2SInstancePtr->Config.BaseAddress,
					XI2S_RX_CORE_CFG_OFFSET);
	/* Audio Data Width */
	I2SHwConfigPtr->DataWidth = (I2SHwConfigPtr->ConfigReg & XI2S_RX_REG_CFG_DWDTH_MASK);
	I2SHwConfigPtr->DataWidth >>= XI2S_RX_REG_CFG_DWDTH_SHIFT;
	VERBOSE("I2S Rx DataWidth is: ");
	VERBOSE("%d",(I2SHwConfigPtr->DataWidth));
	/* Number of Channels */
	I2SHwConfigPtr->NumberOfChannels = (I2SHwConfigPtr->ConfigReg & XI2S_RX_REG_CFG_NUM_CH_MASK);
	I2SHwConfigPtr->NumberOfChannels >>= XI2S_RX_REG_CFG_NUM_CH_SHIFT;
	VERBOSE("I2S Rx Number of Channels are: ");
	VERBOSE("%d",(I2SHwConfigPtr->NumberOfChannels));
	/* Is Master */
	I2SHwConfigPtr->IsMaster = (I2SHwConfigPtr->ConfigReg & XI2S_RX_REG_CFG_MSTR_MASK);
	I2SHwConfigPtr->IsMaster >>= XI2S_RX_REG_CFG_MSTR_SHIFT;
	VERBOSE("I2S Rx operating mode is master: ");
	VERBOSE("%d",(I2SHwConfigPtr->IsMaster));
	/* Is Core enabled? */
	I2SHwConfigPtr->IsEnabled = (I2SHwConfigPtr->ControlReg & XI2S_RX_REG_CTRL_EN_MASK);
	I2SHwConfigPtr->IsEnabled >>= XI2S_RX_REG_CTRL_EN_SHIFT;
	VERBOSE("I2S Rx core is enabled: ");
	VERBOSE("%d",(I2SHwConfigPtr->IsEnabled));
	/* Left Right Justification */
	I2SHwConfigPtr->RightJustification = (I2SHwConfigPtr->ControlReg & XI2S_RX_REG_CTRL_JFE_MASK);
	I2SHwConfigPtr->RightJustification >>= XI2S_RX_REG_CTRL_JFE_SHIFT;
	VERBOSE("I2S Rx core justification is left-right: ");
	VERBOSE("%d",(I2SHwConfigPtr->RightJustification));

	/* Left Right 32bit Clock */
	I2SHwConfigPtr->LRClock32bit = (I2SHwConfigPtr->ControlReg & XI2S_RX_REG_CTRL_LORJF_MASK);
	I2SHwConfigPtr->LRClock32bit>>= XI2S_RX_REG_CTRL_LORJF_SHIFT;
	VERBOSE("I2S Rx LR clock is 32bit: ");
	VERBOSE("%d",(I2SHwConfigPtr->LRClock32bit));

	/* get Channel Mux status */
	I2SHwConfigPtr->ChannelMux = XI2s_Rx_GetChMux(I2SInstancePtr, 0x0);
	VERBOSE("I2S Rx Channel Mux is: ");
	VERBOSE("%d",(I2SHwConfigPtr->ChannelMux ));

}

/*****************************************************************************/
/**
 *
 * This function gets the current config of the I2S receiver module. It reads the
 * control and the config registers and stores important settings into separate variables
 *
 * @param	I2SInstancePtr is a pointer to I2S Rx driver instance
 *
 * @param	I2S_HwConfig is a pointer to the hardware config structure
 *
 * @return
 *
 * @note
 *
*******************************************************************************/

void I2STx_GetHwConfig(XI2s_Tx *I2SInstancePtr, I2S_HwConfig* I2SHwConfigPtr )
{
	/* read out Control Register */
	I2SHwConfigPtr->ControlReg = XI2s_Tx_ReadReg(I2SInstancePtr->Config.BaseAddress,
				XI2S_TX_CORE_CTRL_OFFSET);
	/* read out Config Register */
	I2SHwConfigPtr->ConfigReg = XI2s_Tx_ReadReg(I2SInstancePtr->Config.BaseAddress,
					XI2S_TX_CORE_CFG_OFFSET);
	/* Audio Data Width */
	I2SHwConfigPtr->DataWidth = (I2SHwConfigPtr->ConfigReg & XI2S_TX_REG_CFG_DWDTH_MASK);
	I2SHwConfigPtr->DataWidth >>= XI2S_TX_REG_CFG_DWDTH_SHIFT;
	VERBOSE("I2S Tx DataWidth is: ");
	VERBOSE("%d",(I2SHwConfigPtr->DataWidth));
	/* Number of Channels */
	I2SHwConfigPtr->NumberOfChannels = (I2SHwConfigPtr->ConfigReg & XI2S_TX_REG_CFG_NUM_CH_MASK);
	I2SHwConfigPtr->NumberOfChannels >>= XI2S_TX_REG_CFG_NUM_CH_SHIFT;
	VERBOSE("I2S Tx Number of Channels are: ");
	VERBOSE("%d",(I2SHwConfigPtr->NumberOfChannels));
	/* Is Master */
	I2SHwConfigPtr->IsMaster = (I2SHwConfigPtr->ConfigReg & XI2S_TX_REG_CFG_MSTR_MASK);
	I2SHwConfigPtr->IsMaster >>= XI2S_TX_REG_CFG_MSTR_SHIFT;
	VERBOSE("I2S Tx operating mode is master: ");
	VERBOSE("%d",(I2SHwConfigPtr->IsMaster));
	/* Is Core enabled? */
	I2SHwConfigPtr->IsEnabled = (I2SHwConfigPtr->ControlReg & XI2S_TX_REG_CTRL_EN_MASK);
	I2SHwConfigPtr->IsEnabled >>= XI2S_TX_REG_CTRL_EN_SHIFT;
	VERBOSE("I2S Tx core is enabled: ");
	VERBOSE("%d",(I2SHwConfigPtr->IsEnabled));
	/* Left Right Justification */
	I2SHwConfigPtr->RightJustification = (I2SHwConfigPtr->ControlReg & XI2S_TX_REG_CTRL_JFE_MASK);
	I2SHwConfigPtr->RightJustification >>= XI2S_TX_REG_CTRL_JFE_SHIFT;
	VERBOSE("I2S Tx core justification is left-right: ");
	VERBOSE("%d",(I2SHwConfigPtr->RightJustification));

	/* Left Right 32bit Clock */
	I2SHwConfigPtr->LRClock32bit = (I2SHwConfigPtr->ControlReg & XI2S_TX_REG_CTRL_LORJF_MASK);
	I2SHwConfigPtr->LRClock32bit>>= XI2S_TX_REG_CTRL_LORJF_SHIFT;
	VERBOSE("I2S Tx LR clock is 32bit: ");
	VERBOSE("%d",(I2SHwConfigPtr->LRClock32bit));

	/* get Channel Mux status */
	I2SHwConfigPtr->ChannelMux = XI2s_Tx_GetChMux(I2SInstancePtr, 0x0);
	VERBOSE("I2S Tx Channel Mux is enabled: ");
	VERBOSE("%d",(I2SHwConfigPtr->ChannelMux ));
	VERBOSE("with MuxID: ");
	VERBOSE("%d",(0x0));
}


/****************************************************************************/
/**
 * This function sets the input source for the specified AXI-Stream channel pair
 *
 * @param  InstancePtr is a pointer to the XI2s Receiver instance.
 * @param  ChID specifies the AXI-Stream channel pair
 *   - 0 : AXI-Stream channel 0 and 1
 *   - 1 : AXI-Stream channel 2 and 3
 *   - 2 : AXI-Stream channel 4 and 5
 *   - 3 : AXI-Stream channel 6 and 7
 * @param  InputSource specifies the input source
 *
 * @return
 *   - XST_SUCCESS : if successful.
 *   - XST_FAILURE : if the AXI-Stream channel pair is invalid.
 *
 *****************************************************************************/
u32 XI2s_Rx_GetChMux(XI2s_Rx *InstancePtr, XI2s_Rx_ChannelId ChID)
{
	Xil_AssertNonvoid(InstancePtr != NULL);

	if (ChID > XI2S_RX_NUM_CHANNELS)
		return XST_FAILURE;

	int RegOffset = XI2S_RX_CH01_OFFSET + (ChID * 4);

	u32 data = XI2s_Rx_ReadReg(InstancePtr->Config.BaseAddress,
			RegOffset);
	return data;
}


/****************************************************************************/
/**
 * This function gets the input source for the specified AXI-Stream channel pair
 *
 * @param  InstancePtr is a pointer to the XI2s Receiver instance.
 * @param  ChID specifies the AXI-Stream channel pair
 *   - 0 : AXI-Stream channel 0 and 1
 *   - 1 : AXI-Stream channel 2 and 3
 *   - 2 : AXI-Stream channel 4 and 5
 *   - 3 : AXI-Stream channel 6 and 7
 * @param  InputSource specifies the input source
 *
 * @return
 *   - XST_SUCCESS : if successful.
 *   - XST_FAILURE : if the AXI-Stream channel pair is invalid.
 *
 *****************************************************************************/
u32 XI2s_Tx_GetChMux(XI2s_Tx *InstancePtr, XI2s_Tx_ChannelId ChID)
{
	Xil_AssertNonvoid(InstancePtr != NULL);

	if (ChID > XI2S_TX_NUM_CHANNELS)
		return XST_FAILURE;

	int RegOffset = XI2S_TX_CH01_OFFSET + (ChID * 4);

	u32 data = XI2s_Tx_ReadReg(InstancePtr->Config.BaseAddress,
			RegOffset);
	return data;
}


/*****************************************************************************/
/**
 * This function sets the validity of the audio stream.
 *
 * @param  InstancePtr is a pointer to the XI2s Receiver instance.
 * @param  Enable specifies TRUE/FALSE value to either set or unset validity reg.
 *
 * @return None.
 *
 *****************************************************************************/
void XI2s_Rx_SetValidity(XI2s_Rx *InstancePtr, u8 Enable)
{
	Xil_AssertVoid(InstancePtr != NULL);


	if (Enable) {
		XI2s_Rx_WriteReg(InstancePtr->Config.BaseAddress,
					XPAR_I2S_RECEIVER_0_VALIDITY_REG, 1U);
	} else {
		XI2s_Rx_WriteReg(InstancePtr->Config.BaseAddress,
					XPAR_I2S_RECEIVER_0_VALIDITY_REG, 0U);
	}


}
