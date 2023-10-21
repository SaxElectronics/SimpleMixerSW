/*
 * Tasks_Init.h
 */
#ifndef TASK_100MS_H
#define TASK_100MS_H
/*
 * includes
 */
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
/*
 * own FreeRTOS includes
 */
#include "Tasks_Init.h"

/*
 * defines
 */
#define STACK_SIZE_TASK_100MS  256U


/*
 * declarations
 */

extern StaticTask_t TaskBuffer_100ms;
extern StackType_t  TaskStack_100ms[STACK_SIZE_TASK_100MS];


extern void Task_100ms(void * pvParameters);

#endif//TASK_100MS_H
