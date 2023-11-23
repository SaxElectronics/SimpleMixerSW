#ifndef GLOBAL_TIMER_H_
#define GLOBAL_TIMER_H_

#define GLOBAL_TIMER_BASEADDR      0xF8F00200U
#define GTIMER_CONTROL_OFFSET      0x00U
#define GTIMER_COUNTER_LOWER_OFFSET 0x04U
#define GTIMER_COUNTER_UPPER_OFFSET 0x08U
#define GTIMER_PRESCALER_OFFSET    0x08U

/*
 * Function prototypes
 */

extern int GlobalTimer_ReadValue(void);

extern void InitializeGlobalTimer(uint32_t system_clock_freq, uint32_t desired_freq);


#endif
