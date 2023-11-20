/*
 * Task_1ms.h
 */
#ifndef TASK_1MS_H
#define TASK_1MS_H
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
 * declarations
 */
#define STACK_SIZE_TASK_1MS  256U



extern StaticTask_t TaskBuffer_1ms;
extern StackType_t  TaskStack_1ms[STACK_SIZE_TASK_1MS];
extern uint32_t TaskCounter_1ms;
extern TaskHandle_t xTaskHandle_1ms;

extern void Task_1ms(void * pvParameters);

#endif//TASK_1MS_H
