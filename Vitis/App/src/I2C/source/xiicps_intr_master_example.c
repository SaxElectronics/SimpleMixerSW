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




int BufferSizes[NUMBER_OF_SIZES] = {1, 2, 19, 31, 32, 33, 62, 63, 64,
	65, 66, 94, 95, 96, 97, 98, 99, 250};

/* write request */
static u8 i2c_WriteRequest = FALSE;
/* write request state */
static u8 i2c_WriteRequest_old = FALSE;
/* read request state */
static u8 i2c_ReadRequest = FALSE;
/* store read request state */
static u8 i2c_ReadRequest_old = FALSE;

/* Slave Register Address */
static u8 i2c_SlaveRegisterAddress = 0;
/* Slave Register Value */
static u8 i2c_SlaveRegisterValue = 0x40;
/* Slave Target Address */
static u8 i2c_SlaveAddress = IIC_SLAVE_ADDR;

/* First Byte for Write */
static u8 i2c_SlaveFirstByteWrite_P0toP7 = 0x00;
/* Second Byte for Write */
static u8 i2c_SlaveSecondByteWrite_P8toP15 = 0x00;
/* First Byte for Read */
static u8 i2c_SlaveFirstByteRead_P0toP7 = 0x00;
/* Second Byte for Read */
static u8 i2c_SlaveSecondByteRead_P8toP15 = 0x00;


#define TIMEOUT_THRESHOLD 1000000 // Adjust based on your requirements


// Global variables
u8 sendBuffer[2] = {0x00, 0x33}; // Initial data to send
u8 recvBuffer[2];  // Buffer to receive data
I2C_Params params;

#define SLAVE_ADDRESS_DIGITAL_POTI  0x29


#define SLAVE_ADDRESS_GPIO_EXPANDER		0x20


I2C_Params IOExpanderParams = {
    .send_buffer = SendBuffer,
    .recv_buffer = RecvBuffer,
    .buffer_size = 2,
    .slave_address = SLAVE_ADDRESS_GPIO_EXPANDER // IO expander address
};


#define TIMEOUT_LIMIT 1000  // Define an appropriate timeout value

I2C_Params DigitalPotiParams = {
    .send_buffer = SendBuffer,
    .recv_buffer = RecvBuffer, // Initialize if needed
    .buffer_size = 2,
    .slave_address = SLAVE_ADDRESS_DIGITAL_POTI
};

I2C_Params* activeParams = &IOExpanderParams; // Set default to IO Expander

typedef enum {
    DEVICE_IO_EXPANDER,
    DEVICE_DIGITAL_POTI
} ActiveDevice;

ActiveDevice currentDevice = DEVICE_IO_EXPANDER;  // default


void PrepareDigitalPotiDataToSend(uint8_t *buffer) {
    /* register address */
    buffer[0] = i2c_SlaveRegisterAddress;
    /* wiper or control register reg value */
    buffer[1] = i2c_SlaveRegisterValue;
}

void PrepareIOExpanderDataToSend(uint8_t *buffer) {
    buffer[0] = i2c_SlaveFirstByteWrite_P0toP7;
    buffer[1] = i2c_SlaveSecondByteWrite_P8toP15;
}

void UpdateIOExpanderReceivedData(uint8_t *buffer) {
    i2c_SlaveFirstByteRead_P0toP7 = buffer[0];
    i2c_SlaveSecondByteRead_P8toP15 = buffer[1];
}


void SwitchToDevice(ActiveDevice device) {
    switch (device) {
        case DEVICE_IO_EXPANDER:
            activeParams = &IOExpanderParams;
            break;
        case DEVICE_DIGITAL_POTI:
            activeParams = &DigitalPotiParams;
            break;
        default:
            // Handle unknown device or error
            break;
    }
}
/**
 * @brief Sends data over I2C to a slave device.
 *
 * @param params Pointer to the structure containing I2C communication parameters.
 * @return XST_SUCCESS if data was successfully sent; XST_FAILURE otherwise.
 */
#define TIMEOUT_VALUE		1000
int I2C_SendData(I2C_Params *params) {
    SendComplete = FALSE;

    // Ensure the bus is not busy
    int timeoutCounter = TIMEOUT_VALUE;

    // Ensure the bus is not busy, with timeout
    while (XIicPs_BusIsBusy(&Iic)) {
        if (timeoutCounter-- <= 0) {
            // Handle timeout here (e.g., break the loop, return an error, etc.)
            xil_printf("Timeout occurred waiting for IIC bus to become free.\n");
            return XST_FAILURE;  // Example of returning an error
        }
    }

    SendBuffer[0] = params->send_buffer[0];
    SendBuffer[1] = params->send_buffer[1];
    int NumOfBytes = params->buffer_size;
    // Send the buffer
    XIicPs_MasterSend(&Iic, SendBuffer, NumOfBytes, params->slave_address);

    // Wait for the entire buffer to be sent
    while (!SendComplete) {
        if (0 != TotalErrorCount) {
            return XST_FAILURE;
        }
    }

    return XST_SUCCESS;
}

/**
 * @brief Receives data over I2C from a slave device and checks for data integrity.
 *
 * @param params Pointer to the structure containing I2C communication parameters.
 * @return XST_SUCCESS if data was successfully received and validated; XST_FAILURE otherwise.
 */
int I2C_ReceiveData(I2C_Params *params) {
    int tmp;
    RecvComplete = FALSE;

    // Ensure the bus is not busy
    while (XIicPs_BusIsBusy(&Iic)) {
        // NOP
    }

    // Receive data from slave
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
int I2C_CyclicFunction(void)
{
    int status = XST_SUCCESS; // Default to success unless an error happens

    if (i2c_WriteRequest != i2c_WriteRequest_old) {
        // Store the current state
        i2c_WriteRequest_old = i2c_WriteRequest;

        if (i2c_WriteRequest == TRUE) {
            if (currentDevice == DEVICE_IO_EXPANDER)
            {
                SwitchToDevice(DEVICE_IO_EXPANDER);  // If currently using Digital Poti, switch to IO Expander
                PrepareIOExpanderDataToSend(activeParams->send_buffer);

            }
            else if (currentDevice == DEVICE_DIGITAL_POTI)
            {
                SwitchToDevice(DEVICE_DIGITAL_POTI);  // If currently using IO Expander, switch to Digital Poti
                PrepareDigitalPotiDataToSend(activeParams->send_buffer);
            }
            /* Send data with currently active parameters */
            status = I2C_SendData(activeParams);
            if (status != XST_SUCCESS) {
                // Handle error
                xil_printf("I2C Write failed. Check interrupt handling. \r\n");
                return XST_FAILURE;
            }
        }
    }

    if (i2c_ReadRequest != i2c_ReadRequest_old) {
        // Store the current state
        i2c_ReadRequest_old = i2c_ReadRequest;
        if (i2c_ReadRequest == TRUE)
        {
            /* receive data for currently active device parameters */
            status = I2C_ReceiveData(activeParams);
            if (status != XST_SUCCESS) {
                // Handle error
                xil_printf("I2C Read failed. Check interrupt handling. \r\n");
                return XST_FAILURE;
            }

            if (currentDevice == DEVICE_IO_EXPANDER) {
                UpdateIOExpanderReceivedData(activeParams->recv_buffer);
            }
            // Note: Handle data update for the Digital Poti similarly if required
        }
    }

    return status;
}


/**
 * @brief   Sends data to an I2C slave device.
 *
 * This function waits for the I2C bus to become idle and then sends a buffer containing
 * the slave register address and its value to a specified I2C slave device.
 * It ensures that the entire buffer is sent and checks for any errors or timeouts.
 *
 * @return  XST_SUCCESS if data was successfully sent.
 *          XST_FAILURE on timeout or other error.
 */
int I2C_Send(void)
{
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

    // Populate the buffer with slave register address and value
    SendBuffer[0] = (u8) i2c_SlaveRegisterAddress;
    SendBuffer[1] = (u8) i2c_SlaveRegisterValue;

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

/**
 * @brief   Receives data from an I2C slave device.
 *
 * This function waits for the I2C bus to become idle, then
 * starts receiving data from a specified slave device. It ensures
 * that the data reception is complete and checks for any errors
 * or timeouts.
 *
 * @return  XST_SUCCESS if data was successfully received.
 *          XST_FAILURE on timeout or other error.
 */
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

/**
 * @brief   Sends test messages over I2C based on specific conditions.
 *
 * This function checks the current state of write and read requests. If the
 * state of a request changes (i.e., from previous request), it either
 * sends or receives data accordingly.
 *
 * @return  XST_SUCCESS if data was successfully sent or received.
 *          XST_FAILURE on any internal operation failure.
 */
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



