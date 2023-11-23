/*
 * Initializes Timer0 to be used for FreeRTOS run-time statistics.
 * This is configured to tick at 10kHz which is suitable for tracking
 * task execution times. It assumes that the CPU timers have been
 * initialized elsewhere in the main initialization code of the CPU.
 */
#include "xil_io.h"
#include "xil_types.h"

#include "global_timer.h"

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

inline int GlobalTimer_ReadValue(void)
{
	uint32_t low, high;

	// Reading Global Timer Counter Register
	high = Xil_In32(GLOBAL_TIMER_BASEADDR + GTIMER_COUNTER_UPPER_OFFSET);
	low = Xil_In32(GLOBAL_TIMER_BASEADDR + GTIMER_COUNTER_LOWER_OFFSET);

	return (((uint64_t)high) << 32) | (uint64_t)low;


}
