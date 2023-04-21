 /*
 * FIRFilter.cpp
 *
 *  Created on: 28. feb. 2018
 *      Author: Kim Bjerge
 */
#include "FIRFilter.h"

#include <cmath>
#include <stdio.h>

#define NORMAL_BUFFER 0
//#define CIRCULAR_BUFFER 1

const float PI_FLOAT  = 3.1415926535897932;


FIRFilter::FIRFilter()
{
	//cir_ptr = delayLine;
}

void FIRFilter::updateWeights(long fract* weights){
	for(int i = 0; i < filter_taps_; i++){
		w[i] = weights[i];
	}
}


long fract * FIRFilter::getDelayLine(void ){

	return delayLine;
}

void FIRFilter::process(short* , short* , short* , short len)
{}

//#if NORMAL_BUFFER

void FIRFilter::filterProcess(short* input, short* output, short len)
{
	fract *x = (fract *)input;
	fract *y = (fract *)output;
	float yTmp = 0;
	float yTmp_ = 0;
	//long fract y_ = 0;

	for(int n = 0; n < len; n++){

		for(int m = filter_taps_ - 1;  m > 0; m--)	{
			delayLine[m] = delayLine[m-1];
			//printf("%d \n",(m-1));
		}
		// Delayline
		delayLine[0] = x[n];

		// Convolution
		yTmp = 0lr;

		for(int m = 0; m < filter_taps_; m++){
			yTmp += (w[m] * delayLine[m]);
		}
		y[n] = (fract)yTmp;
		/*
		if (y[n] != yTmp)
		{
			printf("Overflow i y[n] \n");
		}
		*/

		//y[n] = (y_ >> 15);
	}
	/*
	for(int m = filter_taps_ - 1;  m > 0; m--)	{
		delayLine[m] = delayLine[m-1];
	}
	// Delayline
	delayLine[0] = x[0];

	// Convolution
	y[0] = 0;

	for(int m = 0; m < filter_taps_; m++){
		y[0] += (w[m] * delayLine[m]);
	}
*/
}

/*
//#elif CIRCULAR_BUFFER

void FIRFilter::filterProcess(short* input, short* output, short len)
{
	fract *x = (fract*)input;
	fract *y = (fract*)output;
	accum y_ = 0; //9.31

	int n = 0; int m = 0;
	fract * delay; //1.15

	for(n = 0; n < len; n++){

		*cir_ptr = x[n];

		cir_ptr = (fract *)circptr(cir_ptr, sizeof(fract), delayLine, sizeof(fract)*filter_taps_);
		delay = (fract *)cir_ptr;

		y[n] = 0;

		for(m = 0; m < filter_taps_; m++){
			y[n] += w[m] * (*delay); * 0.3r;
			delay = (fract *)circptr(delay, sizeof(fract), delayLine, sizeof(fract)*filter_taps_);
		}

		//y[n]
	}
}
*/
//#endif

void FIRFilter::create(uint8_t filterTaps){
	// Clear coefficients and delay lines
	for (short i = 0; i < MAX_TAPS; i++) {
		w[i] = 0;
	}

	setFilterTaps(filterTaps);

	for (short i = 0; i < MAX_TAPS; i++) {

		delayLine[i] = 0;
	}
}


void FIRFilter::setFilterTaps(uint8_t numTaps){
	filter_taps_ = numTaps;
}
