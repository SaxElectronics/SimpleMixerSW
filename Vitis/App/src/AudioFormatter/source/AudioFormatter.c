
/*
 * AudioFormatter.c: Provide functions to initialize and operate the audio formatter
 *
 * This file contains functions to initialize the audio formatter, to configure/reconfigure
 * and operate it properly.
 *
 */

/*
 * includes
 */

#include "AudioFormatter.h"


// Initialize the audio formatter
void AudioFormatter_Init(void)
{
	Xil_Out32 ( (XPAR_XAUDIOFORMATTER_0_BASEADDR + 0x10), 1 ); // run the audio formatter
	//u32 AudioFormatterRunStop = Xil_In32(XPAR_XAUDIOFORMATTER_0_BASEADDR + 0x10); // check if audio formatter is ran
}
