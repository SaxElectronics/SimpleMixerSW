/*
 * PitchShift.h
 *
 *  Created on: Sep 15, 2022
 *      Author: stank
 */

#ifndef LIBRARIES_AUDIOEFFECTS_PITCHSHIFT_PITCHSHIFT_H_
#define LIBRARIES_AUDIOEFFECTS_PITCHSHIFT_PITCHSHIFT_H_


extern int Do_HighPass (int inSample);
extern int Do_PitchShift(int lSample, int rSample);
extern void Do_PitchShift_Init(void);


typedef struct PitchShift_parameters_t
{
     float Shift;
     float CrossFade;
} PitchShift_parameters_t;

#define BufSize 1000

typedef struct PitchShift_ringbuffer_t
{
     int Buf[BufSize];
     int WtrP;
     float Rd_P;
} PitchShift_ringbuffer_t;

#endif /* LIBRARIES_AUDIOEFFECTS_PITCHSHIFT_PITCHSHIFT_H_ */
