


#include <xiicps_driver.h>

/************************** Function Prototypes *******************************/

int IicPsMasterIntrExample(u16 DeviceId);

void I2C_Handler(void *CallBackRef, u32 Event);


/******************************************************************************/
/**
*
* Main function to call the example.
*
*
* @return	XST_SUCCESS if successful, XST_FAILURE if unsuccessful.
*
* @note		None.
*
*******************************************************************************/
int I2C_main_init(void)
{
	int Status;

	xil_printf("IIC Master Interrupt Example Test \r\n");

	/*
	 * Run the Iic Master Interrupt example , specify the Device ID that is
	 * generated in xparameters.h
	 */
	Status = I2C_Init(IIC_DEVICE_ID);
	//Status = IicPsMasterIntrExample(IIC_DEVICE_ID);

	if (Status != XST_SUCCESS) {
		xil_printf("IIC Master Interrupt Example Test Failed\r\n");
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

/**
 * @brief Initialize the I2C peripheral.
 *
 * This function initializes the I2C device and configures it for communication.
 * The initialization involves looking up configuration, initializing the driver,
 * performing a self-test, and setting up the handler and clock rate.
 *
 * @param DeviceId The device ID of the I2C peripheral as defined in xparameters.h
 * @return XST_SUCCESS if initialization was successful; XST_FAILURE otherwise.
 */
int I2C_Init(u16 DeviceId)
{
    int Status;
    XIicPs_Config *Config;

    // Initialize the IIC driver
    Config = XIicPs_LookupConfig(DeviceId);
    if (NULL == Config) {
        return XST_FAILURE;
    }

    Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    // Perform a self-test to ensure that the hardware was built correctly
    Status = XIicPs_SelfTest(&Iic);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    // Setup the handlers for the IIC
    XIicPs_SetStatusHandler(&Iic, (void *) &Iic, I2C_InterruptHandler);

    // Set the IIC serial clock rate
    XIicPs_SetSClk(&Iic, IIC_SCLK_RATE);

    // Initialize the send buffer bytes with a pattern
    for (int Index = 0; Index < TEST_BUFFER_SIZE; Index++) {
        SendBuffer[Index] = 0;
        RecvBuffer[Index] = 0;
    }

    return XST_SUCCESS;
}



/*****************************************************************************/
/**
*
* This function does a minimal test on the Iic device and driver as a
* design example. The purpose of this function is to illustrate
* how to use the XIicPs driver.
*
* This function sends data and expects to receive the same data through the IIC
* using the Aardvark test hardware.
*
* This function uses interrupt driver mode of the IIC.
*
* @param	DeviceId is the Device ID of the IicPs Device and is the
*		XPAR_<IICPS_instance>_DEVICE_ID value from xparameters.h
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
*
* @note
*
* This function contains an infinite loop such that if interrupts are not
* working it may never return.
*
*******************************************************************************/
int IicPsMasterIntrExample(u16 DeviceId)
{
	int Status;
	XIicPs_Config *Config;
	int Index;
	int tmp;
	int BufferSizes[NUMBER_OF_SIZES] = {1, 2, 19, 31, 32, 33, 62, 63, 64,
	65, 66, 94, 95, 96, 97, 98, 99, 250};

	/*
	 * Initialize the IIC driver so that it's ready to use
	 * Look up the configuration in the config table, then initialize it.
	 */
	Config = XIicPs_LookupConfig(DeviceId);
	if (NULL == Config) {
		return XST_FAILURE;
	}

	Status = XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built correctly.
	 */
	Status = XIicPs_SelfTest(&Iic);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}


	/*
	 * Setup the handlers for the IIC that will be called from the
	 * interrupt context when data has been sent and received, specify a
	 * pointer to the IIC driver instance as the callback reference so
	 * the handlers are able to access the instance data.
	 */
	XIicPs_SetStatusHandler(&Iic, (void *) &Iic, I2C_Handler);

	/*
	 * Set the IIC serial clock rate.
	 */
	XIicPs_SetSClk(&Iic, IIC_SCLK_RATE);

	/*
	 * Initialize the send buffer bytes with a pattern to send and the
	 * the receive buffer bytes to zero to allow the receive data to be
	 * verified.
	 */
	for (Index = 0; Index < TEST_BUFFER_SIZE; Index++) {
		SendBuffer[Index] = (Index % TEST_BUFFER_SIZE);
		RecvBuffer[Index] = 0;
	}

	for(Index = 0; Index < NUMBER_OF_SIZES; Index++) {

		/* Wait for bus to become idle
		 */
		while (XIicPs_BusIsBusy(&Iic)) {
			/* NOP */
		}

		SendComplete = FALSE;

		/*
		 * Send the buffer, errors are reported by TotalErrorCount.
		 */
		XIicPs_MasterSend(&Iic, SendBuffer, BufferSizes[Index],
				IIC_SLAVE_ADDR);

		/*
		 * Wait for the entire buffer to be sent, letting the interrupt
		 * processing work in the background, this function may get
		 * locked up in this loop if the interrupts are not working
		 * correctly.
		 */
		while (!SendComplete) {
			if (0 != TotalErrorCount) {
				return XST_FAILURE;
			}
		}

		/*
		 * Wait bus activities to finish.
		 */
		while (XIicPs_BusIsBusy(&Iic)) {
			/* NOP */
		}

		/*
		 * Receive data from slave, errors are reported through
		 * TotalErrorCount.
		 */
		RecvComplete = FALSE;
		XIicPs_MasterRecv(&Iic, RecvBuffer, BufferSizes[Index],
				IIC_SLAVE_ADDR);

		while (!RecvComplete) {
			if (0 != TotalErrorCount) {
				return XST_FAILURE;
			}
		}

		/* Check for received data.
		 */
		for(tmp = 0; tmp < BufferSizes[Index]; tmp ++) {

			/*
			 * Aardvark as slave can only set up to 64 bytes for
			 * output.
			 */
			if (RecvBuffer[tmp] != tmp % 64) {
				return XST_FAILURE;
			}
		}
	}
	return XST_SUCCESS;
}
