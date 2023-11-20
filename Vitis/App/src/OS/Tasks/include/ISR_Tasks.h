/*
 * ISR_Tasks.h
 *
 *  Created on: Nov 3, 2023
 *      Author: stank
 */

#ifndef TASKS_INCLUDE_ISR_TASKS_H_
#define TASKS_INCLUDE_ISR_TASKS_H_

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

typedef struct {
    uint32_t *rxBufferPtr;  // Pointer to the RX audio buffer
    uint32_t *txBufferPtr;  // Pointer to the TX audio buffer
    size_t bufferSize;      // Size of the buffer or data chunk (in uint32_t units)
} AudioData_t;

/* Semaphores for each ISR task */
extern SemaphoreHandle_t xCanSemaphore;
extern SemaphoreHandle_t xClaSemaphore;
extern SemaphoreHandle_t xI2cSemaphore;
/* Task handles */
extern TaskHandle_t xIsrHandle_AF_MM2S;
extern TaskHandle_t xIsrHandle_AF_S2MM;
extern TaskHandle_t xIsrHandle_AF_I2C;


/* ISR Tasks Counters */
extern uint32_t IsrTask_Counter_I2C;
extern uint32_t IsrTask_Counter_AF_MM2S;
extern uint32_t IsrTask_Counter_AF_S2MM;


/* Input Queue */
extern QueueHandle_t audioDataQueueInput;
/* Output Queue */
extern QueueHandle_t audioDataQueueOutput;

/*
 * function declarations
 */
extern void Create_ISR_Tasks_Init(void);

#endif /* TASKS_INCLUDE_ISR_TASKS_H_ */
