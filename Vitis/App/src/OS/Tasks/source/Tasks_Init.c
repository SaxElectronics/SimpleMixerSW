/*
 * FreeRTOS V202112.00
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/******************************************************************************
 * NOTE 1:  This project provides three demo applications.  A simple blinky
 * style project, a more comprehensive test and demo application, and an
 * lwIP example.  The mainSELECTED_APPLICATION setting in main.c is used to
 * select between the three.  See the notes on using mainSELECTED_APPLICATION
 * in main.c.  This file implements the simply blinky style version.
 *
 * NOTE 2:  This file only contains the source code that is specific to the
 * basic demo.  Generic functions, such FreeRTOS hook functions, and functions
 * required to configure the hardware are defined in main.c.
 ******************************************************************************
 *
 * main_blinky() creates one queue, and two tasks.  It then starts the
 * scheduler.
 *
 * The Queue Send Task:
 * The queue send task is implemented by the prvQueueSendTask() function in
 * this file.  prvQueueSendTask() sits in a loop that causes it to repeatedly
 * block for 200 milliseconds, before sending the value 100 to the queue that
 * was created within main_blinky().  Once the value is sent, the task loops
 * back around to block for another 200 milliseconds...and so on.
 *
 * The Queue Receive Task:
 * The queue receive task is implemented by the prvQueueReceiveTask() function
 * in this file.  prvQueueReceiveTask() sits in a loop where it repeatedly
 * blocks on attempts to read data from the queue that was created within
 * main_blinky().  When data is received, the task checks the value of the
 * data, and if the value equals the expected 100, toggles an LED.  The 'block
 * time' parameter passed to the queue receive function specifies that the
 * task should be held in the Blocked state indefinitely to wait for data to
 * be available on the queue.  The queue receive task will only leave the
 * Blocked state when the queue send task writes to the queue.  As the queue
 * send task writes to the queue every 200 milliseconds, the queue receive
 * task leaves the Blocked state every 200 milliseconds, and therefore toggles
 * the LED every 200 milliseconds.
 */

#include "stdbool.h"

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Standard demo includes. */
#include "partest.h"

/*
 * include Tasks headers
 */
#include "Task_100ms.h"
#include "Task_10ms.h"
#include "Task_1ms.h"

/* Priorities at which the tasks are created. */
#define mainQUEUE_RECEIVE_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )
#define	mainQUEUE_SEND_TASK_PRIORITY		( tskIDLE_PRIORITY + 1 )

/* The rate at which data is sent to the queue.  The 200ms value is converted
to ticks using the portTICK_PERIOD_MS constant. */
#define mainQUEUE_SEND_FREQUENCY_MS			( 200 / portTICK_PERIOD_MS )

/* The number of items the queue can hold.  This is 1 as the receive task
will remove items as they are added, meaning the send task should always find
the queue empty. */
#define mainQUEUE_LENGTH					( 1 )

/* The LED toggled by the Rx task. */
#define mainTASK_LED						( 0 )

/*-----------------------------------------------------------*/

/*
 * The tasks as described in the comments at the top of this file.
 */
static void prvQueueReceiveTask( void *pvParameters );
static void prvQueueSendTask( void *pvParameters );

/*-----------------------------------------------------------*/

/* The queue used by both tasks. */
static QueueHandle_t xQueue = NULL;

void FreeRTOS_CreateTasks_Init(void)
{
	/* Create the queue. */
	xQueue = xQueueCreate( mainQUEUE_LENGTH, sizeof( uint32_t ) );

	if( xQueue != NULL )
	{
		/* Start the two tasks as described in the comments at the top of this
		file. */
		xTaskCreate( prvQueueReceiveTask,				/* The function that implements the task. */
					"Rx", 								/* The text name assigned to the task - for debug only as it is not used by the kernel. */
					configMINIMAL_STACK_SIZE, 			/* The size of the stack to allocate to the task. */
					NULL, 								/* The parameter passed to the task - not used in this case. */
					mainQUEUE_RECEIVE_TASK_PRIORITY, 	/* The priority assigned to the task. */
					&xRxTaskHandle );								/* The task handle is not required, so NULL is passed. */

		xTaskCreate( prvQueueSendTask,
				"TX",
				configMINIMAL_STACK_SIZE,
				NULL,
				mainQUEUE_SEND_TASK_PRIORITY,
				&xTxTaskHandle  );

		 /*
		 * create periodic tasks 1ms, 10ms and 100ms
		 */
		xTaskHandle_1ms =  xTaskCreateStatic(Task_1ms,         // Function that implements the task.
								 "1ms Task",      // Text name for the task.
								 STACK_SIZE_TASK_1MS,           // Number of indexes in the xStack array.
								 ( void * ) NULL,      // Parameter passed into the task.
								 TASK_PRIORITY_1MS, // Priority at which the task is created.
								 TaskStack_1ms,        // Array to use as the task's stack.
								 &TaskBuffer_1ms );    // Variable to hold the task's data structure.
		xTaskHandle_10ms =  xTaskCreateStatic(Task_10ms,         // Function that implements the task.
									 "10ms Task",      // Text name for the task.
									 STACK_SIZE_TASK_10MS,           // Number of indexes in the xStack array.
									 ( void * ) NULL,      // Parameter passed into the task.
									 TASK_PRIORITY_10MS, // Priority at which the task is created.
									 TaskStack_10ms,        // Array to use as the task's stack.
									 &TaskBuffer_10ms );    // Variable to hold the task's data structure.
		xTaskHandle_100ms =  xTaskCreateStatic(Task_100ms,         // Function that implements the task.
									  "100ms Task",      // Text name for the task.
									  STACK_SIZE_TASK_100MS,           // Number of indexes in the xStack array.
									  ( void * ) NULL,      // Parameter passed into the task.
									  TASK_PRIORITY_100MS, // Priority at which the task is created.
									  TaskStack_100ms,        // Array to use as the task's stack.
									  &TaskBuffer_100ms );    // Variable to hold the task's data structure.

		 /* Create the task that performs the 'check' functionality with dynamic memory allocation */
		/* ToDo: Check if a second semaphore is required for dynamic memory allocation is required*/
		xTaskCreate( prvCheckTask, "Check", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, &xCheckTaskHandle );

	}
}


void FreeRTOS_StartScheduler(void)
{
	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was either insufficient FreeRTOS heap memory available for the idle
	and/or timer tasks to be created, or vTaskStartScheduler() was called from
	User mode.  See the memory management section on the FreeRTOS web site for
	more details on the FreeRTOS heap http://www.freertos.org/a00111.html.  The
	mode from which main() is called is set in the C start up code and must be
	a privileged mode (not user mode). */
	for( ;; );
}

/*-----------------------------------------------------------*/
TaskHandle_t xTxTaskHandle;
uint32_t ulTxTaskCounter;
static void prvQueueSendTask( void *pvParameters )
{
TickType_t xNextWakeTime;
const unsigned long ulValueToSend = 100UL;

	/* Remove compiler warning about unused parameter. */
	( void ) pvParameters;

	/* Initialise xNextWakeTime - this only needs to be done once. */
	xNextWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		/* Place this task in the blocked state until it is time to run again. */
		vTaskDelayUntil( &xNextWakeTime, mainQUEUE_SEND_FREQUENCY_MS );
		ulTxTaskCounter++;
		/* Send to the queue - causing the queue receive task to unblock and
		toggle the LED.  0 is used as the block time so the sending operation
		will not block - it shouldn't need to block as the queue should always
		be empty at this point in the code. */
		xQueueSend( xQueue, &ulValueToSend, 0U );
	}
}
/*-----------------------------------------------------------*/
TaskHandle_t xRxTaskHandle;
uint32_t ulRxTaskCounter;

static void prvQueueReceiveTask( void *pvParameters )
{
unsigned long ulReceivedValue;
const unsigned long ulExpectedValue = 100UL;

	/* Remove compiler warning about unused parameter. */
	( void ) pvParameters;

	for( ;; )
	{
		/* Wait until something arrives in the queue - this task will block
		indefinitely provided INCLUDE_vTaskSuspend is set to 1 in
		FreeRTOSConfig.h. */
		xQueueReceive( xQueue, &ulReceivedValue, portMAX_DELAY );
		ulRxTaskCounter++;
		/*  To get here something must have been received from the queue, but
		is it the expected value?  If it is, toggle the LED. */
		if( ulReceivedValue == ulExpectedValue )
		{
			vParTestToggleLED( mainTASK_LED );
			ulReceivedValue = 0U;
		}
	}
}


/*
 * if xTaskError is true, some of the tasks are not running;
 */
bool xTaskError;
TaskHandle_t xCheckTaskHandle;
uint32_t IsrTask_Counter_Check = 0;

void prvCheckTask( void *pvParameters )
{
TickType_t xDelayPeriod = TASK_PERIOD_TICKS_100MS;
TickType_t xLastExecutionTime;
static uint32_t TaskCounter_1ms_old;
static uint32_t TaskCounter_10ms_old;
static uint32_t TaskCounter_100ms_old;

unsigned long ulErrorFound = pdFALSE;

    /* Just to stop compiler warnings. */
    ( void ) pvParameters;

    /* Initialise xLastExecutionTime so the first call to vTaskDelayUntil()
    works correctly. */
    xLastExecutionTime = xTaskGetTickCount();

    /* Cycle for ever, delaying then checking all the other tasks are still
    operating without error.  The LEDs will increase toglling if one of the tasks
    is not anymore running */
    for( ;; )
    {
        /* Delay until it is time to execute again. */
        vTaskDelayUntil( &xLastExecutionTime, xDelayPeriod );


        /* Check all tasks if they have incremented their counter (running)*/
        if( TaskCounter_1ms == TaskCounter_1ms_old)
        {
            ulErrorFound |= 1UL << 0UL;
        }

        if( TaskCounter_10ms == TaskCounter_10ms_old)
        {
            ulErrorFound |= 1UL << 1UL;
        }

        if( TaskCounter_100ms == TaskCounter_100ms_old)
        {
            ulErrorFound |= 1UL << 2UL;
        }

        TaskCounter_1ms_old = TaskCounter_1ms;
        TaskCounter_10ms_old = TaskCounter_10ms;
        TaskCounter_100ms_old = TaskCounter_100ms;

        if( ulErrorFound != pdFALSE )
        {
            /* An error has been detected in one of the tasks - flash the LED
            at a higher frequency to give visible feedback that something has
            gone wrong (it might just be that the loop back connector required
            by the comtest tasks has not been fitted). */
            xDelayPeriod = mainERROR_CHECK_TASK_PERIOD;
            xTaskError = true;
        }
    }
}
