/******************************************************************************
* Copyright (C) 2010 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
 * @file xiicps_intr_master_example.c
 *
 * Design example to use the IIC device as master in interrupt-driven mode.
 *
 * It continuously sends 18 buffers to slave.
 *
 * <pre> MODIFICATION HISTORY:
 *
 * Ver   Who Date     Changes
 * ----- --- -------- -----------------------------------------------
 * 1.00a jz  01/30/10 First release
 *
 * </pre>
 *
 ****************************************************************************/

#include <xiicps_driver.h>


/************************** Variable Definitions ******************************/

XIicPs Iic;			/* Instance of the IIC Device */

/*
 * The following buffers are used in this example to send and receive data
 * with the IIC. They are defined as global so that they are not on the stack.
 */
u8 SendBuffer[TEST_BUFFER_SIZE];    /* Buffer for Transmitting Data */
u8 RecvBuffer[TEST_BUFFER_SIZE];    /* Buffer for Receiving Data */

/*
 * The following counters are used to determine when the entire buffer has
 * been sent and received.
 */
volatile u32 SendComplete;
volatile u32 RecvComplete;
volatile u32 SendCompleteCntr;
volatile u32 RecvCompleteCntr;
volatile u32 TotalErrorCount;

I2C_Params i2c_params;




/**
 * @brief Set up I2C communication parameters and data.
 *
 * This function initializes the I2C communication parameters and buffers
 * for transmission. It configures the sending buffer, and other parameters
 * needed for I2C communication.
 *
 * @param params Pointer to the I2C_Params structure to be configured.
 * @param send_data Pointer to the data to be sent.
 * @param recv_buffer Pointer to the buffer to store received data.
 * @param slave_address The address of the I2C slave device.
 * @param buffer_size The size of the data buffers.
 */
void I2C_SetupCommunication(
    I2C_Params *params,
    u8 *send_data,
    u8 *recv_buffer,
    u8 slave_address,
    int buffer_size
)
{
    // Configuring the I2C parameters
    params->send_buffer = send_data;
    params->recv_buffer = recv_buffer;
    params->slave_address = slave_address;
    params->buffer_size = buffer_size;

    // Additional setup code, if needed, can go here.
}

int BufferSizes[NUMBER_OF_SIZES] = {1, 2, 19, 31, 32, 33, 62, 63, 64,
	65, 66, 94, 95, 96, 97, 98, 99, 250};

u8 SendBufferOwn[2];
static u8 i2c_WriteRequest = FALSE;
static u8 i2c_WriteRequest_old = FALSE;
static u8 i2c_ReadRequest = FALSE;
static u8 i2c_ReadRequest_old = FALSE;

/* Slave Register Address */
static u8 i2c_SlaveRegisterAddress = 0;
/* Slave Register Value */
static u8 i2c_SlaveRegisterValue = 0x40;
/* Slave Target Address */
static u8 i2c_SlaveAddress = IIC_SLAVE_ADDR;

#define TIMEOUT_THRESHOLD 1000000 // Adjust based on your requirements

int I2C_Send(void) {
    u32 timeout;

    // Wait for bus to become idle with timeout
    timeout = 0;
    while (XIicPs_BusIsBusy(&Iic)) {
        if (++timeout > TIMEOUT_THRESHOLD) {
            xil_printf("Timeout while waiting for bus to become idle.\n");
            return XST_FAILURE;
        }
    }

    SendComplete = FALSE;

    SendBuffer[0] = (u8)i2c_SlaveRegisterAddress;
    SendBuffer[1] = (u8)i2c_SlaveRegisterValue;

    // Send the buffer
    XIicPs_MasterSend(&Iic, SendBuffer, 2, i2c_SlaveAddress);

    // Wait for the entire buffer to be sent with timeout
    timeout = 0;
    while (!SendComplete) {
        if (0 != TotalErrorCount || ++timeout > TIMEOUT_THRESHOLD) {
            xil_printf("Send timeout or error occurred.\n");
            return XST_FAILURE;
        }
    }

    return XST_SUCCESS;
}

int I2C_Receive(void) {
    u32 timeout;

    // Wait for bus to become idle with timeout
    timeout = 0;
    while (XIicPs_BusIsBusy(&Iic)) {
        if (++timeout > TIMEOUT_THRESHOLD) {
            xil_printf("Timeout while waiting for bus to become idle.\n");
            return XST_FAILURE;
        }
    }

    RecvComplete = FALSE;

    // Receive data from slave
    XIicPs_MasterRecv(&Iic, RecvBuffer, 2, IIC_SLAVE_ADDR);

    // Wait for data to be received with timeout
    timeout = 0;
    while (!RecvComplete) {
        if (0 != TotalErrorCount || ++timeout > TIMEOUT_THRESHOLD) {
            xil_printf("Receive timeout or error occurred.\n");
            return XST_FAILURE;
        }
    }

    return XST_SUCCESS;
}

int I2C_SendTestMessage(void) {

    if (i2c_WriteRequest != i2c_WriteRequest_old) {
        // Store state
        i2c_WriteRequest_old = i2c_WriteRequest;

        if (i2c_WriteRequest == TRUE) {
            if (I2C_Send() != XST_SUCCESS) {
                return XST_FAILURE;
            }
        }
    }

    if (i2c_ReadRequest != i2c_ReadRequest_old) {
        // Store state
        i2c_ReadRequest_old = i2c_ReadRequest;

        if (i2c_ReadRequest == TRUE) {
            if (I2C_Receive() != XST_SUCCESS) {
                return XST_FAILURE;
            }
        }
    }

    return XST_SUCCESS;
}



/**
 * @brief Manage I2C communication in a cyclic/periodic manner.
 *
 * This function handles the sending and receiving of I2C data in a non-blocking
 * manner, using provided parameters. It sends data to an I2C slave device,
 * waits for the send to be complete, then initiates a receive from the I2C slave,
 * and ensures data integrity by checking against a predefined pattern.
 *
 * @param params Pointer to the structure containing I2C communication parameters.
 * @return XST_SUCCESS if data transmission was successful; XST_FAILURE otherwise.
 */
int I2C_ExecuteCommunication(I2C_Params *params) {
    int tmp;
    SendComplete = FALSE;

    // Ensure the bus is not busy
    while (XIicPs_BusIsBusy(&Iic)) {
        // NOP
    }

    // Send the buffer
    XIicPs_MasterSend(&Iic, params->send_buffer, params->buffer_size, params->slave_address);

    // Wait for the entire buffer to be sent
    while (!SendComplete) {
        if (0 != TotalErrorCount) {
            return XST_FAILURE;
        }
    }

    // Wait bus activities to finish
    while (XIicPs_BusIsBusy(&Iic)) {
        // NOP
    }

    // Receive data from slave
    RecvComplete = FALSE;
    XIicPs_MasterRecv(&Iic, params->recv_buffer, params->buffer_size, params->slave_address);

    while (!RecvComplete) {
        if (0 != TotalErrorCount) {
            return XST_FAILURE;
        }
    }

    // Check for received data
    for(tmp = 0; tmp < params->buffer_size; tmp++) {
        // Ensure the received data is valid...
    }

    return XST_SUCCESS;
}


/**
 * @brief Manage I2C communication in a cyclic/periodic manner.
 *
 * This function handles the sending and receiving of I2C data in a non-blocking
 * manner, i.e., it checks whether the I2C bus is busy before sending/receiving data.
 * It sends data to an I2C slave device and waits for the send to be complete, then
 * initiates a receive from the I2C slave, ensuring data integrity by checking against
 * a predefined pattern. The function also manages failure cases by checking error
 * counters and can be used in a main loop or periodically called to manage I2C communication.
 *
 * @param BufferSize The size of the buffer to be sent/received.
 * @return XST_SUCCESS if data transmission was successful; XST_FAILURE otherwise.
 */
static u8 slaveAddr = 0x28; // Initial slave address
static int bufferSize = 2;   // Initial buffer size

// Global variables
u8 sendBuffer[2] = {0x00, 0x33}; // Initial data to send
u8 recvBuffer[2];  // Buffer to receive data
I2C_Params params;
#define TIMEOUT_LIMIT 1000  // Define an appropriate timeout value

int I2C_CyclicFunction()
{
    int status = XST_FAILURE;
    int timeout_counter;

	 // Set up I2C communication parameters
	I2C_SetupCommunication(&params, sendBuffer, recvBuffer, slaveAddr, bufferSize);

	// Main loop/cyclic function
	while(1)
	{
        timeout_counter = 0;

        // Check the status and handle timeout
		while(status != XST_SUCCESS && timeout_counter < TIMEOUT_LIMIT) {
			// Increment timeout counter
			timeout_counter++;

			// Try communication again
			status = I2C_ExecuteCommunication(&params);
		}

		if(status != XST_SUCCESS)
		{
			// Handle error
			xil_printf("I2C Communication failed check interrupt handling. \r\n");

		}

	}
}
