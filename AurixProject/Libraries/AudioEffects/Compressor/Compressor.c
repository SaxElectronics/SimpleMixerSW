/*
 * Compressor.c
 *
 *  Created on: Sep 13, 2022
 *      Author: stanko
 */

#include "math.h"
// 0 = no gain reduction
// 1 = attack
// 2 = gain reduction
// 3 = release
enum CompStates {S_NoOperation, S_Attack, S_GainReduction, S_Release };
enum CompStates State = S_NoOperation;

typedef struct {
    int AttackTime, ReleaseTime, HoldTime;
    float GainReduction, MakeUpGain, Threshold;
} CompressorUserSettings_t;

CompressorUserSettings_t CompressorParameters;

int TimeOut;
float  gain_step_attack, gain_step_release, gain_actual;

void DoCompressor_Init(void)
{
    // 1 sample = 1/96kHz = ~10us
    //AttackTime -> 30 ms -> 3000
    //Release -> 20 ms -> 2000
    //HoldTime -> 10ms -> 1000
    CompressorParameters.AttackTime = 3000;
    CompressorParameters.ReleaseTime = 2000;
    CompressorParameters.HoldTime = 1000;

    //Threshold -20dB below limit -> 0.1 * 2^31
    CompressorParameters.Threshold = 0.1f * 2147483648;

    //compression ratio: 6:1 -> -6dB = 0.5
    CompressorParameters.GainReduction = 0.5f;

    gain_step_attack = (1.0f - CompressorParameters.GainReduction) / CompressorParameters.AttackTime;
    gain_step_release = (1.0f - CompressorParameters.GainReduction) / CompressorParameters.ReleaseTime;

    //initial gain_actual = 1.0 -> no compression
    gain_actual = 1.0f;
}


int DoCompressor (int inSample)
{
    float inSampleF = (float)inSample;
    float SampleFabs = fabs(inSampleF);
    if (SampleFabs > CompressorParameters.Threshold) {
        if (gain_actual >=  CompressorParameters.GainReduction)
        {
            if (State==S_NoOperation) {
                State=S_Attack;
                TimeOut = CompressorParameters.AttackTime;
            }
            else if (State==S_Release) {
                State=S_Attack;
                TimeOut = CompressorParameters.AttackTime;
            }
        }
        if (State==S_GainReduction)
        {
            TimeOut = CompressorParameters.HoldTime;
        }
    }

    if (SampleFabs < CompressorParameters.Threshold && gain_actual <= 1.0f)
    {
        if (TimeOut==0 && State==S_GainReduction)
        {
            State=S_Release;
            TimeOut = CompressorParameters.ReleaseTime;
        }
    }
    switch (State) {

        case S_Attack:
            if (TimeOut>0 && gain_actual > CompressorParameters.GainReduction) {
                gain_actual -= gain_step_attack;
                TimeOut--;
            }
            else {
                State=S_GainReduction;
                TimeOut = CompressorParameters.HoldTime;
            }
            break;


        case S_GainReduction:
            if (TimeOut>0) TimeOut--;
            else {
                State=S_Release;
                TimeOut = CompressorParameters.ReleaseTime;
            }
            break;


        case S_Release:
            if (TimeOut>0 && gain_actual<1.0f) {
                TimeOut--;
                gain_actual += gain_step_release;
            }
            else {
                State=S_NoOperation;
            }
            break;

        case S_NoOperation:
            if (gain_actual < 1.0f) gain_actual = 1.0F;
            break;

        default:

            break;

    }


    float outSampleF = inSample*gain_actual;

    return (int) outSampleF;
}
