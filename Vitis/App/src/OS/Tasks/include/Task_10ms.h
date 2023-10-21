/*
 * Tasks_Init.h
 */
#ifndef TASK_10MS_H
#define TASK_10MS_H
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
#define STACK_SIZE_TASK_10MS  256U


/*
 * declarations
 */
extern StaticTask_t TaskBuffer_10ms;
extern StackType_t  TaskStack_10ms[STACK_SIZE_TASK_10MS];

/*
 * function prototypes
 */

extern void Task_10ms(void * pvParameters);

#endif//TASK_10MS_H
