/*
 * Tasks_Statistics.h
 *
 *  Created on: Nov 4, 2023
 *      Author: stank
 */

#ifndef TASKS_INCLUDE_TASKS_STATISTICS_H_
#define TASKS_INCLUDE_TASKS_STATISTICS_H_

/*
 * Define the structure that will hold task run time information
 * including the percentage of total run time.
 */
typedef struct {
    const char *pcTaskName;        // Task name
    uint32_t ulRunTimeCounter;     // Run time since system started
    float fRunTimePercentage;      // Percentage of total run time
    uint32_t ulExecutionTimeMicroseconds; // Updated member to store execution time in microseconds.
} TaskRunTimeStats_t;


typedef struct {
    TaskHandle_t xTaskHandle;  // Task handle
    const char* pcTaskName;    // Task name
    uint32_t* pulTaskCounter;  // Pointer to the task counter variable
} TaskMapping_t;


extern void FreeRTOS_GetRunTimeStats(void);

extern void FreeRTOS_MappTasksForTaskExecutionTime(void);

#endif /* TASKS_INCLUDE_TASKS_STATISTICS_H_ */
