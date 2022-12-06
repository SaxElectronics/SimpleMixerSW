/*
 * FIR.h
 *
 *  Created on: Sep 14, 2022
 *      Author: stank
 */

#ifndef LIBRARIES_AUDIOEFFECTS_FILTERS_FILTERS_H_
#define LIBRARIES_AUDIOEFFECTS_FILTERS_FILTERS_H_

/****************************/
/*        DEFINES           */
/****************************/
#define FILTER_TAP_NUM 17

/****************************/
/*        TYPEDEFS          */
/****************************/


typedef struct FIR_parameters_t
{
    float filter_taps[FILTER_TAP_NUM];
} FIR_parameters_t;

typedef struct FIR_data_t
{
    float inSampleF;
    float outSampleF;
    float firdata [FILTER_TAP_NUM];
    int firptr [FILTER_TAP_NUM];
    int fir_w_ptr;
} FIR_data_t;

typedef struct filterFIR_t
{
    FIR_data_t Data;
    FIR_parameters_t Parameters;
} filterFIR_t;

typedef struct IIR_data_t
{
       float in_z1; float in_z2;
       float out_z1; float out_z2;
       float inSampleF; float outSampleF;
} IIR_data_t;

typedef struct IIR_parameters_t
{
        float a0; float a1; float a2; float b1; float b2;
} IIR_parameters_t;

typedef struct filterIIR_t
{
        IIR_data_t Data;
        IIR_parameters_t Parameters;
} filterIIR_t;

/****************************/
/*        External Variables          */
/****************************/

extern IIR_data_t IIR_DataLeft;
extern IIR_data_t IIR_DataRight;
extern IIR_parameters_t IIR_ParametersLeft;
extern IIR_parameters_t IIR_ParametersRight;


extern int Calc_FIR (int inSample);

extern int Calc_IIR (int inSample, IIR_parameters_t* IIR_ParamsPtr, IIR_data_t* IIR_DataPtr);

#endif /* LIBRARIES_AUDIOEFFECTS_FILTERS_FILTERS_H_ */
