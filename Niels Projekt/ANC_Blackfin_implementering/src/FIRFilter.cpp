 /*
 * FIRFilter.cpp
 *
 *  Created on: 28. feb. 2018
 *      Author: Kim Bjerge
 */
#include "FIRFilter.h"

#include <cmath>
#include <stdio.h>

const float PI_FLOAT  = 3.1415926535897932;

FIRFilter::FIRFilter()
{

}

void FIRFilter::updateWeights(fract* weights){
	for(int i = 0; i < filter_taps_; i++){
		w[i] = weights[i];
	}
}


fract * FIRFilter::getDelayLine(void ){

	return delayLine;
}

void FIRFilter::process(short* input, short* errorInput, short* output, short len)
{
	/*
	fract *x = (fract *)input;
	fract *y = (fract *)output;

	for(int n = 0; n < len; n++){

		for(int m = filter_taps_ - 1;  m > 0; m--)	{
			delayLine[m] = delayLine[m-1];
		}

		// Delayline
		delayLine[0] = x[n];

		// Convolution
		for(int m = 0; m < filter_taps_; m++){
			y[n] += w[m] * delayLine[m];
		}
	}
	*/
}

void FIRFilter::filterProcess(short* input, short* output, short len)
{
	fract *x = (fract *)input;
	fract *y = (fract *)output;

	for(int n = 0; n < len; n++){

		for(int m = filter_taps_ - 1;  m > 0; m--)	{
			delayLine[m] = delayLine[m-1];
		}

		// Delayline
		delayLine[0] = x[n];

		// Convolution
		y[n] = 0;
		for(int m = 0; m < filter_taps_; m++){
			y[n] += (w[m] * delayLine[m]*0.3r);
		}

	}

}

void FIRFilter::create(void){

}

void FIRFilter::create(uint8_t filterTaps)
{
	setFilterTaps(filterTaps);

	// Clear coefficients and delay lines
	for (short i = 0; i < MAX_TAPS; i++) {

		w[i] = 0;

		delayLine[i] = 0;
	}}


void FIRFilter::setFilterTaps(uint8_t numTaps){
	filter_taps_ = numTaps;
}
