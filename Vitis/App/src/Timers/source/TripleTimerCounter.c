#include "xttcps.h"
#include "xil_assert.h"

#include "ttc_init.h"

XTtcPs Ttc0PsInstance; // The instance of the TTC
int InitializeTTC(u16 DeviceId, u32 TickRateHz);

/*
 * Triple Timer Counter (TTC) on Zynq SoC and ISR Explanation
 * ----------------------------------------------------------
 *
 * The Zynq SoC integrates a Triple Timer Counter (TTC) module that provides three independent timer/counter devices.
 * Each counter can be used for a wide range of timing and counting applications requiring high resolution and
 * flexibility in configuration.
 *
 * The TTC module can be clocked by an external clock source or by the system clock, with a configurable prescaler
 * to adjust the input clock frequency. The counters within the TTC can be set to operate in different modes:
 *
 * - Interval Mode: The counter generates an interrupt at regular intervals based on the value set in the interval
 *   register. After reaching the interval, the counter resets to zero (or the reset value) and starts counting again.
 * - Match Mode: The counter generates an interrupt when the counter value matches a predefined value set in the match
 *   register.
 * - Overflow Mode: The counter runs continuously from zero to its maximum value and generates an interrupt when it
 *   overflows, starting again from zero.
 *
 * In our application, we are using the Interval Mode to generate periodic interrupts at a frequency of 1 MHz. The
 * interrupt service routine (ISR), `Ttc0InterruptHandler`, is called every time the TTC counter reaches the interval value.
 *
 * Inside the ISR, we first clear the interrupt status to acknowledge the interrupt and prevent the ISR from being
 * immediately called again. Then we increment a 32-bit variable, `ttc_elapsedTime`, which tracks the number of times
 * the interrupt has occurred. This effectively creates a software counter with a higher range than the hardware TTC
 * counter itself.
 *
 * To set up the TTC interrupt, the `SetupTtcPsInterrupt` function configures the Global Interrupt Controller (GIC) to
 * recognize and handle the TTC interrupt. It registers the `Ttc0InterruptHandler` as the callback function to be called upon
 * the interrupt firing. The interrupt is then enabled in the GIC and in the processor, allowing the system to respond
 * to the TTC interrupt.
 *
 * When integrating the TTC into an application, it is important to configure it correctly according to the specific
 * timing requirements. The initialization of the TTC, the setup of the interrupt system, and the synchronization with
 * other system components are critical steps for reliable operation.
 *
 * Usage Example:
 * --------------
 * In the main function or system initialization code, call `InitializeInterruptSystem()` to set up the interrupt system.
 * This prepares the TTC to generate interrupts at the desired rate, and sets up the ISR to handle these interrupts.
 */


void FreeRTOS_CounterInit_TTC(void)
{
	InitializeTTC(TTC_DEVICE_ID, TTC_TICK_RATE_HZ);

}

int InitializeTTC(u16 DeviceId, u32 TickRateHz)
{
    XTtcPs_Config *Config;
    int Status;
    u32 Options;
    XInterval Interval;
    u8 Prescaler;

    // Look up the configuration based on the device ID
    Config = XTtcPs_LookupConfig(DeviceId);
    if (NULL == Config) {
        return XST_FAILURE;
    }

    // Initialize the device
    Status = XTtcPs_CfgInitialize(&Ttc0PsInstance, Config, Config->BaseAddress);
    if (Status != XST_SUCCESS) {
        return Status;
    }

    // Disable the TTC
    XTtcPs_Stop(&Ttc0PsInstance);

    // Calculate the interval and prescaler for the desired frequency
    XTtcPs_CalcIntervalFromFreq(&Ttc0PsInstance, TickRateHz, &Interval, &Prescaler);

    // Check if calculation was successful
    if (Interval == XTTCPS_MAX_INTERVAL_COUNT && Prescaler == 0xFFU) {
        xil_printf("TTC Timer initialization failed: Interval and Prescaler calculation error\n");
        return XST_FAILURE; // Calculation failed
    }

    // Set the options for the timer
    Options = XTTCPS_OPTION_WAVE_DISABLE;

#ifdef USE_INTERVAL_MODE
    // Enable interval interrupts if USE_INTERVAL_MODE is defined
    Options |= XTTCPS_OPTION_INTERVAL_MODE;
    XTtcPs_SetOptions(&Ttc0PsInstance, Options);
    // Set the interval and prescaler
	XTtcPs_SetInterval(&Ttc0PsInstance, Interval);
    XTtcPs_EnableInterrupts(&Ttc0PsInstance, XTTCPS_IXR_INTERVAL_MASK);
#else
    // Otherwise, set up for overflow interrupt only
    XTtcPs_SetOptions(&Ttc0PsInstance, Options);
    XTtcPs_EnableInterrupts(&Ttc0PsInstance, XTTCPS_IXR_CNT_OVR_MASK);
    XTtcPs_SetPrescaler(&Ttc0PsInstance, 0x06);
#endif


    // Register the TickHandler as the callback function for TTC interrupts
    XTtcPs_SetStatusHandler(&Ttc0PsInstance, &Ttc0PsInstance,
                            (XTtcPs_StatusHandler) Ttc0InterruptHandler);

    // Start the timer
    XTtcPs_Start(&Ttc0PsInstance);

    return XST_SUCCESS;
}


static uint32_t ttc_elapsedTimeCounter;
static uint16_t ttc_OverflowCounter;
static uint16_t ttc_CounterValueReg;
static uint16_t ttc_InterruptCounter;

XTtcPs Ttc0PsInstance; // Assuming this is your TTC instance

/*
 * return ttc_elapsedTime, which is increased each TTC_TICK_RATE_HZ (1Mhz) in a dedicated isr
 */

uint32_t GetMonotonicTtcTime(void)
{
	ttc_CounterValueReg = XTtcPs_GetCounterValue(&Ttc0PsInstance);

	ttc_elapsedTimeCounter = ( ((uint32_t) ttc_OverflowCounter ) << 16) | ttc_CounterValueReg;

    return ttc_elapsedTimeCounter;
}



// The ISR for the TTC timer interrupt
void Ttc0InterruptHandler(void *CallBackRef)
{
    XTtcPs *TtcPtr = (XTtcPs *)CallBackRef;

    u32 StatusEvent = XTtcPs_GetInterruptStatus(TtcPtr);
    ttc_InterruptCounter++;
	ttc_OverflowCounter++;

#ifdef USE_INTERVAL_MODE
    if (StatusEvent & XTTCPS_IXR_INTERVAL_MASK)
    {
        // Handle the interval event
        // Your code to handle interval interrupts
    	ttc_elapsedTime++;
    }
#else
    if (StatusEvent & XTTCPS_IXR_CNT_OVR_MASK)
    {
        // Handle the overflow event
        // Your code to handle overflow interrupts
    	ttc_OverflowCounter++;
    }
#endif

    // Clear the interrupt status
    XTtcPs_ClearInterruptStatus(TtcPtr, StatusEvent);
}

