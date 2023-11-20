#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "ISR_Tasks.h"

#include "AudioFormatter.h"


/* Task handles */
TaskHandle_t xIsrHandle_AF_MM2S = NULL;
TaskHandle_t xIsrHandle_AF_S2MM = NULL;

TaskHandle_t xIsrHandle_I2C = NULL;


/* Semaphores for each ISR task */
/* not used currently, only task notifications */
//SemaphoreHandle_t xCanSemaphore;
//SemaphoreHandle_t xClaSemaphore;
//SemaphoreHandle_t xI2cSemaphore;

/* ISR Tasks Counters */
uint32_t IsrTask_Counter_AF_MM2S = 0;
uint32_t IsrTask_Counter_AF_S2MM = 0;
uint32_t IsrTask_Counter_ClaTask8 = 0;
uint32_t IsrTask_Counter_CANA = 0;
uint32_t IsrTask_Counter_Check = 0;

/* Task functions prototypes */
void CANA_InterruptServiceRoutine_Task(void *pvParameters);
void CLA_Task8_InterruptServiceRoutine_Task(void *pvParameters);
void CLA_Task1_InterruptServiceRoutine_Task(void *pvParameters);

void I2CA_InterruptServiceRoutine_Task(void *pvParameters);




/* Input Queue */
QueueHandle_t audioDataQueueInput;
/* Output Queue */
QueueHandle_t audioDataQueueOutput;
/* AF Pointer Que */
QueueHandle_t audioFormatterQueue;

#define QUEUE_LENGTH 8  // Adjust this based on your calculation

/* ISR Tasks */
void XMM2SAFCallbackInterruptOnComplete_Task(void *pvParameters);
void XS2MMAFCallbackInterruptOnComplete_Task(void *pvParameters);

void Create_ISR_Tasks_Init(void)
{
	// Initialize the queues
	audioDataQueueInput = xQueueCreate(QUEUE_LENGTH, sizeof(AudioData_t));
	audioDataQueueOutput = xQueueCreate(QUEUE_LENGTH, sizeof(AudioData_t));
	audioFormatterQueue = xQueueCreate(QUEUE_LENGTH, sizeof(XAudioFormatter*));

	if (audioDataQueueInput == NULL) {
		// Handle error: Queue creation failed
	}

    /* Create Audio Formatter ISR task MM2S */
    xTaskCreate(
    		XMM2SAFCallbackInterruptOnComplete_Task,
        "AF MM2S ISR Task",
        128,
        NULL,
		TASK_PRIORITY_AF_MM2S_ISR,  /* Adjust priority here */
        &xIsrHandle_AF_MM2S
    );

    /* Create Audio Formatter ISR task S2MM */
    xTaskCreate(
    		XS2MMAFCallbackInterruptOnComplete_Task,
        "AF MM2S ISR Task",
        128,
        NULL,
		TASK_PRIORITY_AF_MM2S_ISR,  /* Adjust priority here */
        &xIsrHandle_AF_S2MM
    );

//    /* Create I2C ISR task */
//    xTaskCreate(
//    		I2CA_InterruptServiceRoutine_Task,
//        "I2C ISR Task1",
//        128,
//        NULL,
//        ISR_TASK_CLA1_PRIORITY,  /* Adjust priority here */
//        &xIsrHandle_I2C
//    );

}



void XMM2SAFCallbackInterruptOnComplete_Task(void *pvParameters)
{
    XAudioFormatter *AFInstancePtr;

    for (;;)
    {
        // Receive data from the queue
        if (xQueueReceive(audioFormatterQueue, &AFInstancePtr, portMAX_DELAY) == pdPASS)
        {
            // Call the function to process the data
            XMM2SAFCallbackInterruptOnComplete_InTask(AFInstancePtr);
        }
    }
}



void XS2MMAFCallbackInterruptOnComplete_Task(void *pvParameters)
{
    AudioData_t audioDataFromISR;

    for (;;)
    {
        // Receive data from the queue
        if (xQueueReceive(audioDataQueueOutput, &audioDataFromISR, portMAX_DELAY) == pdPASS)
        {
            // Process the audio data for one period
            ProcessAudioPeriod(&audioDataFromISR);
        }
    }
}

