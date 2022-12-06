/*
 * Reverb.h
 *
 *  Created on: Sep 15, 2022
 *      Author: stank
 */

#ifndef LIBRARIES_AUDIOEFFECTS_REVERB_REVERB_H_
#define LIBRARIES_AUDIOEFFECTS_REVERB_REVERB_H_

extern float Do_Comb0(float inSample);
extern float Do_Comb1(float inSample);
extern float Do_Comb2(float inSample);
extern float Do_Comb3(float inSample);
extern float Do_Allpass0(float inSample);
extern float Do_Allpass1(float inSample);
extern float Do_Allpass2(float inSample);
extern float Do_Reverb(float inSample);

#endif /* LIBRARIES_AUDIOEFFECTS_REVERB_REVERB_H_ */
