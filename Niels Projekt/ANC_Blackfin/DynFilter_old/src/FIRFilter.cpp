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

FIRFilter::FIRFilter(uint8_t filterTaps)
{
	setFilterTaps(FILTER_TAPS_);

	// Clear coefficients and delay lines
	for (short i = 0; i < MAX_TAPS; i++) {

		w[i] = 0;

		// Sikre at x ikke bliver overskrevet ved MAX_TAPS
		if (i < MAX_TAPS-1)	{
			x[i] = 0;
		}
	}

}

void FIRFilter::updateWeights(fract* weights){
	for(int i = 0; i < FILTER_TAPS_; i++){
		x[i] = weights[i];
	}
}

void FIRFilter::process(short* input, short* output, short len)
{
	fract *x = (fract *)input;
	fract *y = (fract *)output;

	for(int n = 0; n < len; n++){

		for(int m = FILTER_TAPS_ - 1;  m > 0; m--)	{
			delayLine[m] = delayLine[m-1];
		}

		// Delayline
		delayLine[n] = x[n];

		// Convolution
		for(int m = 0; m < FILTER_TAPS_; m++){
			y[n] += w[m] * delayLine[m];
		}
	}




	// Performs 2. order IIR filtering using Native fractional types
	/*
	fract *x = (fract *)input;
	fract *y = (fract *)output;
	accum ylf;
	for (short i = 0; i < len; i++) {
		ylf = bq.b[0]*x[i] + bq.b[1]*bq.x[0] + bq.b[2]*bq.x[1] - bq.a[1]*bq.y[0] - bq.a[2]*bq.y[1];
	    bq.y[1] = bq.y[0];
	    bq.y[0] = ylf/bq.a[0];
	    y[i] = (fract)bq.y[0];
	    bq.x[1] = bq.x[0];
	    bq.x[0] = x[i];
	}
	*/
}

void FIRFilter::create(void)
{
	/*
	// Initialization of coefficients
	for (short i = 0; i < NUM_IIR_COEFFS; i++) {
		bq.a[i] = 0;
		bq.b[i] = 0;
	}
	bq.a[0] = FRACT_MAX;
	bq.b[0] = FRACT_MAX;
	*/
}
