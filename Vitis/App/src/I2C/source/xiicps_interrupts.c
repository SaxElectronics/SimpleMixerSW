


#include "xiicps_driver.h"


/*****************************************************************************/
/**
*
* This function is the handler which performs processing to handle data events
* from the IIC.  It is called from an interrupt context such that the amount
* of processing performed should be minimized.
*
* This handler provides an example of how to handle data for the IIC and
* is application specific.
*
* @param	CallBackRef contains a callback reference from the driver, in
*		this case it is the instance pointer for the IIC driver.
* @param	Event contains the specific kind of event that has occurred.
*
* @return	None.
*
* @note		None.
*
*******************************************************************************/
I2C_InterruptStats I2CStats = {0};  // Global or static instance of the structure

void I2C_InterruptHandler(void *CallBackRef, u32 Event) {
    // Data transfer completion events.
    if (0 != (Event & XIICPS_EVENT_COMPLETE_RECV)) {
        I2CStats.CompleteRecvCount++;
        RecvComplete = TRUE;
    	xil_printf("I2C Interrupt: XIICPS_EVENT_COMPLETE_RECV.\n");
    } else if (0 != (Event & XIICPS_EVENT_COMPLETE_SEND)) {
        I2CStats.CompleteSendCount++;
        SendComplete = TRUE;
    	xil_printf("I2C Interrupt: XIICPS_EVENT_COMPLETE_SEND.\n");
    }

    // Grouped error handling for Slave, Receive, and NACK errors.
    if (0 != (Event & XIICPS_EVENT_ERROR) ||
        0 != (Event & XIICPS_EVENT_NACK) ||
        0 == (Event & XIICPS_EVENT_SLAVE_RDY)) {

        if (0 != (Event & XIICPS_EVENT_ERROR)) {
            xil_printf("I2C Error: Receive error.\n");
            I2CStats.ReceiveErrorCount++;

        }

        if (0 != (Event & XIICPS_EVENT_NACK)) {
            xil_printf("I2C Error: NACK Received.\n");
            I2CStats.NackReceivedErrorCount++;
        }

        if (0 == (Event & XIICPS_EVENT_SLAVE_RDY)) {
            xil_printf("I2C Error: Slave not ready.\n");
            I2CStats.SlaveNotReadyErrorCount++;
        }
        // Release the bus
	    I2C_ClearHoldBit(Iic.Config.BaseAddress);
        SendComplete = TRUE;

    }

    // Other error handling.
    if (0 != (Event & XIICPS_EVENT_TIME_OUT)) {
    	xil_printf("I2C Error: Transfer timed out.\n");
        I2CStats.TimeoutErrorCount++;
    }
    if (0 != (Event & XIICPS_EVENT_ARB_LOST)) {
    	xil_printf("I2C Error: Arbitration lost.\n");
        I2CStats.ArbLostErrorCount++;
    }
    if (0 != (Event & XIICPS_EVENT_RX_OVR)) {
    	xil_printf("I2C Error: RX overflow.\n");
        I2CStats.RxOverflowErrorCount++;
    }
    if (0 != (Event & XIICPS_EVENT_TX_OVR)) {
    	xil_printf("I2C Error: TX overflow.\n");
        I2CStats.TxOverflowErrorCount++;
    }
    if (0 != (Event & XIICPS_EVENT_RX_UNF)) {
    	xil_printf("I2C Error: RX underflow.\n");
        I2CStats.RxUnderflowErrorCount++;
    }

    I2CStats.TotalErrorCount = I2CStats.TimeoutErrorCount + I2CStats.ReceiveErrorCount +
                                  I2CStats.ArbLostErrorCount + I2CStats.NackReceivedErrorCount +
                                  I2CStats.SlaveNotReadyErrorCount + I2CStats.RxOverflowErrorCount +
                                  I2CStats.TxOverflowErrorCount + I2CStats.RxUnderflowErrorCount;
}

/*****************************************************************************/
/**
*
* This function is the handler which performs processing to handle data events
* from the IIC.  It is called from an interrupt context such that the amount
* of processing performed should be minimized.
*
* This handler provides an example of how to handle data for the IIC and
* is application specific.
*
* @param	CallBackRef contains a callback reference from the driver, in
*		this case it is the instance pointer for the IIC driver.
* @param	Event contains the specific kind of event that has occurred.
*
* @return	None.
*
* @note		None.
*
*******************************************************************************/
void I2C_Handler(void *CallBackRef, u32 Event)
{
	/*
	 * All of the data transfer has been finished.
	 */
	if (0 != (Event & XIICPS_EVENT_COMPLETE_RECV)){
		RecvComplete = TRUE;
	} else if (0 != (Event & XIICPS_EVENT_COMPLETE_SEND)) {
		SendComplete = TRUE;
	} else if (0 == (Event & XIICPS_EVENT_SLAVE_RDY)){
		/*
		 * If it is other interrupt but not slave ready interrupt, it is
		 * an error.
		 * Data was received with an error.
		 */
		TotalErrorCount++;
	}
}
