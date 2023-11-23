
#ifndef TASKS_INIT_H
#define TASKS_INIT_H


/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


#define mainERROR_CHECK_TASK_PERIOD         ( 200UL / portTICK_PERIOD_MS )


extern uint32_t ulIdleTaskCounter;

extern void FreeRTOS_StartScheduler(void);

extern void FreeRTOS_CreateTasks_Init(void);

/* Cyclic Task 1ms */
extern uint32_t TaskCounter_1ms;
extern void Task_1ms(void * pvParameters);

/* Cyclic Task 10ms */
extern uint32_t TaskCounter_10ms;
extern void Task_10ms(void * pvParameters);

/* Cyclic Task 100ms */
extern uint32_t TaskCounter_100ms;
extern void Task_100ms(void * pvParameters);

/* check task */
extern bool xTaskError;
extern void prvCheckTask( void *pvParameters );

/*
 * task handles
 */
extern TaskHandle_t xCheckTaskHandle;
extern TaskHandle_t xTxTaskHandle;
extern TaskHandle_t xRxTaskHandle;

/*
 * Idle task counter
 */
extern uint32_t ulIdleTaskCounter;
extern uint32_t ulRxTaskCounter;
extern uint32_t ulTxTaskCounter;
extern uint32_t IsrTask_Counter_Check;

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* CO_ROUTINE_H */


