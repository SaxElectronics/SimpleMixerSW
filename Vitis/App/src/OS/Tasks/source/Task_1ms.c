
/*
 * Tasks_Init.c
 *
 */

#include "FreeRTOS.h"
#include "Task_1ms.h"
/* I2S */
#include "I2S.h"
/* I2C includes */
#include "xiicps_driver.h"
/* Audio Formatte */
#include "AudioFormatter.h"


/*
 * typedefs
 */
StaticTask_t TaskBuffer_1ms;
StackType_t  TaskStack_1ms[STACK_SIZE_TASK_1MS];
uint32_t TaskCounter_1ms;
TaskHandle_t xTaskHandle_1ms;


/*
 *  Task 1ms Function
 */
void Task_1ms(void * pvParameters)
{
    //TickType_t xDelayPeriod = mainNO_ERROR_CHECK_TASK_PERIOD;
    TickType_t xLastWakeTime;
    const  TickType_t xPeriod = TASK_PERIOD_TICKS_1MS;
 //  unsigned long ulErrorFound = pdFALSE;

        /* Just to stop compiler warnings. */
        ( void ) pvParameters;

        /* Initialise xLastExecutionTime so the first call to vTaskDelayUntil()
        works correctly. */
        xLastWakeTime = xTaskGetTickCount();

        /* Cycle for ever, delaying then checking all the other tasks are still
        operating without error.  The onboard LED is toggled on each iteration.
        If an error is detected then the delay period is decreased from
        mainNO_ERROR_CHECK_TASK_PERIOD to mainERROR_CHECK_TASK_PERIOD.  This has the
        effect of increasing the rate at which the onboard LED toggles, and in so
        doing gives visual feedback of the system status. */
        for( ;; )
        {
            /* Delay until it is time to execute again. */
            vTaskDelayUntil( &xLastWakeTime, xPeriod );
            /* Call here the cyclic functions */
            TaskCounter_1ms++;
            /* run I2S processing */
            //I2S_CycleFunction();



        }
}

