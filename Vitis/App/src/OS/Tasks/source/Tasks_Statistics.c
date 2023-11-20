
/*
 * Basic Platform Typedefs
 */

#include <string.h>


/*
 * FreeRTOS includes
 */

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "Task_100ms.h"
#include "Task_10ms.h"
#include "Task_1ms.h"

#include "ISR_Tasks.h"
#include "Tasks_Statistics.h"


// Assuming configTICK_RATE_STATS_HZ is defined elsewhere and is the rate in Hz at which the stats tick counter increments.
#define TICKS_PER_SECOND (configTICK_RATE_STATS_HZ)
#define MICROSECONDS_PER_SECOND 1000000
#define TICKS_TO_MICROSECONDS(ticks) ((ticks * MICROSECONDS_PER_SECOND) / TICKS_PER_SECOND)



TaskRunTimeStats_t xRunTimeStats[configSTATS_MAXNUMBER_OF_TASKS];
TaskMapping_t xTaskMappings[configSTATS_MAXNUMBER_OF_TASKS];


/**
 * Initializes the runtime statistics feature of FreeRTOS by creating a mapping between
 * task names, their respective task handles, and individual counters to keep track of each task's
 * runtime. This mapping is necessary because FreeRTOS does not provide built-in support for
 * detailed execution time tracking of individual tasks.
 *
 * Each entry in the `xTaskMappings` array corresponds to a specific task identified by its name.
 * The task handle allows for programmatic interaction with the task through the FreeRTOS API, and
 * the counter is used to accumulate the total runtime ticks that the task has consumed. This allows
 * for calculating the percentage of CPU time used by each task during the system's runtime.
 *
 * By setting up this mapping, we enable the capability to collect and analyze detailed runtime
 * statistics, which are crucial for profiling, system tuning, and ensuring real-time performance
 * guarantees. It is essential for systems where understanding the time behavior of tasks is critical.
 *
 * Note: This initialization function should be called after the scheduler has started, as some task
 * handles, like that of the idle task, are only available after the FreeRTOS scheduler is running.
 */
void FreeRTOS_MappTasksForTaskExecutionTime(void)
{
    // Define an array of task information
    struct TaskInfo {
        TaskHandle_t* xTaskHandle;
        const char* pcTaskName;
        uint32_t* pulTaskCounter;
    };

    // Initialize the array with task data
    struct TaskInfo taskInfos[] = {
        {&xTaskHandle_1ms, "1ms Task", &TaskCounter_1ms},
        {&xTaskHandle_10ms, "10ms Task", &TaskCounter_10ms},
        {&xTaskHandle_100ms, "100ms Task", &TaskCounter_100ms},
        {&xIsrHandle_AF_MM2S, "AF MM2S ISR Task", &IsrTask_Counter_AF_MM2S},
        {&xIsrHandle_AF_S2MM, "AF S2MM ISR Task", &IsrTask_Counter_AF_S2MM},
    };

    // Use a loop to populate the task mappings
    for (int idx = 0; idx < (sizeof(taskInfos) / sizeof(taskInfos[0])); ++idx) {
        xTaskMappings[idx] = (TaskMapping_t){
            .xTaskHandle = *taskInfos[idx].xTaskHandle,
            .pcTaskName = taskInfos[idx].pcTaskName,
            .pulTaskCounter = taskInfos[idx].pulTaskCounter
        };
    }
}

/*
 * Initializes Timer0 to be used for FreeRTOS run-time statistics.
 * This is configured to tick at 10kHz which is suitable for tracking
 * task execution times. It assumes that the CPU timers have been
 * initialized elsewhere in the main initialization code of the CPU.
 */
#include "xil_io.h"
#include "xil_types.h"

#define GLOBAL_TIMER_BASEADDR      0xF8F00200U
#define GTIMER_CONTROL_OFFSET      0x00U
#define GTIMER_COUNTER_LOWER_OFFSET 0x04U
#define GTIMER_COUNTER_UPPER_OFFSET 0x08U
#define GTIMER_PRESCALER_OFFSET    0x08U

void InitializeGlobalTimer(uint32_t system_clock_freq, uint32_t desired_freq)
{
    uint32_t prescaler;

    // Calculate the prescaler value for 10kHz
    prescaler = (system_clock_freq / desired_freq) - 1;

    // Disable the Global Timer
    Xil_Out32(GLOBAL_TIMER_BASEADDR + GTIMER_CONTROL_OFFSET, 0x0);

    // Set the prescaler value
    Xil_Out32(GLOBAL_TIMER_BASEADDR + GTIMER_PRESCALER_OFFSET, prescaler);

    // Reset the Global Timer Counter Register
    Xil_Out32(GLOBAL_TIMER_BASEADDR + GTIMER_COUNTER_LOWER_OFFSET, 0x0);
    Xil_Out32(GLOBAL_TIMER_BASEADDR + GTIMER_COUNTER_UPPER_OFFSET, 0x0);

    // Enable the Global Timer
    Xil_Out32(GLOBAL_TIMER_BASEADDR + GTIMER_CONTROL_OFFSET, 0x1);
}



/*
 * Retrieves the current run-time counter value for FreeRTOS,
 * which is used to calculate how much CPU time each task has consumed.
 * This function should return a monotonically increasing timer value.
 */
static inline uint32_t FreeRTOS_GetRunTimeCounterValue(void)
{

	uint32_t low, high;

	// Reading Global Timer Counter Register
	high = Xil_In32(GLOBAL_TIMER_BASEADDR + GTIMER_COUNTER_UPPER_OFFSET);
	low = Xil_In32(GLOBAL_TIMER_BASEADDR + GTIMER_COUNTER_LOWER_OFFSET);

	return (((uint64_t)high) << 32) | (uint64_t)low;

}

static uint32_t GetAverageTaskExecutionTimeByTaskHandle(TaskHandle_t xTaskHandle, uint32_t ulTotalRunTimeCounter) {
    for (int i = 0; i < sizeof(xTaskMappings) / sizeof(xTaskMappings[0]); ++i) {
        if (xTaskHandle == xTaskMappings[i].xTaskHandle) {
            // Check to ensure we don't divide by zero.
            if (*(xTaskMappings[i].pulTaskCounter) > 0) {
                // Found the task, calculate average execution time.
                // Divide total run time (in ticks) by the number of executions to get average ticks per execution.
                uint32_t averageTicksPerExecution = ulTotalRunTimeCounter / *(xTaskMappings[i].pulTaskCounter);
                // Convert average ticks per execution to microseconds.
                uint32_t averageExecutionTimeMicroseconds = TICKS_TO_MICROSECONDS(averageTicksPerExecution);
                return averageExecutionTimeMicroseconds;
            } else {
                // Task has never executed, return zero as the average execution time.
                return 0;
            }
        }
    }
    // Task not found, return a special value to indicate failure.
    // Choose an unlikely high number that would not be a valid average execution time.
    return UINT32_MAX;
}



/**
 * @brief Retrieves run time statistics for all tasks in the system.
 *
 * @param pxTaskRunTimeStatsArray A pointer to an array of TaskRunTimeStats_t structures
 *                                that the run time stats will be written into.
 * @param uxArraySize The size of the array pointed to by pxTaskRunTimeStatsArray.
 *                    This should be large enough to hold a structure for each task.
 *
 * @note The function will populate each TaskRunTimeStats_t structure with the
 *       task name, run time counter, and run time percentage of the total time.
 *
 * @return pdPASS if the stats were successfully retrieved and the array was filled,
 *         otherwise pdFAIL.
 */
BaseType_t xTaskGetRunTimeStatsRaw(TaskRunTimeStats_t *pxTaskRunTimeStatsArray, const UBaseType_t uxArraySize) {
    TaskStatus_t *pxTaskStatusArray;
    uint32_t ulTotalTime;
    UBaseType_t uxArraySizeSnapshot, x;

    // Take a snapshot of the number of tasks in case it changes while this function is executing.
    uxArraySizeSnapshot = uxTaskGetNumberOfTasks();

    // Allocate a temporary array to hold the status information about each task.
    pxTaskStatusArray = pvPortMalloc(uxArraySizeSnapshot * sizeof(TaskStatus_t));

    if (pxTaskStatusArray == NULL) {
        // Could not get the memory needed for the task status array.
        return pdFAIL;
    }

    // Get the actual system state.
    uxArraySizeSnapshot = uxTaskGetSystemState(pxTaskStatusArray, uxArraySizeSnapshot, &ulTotalTime);

    // Avoid division by zero and check if we got the task status array correctly.
    if ((ulTotalTime > 0UL) && (uxArraySizeSnapshot > 0)) {

        for (x = 0; x < uxArraySizeSnapshot; x++)
        {
          if (x < uxArraySize)
          {
              // Calculate percentage using floating-point arithmetic to avoid integer division issues.
              float fStatsAsPercentage = ((float)pxTaskStatusArray[x].ulRunTimeCounter / (float)ulTotalTime) * 100.0f;

              // Get the execution time in microseconds from the mappings using the helper function.
              //float ulExecutionTime = GetTaskExecutionTimeByTaskName(pxTaskStatusArray[x].pcTaskName);
              uint32_t ulAverageExecutionTime = GetAverageTaskExecutionTimeByTaskHandle(pxTaskStatusArray[x].xHandle, pxTaskStatusArray[x].ulRunTimeCounter);

              // Copy the task name, run time, calculated percentage, and execution time into the user-provided array.
              pxTaskRunTimeStatsArray[x].pcTaskName = pxTaskStatusArray[x].pcTaskName;
              pxTaskRunTimeStatsArray[x].ulRunTimeCounter = pxTaskStatusArray[x].ulRunTimeCounter;
              pxTaskRunTimeStatsArray[x].fRunTimePercentage = fStatsAsPercentage;
              // Adding execution time in microseconds to the array.
              pxTaskRunTimeStatsArray[x].ulExecutionTimeMicroseconds = ulAverageExecutionTime;
          }
          else
          {
              // ... (error handling)
          }
        }
    } else {
        // Total run time was 0 or obtaining task status failed, clean up and return fail.
        vPortFree(pxTaskStatusArray);
        return pdFAIL;
    }

    // Clean up.
    vPortFree(pxTaskStatusArray);
    return pdPASS;
}


/*
 * Collects and prints the FreeRTOS task run-time statistics.
 * This function will disable interrupts while collecting the statistics.
 * It should be used cautiously, as it will impact real-time performance.
 */
void FreeRTOS_GetRunTimeStats(void)
{
    static BaseType_t xMappingDone = pdFALSE;
    static BaseType_t callCount = 0;

    // Only map tasks once
    if (xMappingDone == pdFALSE) {
        FreeRTOS_MappTasksForTaskExecutionTime();
        xMappingDone = pdTRUE;
    }

    callCount++;
    if (callCount >= 10) {
        // Reset counter
        callCount = 0;

        if (xTaskGetRunTimeStatsRaw(xRunTimeStats, configSTATS_MAXNUMBER_OF_TASKS) == pdPASS) {
            // The xRunTimeStats array now contains the run time info for each task.
            // Since the inner loop is removed, the processing of stats will need
            // to be done elsewhere, after every 10th call to this function.
        } else {
            // Handle error
        }
    }

    // You may want to do some other periodic processing here, or simply return.
}

