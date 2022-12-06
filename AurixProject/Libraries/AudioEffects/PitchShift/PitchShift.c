/*
 * PitchShift.c
 *
 *  Created on: Sep 15, 2022
 *      Author: stank
 */


/*************************
      includes
**************************/
#include "math.h"
#include "Filters.h"
#include "PitchShift.h"

/*************************
      defines
**************************/
#define Overlap 100



float Shift;
float CrossFade;


PitchShift_parameters_t PitchShiftParameters =
{
     .Shift = 1.4f,
     .CrossFade = 1.0f
};

PitchShift_ringbuffer_t PitchShiftRingBuffer =
{
        .Rd_P = 0.0f,
        .WtrP = 0,
        .Buf = {0}
};

IIR_parameters_t IIR_HighPassParameters =
        {
            .a0 = 0.9862117951198142f,
            .a1 = -1.9724235902396283f,
            .a2 = 0.9862117951198142f,
            .b1 = -1.972233470205696f,
            .b2 = 0.9726137102735608f
        };

IIR_data_t IIR_HighPassData =
        {
           .in_z1 = 0,
           .in_z2 = 0,
           .out_z1 = 0,
           .out_z2 = 0,
           .inSampleF = 0,
           .outSampleF = 0
        };


int Do_PitchShift(int lSample, int rSample)
{
    int sum = lSample + rSample;
    //sum up and do high-pass
    sum = Calc_IIR(sum, &IIR_HighPassParameters, &IIR_HighPassData);

    //write to ringbuffer
    PitchShiftRingBuffer.Buf[PitchShiftRingBuffer.WtrP] = sum;

    //read fractional readpointer and generate 0� and 180� read-pointer in integer
    int RdPtr_Int = roundf(PitchShiftRingBuffer.Rd_P);
    int RdPtr_Int2 = 0;
    if (RdPtr_Int >= BufSize/2) RdPtr_Int2 = RdPtr_Int - (BufSize/2);
    else RdPtr_Int2 = RdPtr_Int + (BufSize/2);

    //read the two samples...
    float Rd0 = (float) PitchShiftRingBuffer.Buf[RdPtr_Int];
    float Rd1 = (float) PitchShiftRingBuffer.Buf[RdPtr_Int2];

    //Check if first readpointer starts overlap with write pointer?
    // if yes -> do cross-fade to second read-pointer
    if (Overlap >= (PitchShiftRingBuffer.WtrP-RdPtr_Int) && (PitchShiftRingBuffer.WtrP-RdPtr_Int) >= 0 && PitchShiftParameters.Shift!=1.0f) {
        int rel = PitchShiftRingBuffer.WtrP - RdPtr_Int;
        PitchShiftParameters.CrossFade = ((float)rel)/(float)Overlap;
    }
    else if (PitchShiftRingBuffer.WtrP-RdPtr_Int == 0) PitchShiftParameters.CrossFade = 0.0f;

    //Check if second readpointer starts overlap with write pointer?
    // if yes -> do cross-fade to first read-pointer
    if (Overlap >= (PitchShiftRingBuffer.WtrP-RdPtr_Int2) && (PitchShiftRingBuffer.WtrP-RdPtr_Int2) >= 0 && PitchShiftParameters.Shift!=1.0f) {
            int rel = PitchShiftRingBuffer.WtrP-RdPtr_Int2;
            PitchShiftParameters.CrossFade = 1.0f - ((float)rel)/(float)Overlap;
        }
    else if (PitchShiftRingBuffer.WtrP-RdPtr_Int2 == 0) PitchShiftParameters.CrossFade = 1.0f;


    //do cross-fading and sum up
    sum = (Rd0*PitchShiftParameters.CrossFade + Rd1 * (1.0f - PitchShiftParameters.CrossFade));

    //increment fractional read-pointer and write-pointer
    PitchShiftRingBuffer.Rd_P += PitchShiftParameters.Shift;
    PitchShiftRingBuffer.WtrP++;
    if (PitchShiftRingBuffer.WtrP == BufSize) PitchShiftRingBuffer.WtrP = 0;
    if (roundf(PitchShiftRingBuffer.Rd_P) >= BufSize) PitchShiftRingBuffer.Rd_P = 0.0f;

    return sum;

}
