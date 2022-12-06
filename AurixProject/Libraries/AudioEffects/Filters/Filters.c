/*
 * FIR.c
 *
 *  Created on: Sep 14, 2022
 *      Author: stank
 */

#include <AudioEffects/Filters/Filters.h>



struct IIR_parameters_t IIR_ParametersLeft =
        {
            .a0 = 0.9543457485325094f,
            .a1 = -1.9086914970650188f,
            .a2 = 0.9543457485325094f,
            .b1 = -1.9066459797557103f,
            .b2 = 0.9107370143743273f
        };

struct IIR_parameters_t IIR_ParametersRight =
        {
            .a0 = 0.0010227586546542474f,
            .a1 = 0.002045517309308495f,
            .a2 = 0.0010227586546542474f,
            .b1 = -1.9066459797557103f,
            .b2 = 0.9107370143743273f
        };

struct IIR_data_t IIR_DataLeft =
        {

           .in_z1 = 0,
           .in_z2 = 0,
           .out_z1 = 0,
           .out_z2 = 0,
           .inSampleF = 0,
           .outSampleF = 0
        };


struct IIR_data_t IIR_DataRight=
        {

           .in_z1 = 0,
           .in_z2 = 0,
           .out_z1 = 0,
           .out_z2 = 0,
           .inSampleF = 0,
           .outSampleF = 0
        };

static FIR_data_t FIR_data;
struct FIR_parameters_t FIR_Parameters =
{
        {
          -0.0021834891907904987,
          0.023133081888390004,
          0.03440125360693663,
          0.054016706019288735,
          0.07610902012650608,
          0.09772535709704201,
          0.11593264129629442,
          0.12810228628568973,
          0.13238343618749146,
          0.12810228628568973,
          0.11593264129629442,
          0.09772535709704201,
          0.07610902012650608,
          0.054016706019288735,
          0.03440125360693663,
          0.023133081888390004,
          -0.0021834891907904987
        },
};

int Calc_FIR (int inSample) 
{
    FIR_data.inSampleF = (float)inSample;
    FIR_data.outSampleF = 0;

    for (int i=0;i < FILTER_TAP_NUM; i++)
    {
        FIR_data.outSampleF += (FIR_data.firdata[i]*FIR_Parameters.filter_taps[FIR_data.firptr[i]]);
        FIR_data.firptr[i]++;
    }

    FIR_data.firdata[FIR_data.fir_w_ptr] = FIR_data.inSampleF;
    FIR_data.firptr[FIR_data.fir_w_ptr] = 0;
    FIR_data.fir_w_ptr++;
    if (FIR_data.fir_w_ptr == FILTER_TAP_NUM) FIR_data.fir_w_ptr=0;

    return (int) FIR_data.outSampleF;
}


int Calc_IIR (int inSample, IIR_parameters_t* IIR_ParamsPtr, IIR_data_t* IIR_DataPtr) {
    IIR_DataPtr->inSampleF = (float)inSample;
    IIR_DataPtr->outSampleF =
            IIR_ParamsPtr->a0 * IIR_DataPtr->inSampleF
            + IIR_ParamsPtr->a1 * IIR_DataPtr->in_z1
            + IIR_ParamsPtr->a2 * IIR_DataPtr->in_z2
            - IIR_ParamsPtr->b1 * IIR_DataPtr->out_z1
            - IIR_ParamsPtr->b2 * IIR_DataPtr->out_z2;
    IIR_DataPtr->in_z2 = IIR_DataPtr->in_z1;
    IIR_DataPtr->in_z1 = IIR_DataPtr->inSampleF;
    IIR_DataPtr->out_z2 = IIR_DataPtr->out_z1;
    IIR_DataPtr->out_z1 = IIR_DataPtr->outSampleF;

    return (int) IIR_DataPtr->outSampleF;
}



