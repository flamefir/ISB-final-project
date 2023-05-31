
#include "FIRFilter.h"
#include <cmath>
#include <stdio.h>

FIRFilter::FIRFilter()
{
#if CIRCULAR_BUFFER
	cir_ptr = delayLine;
#endif
}

FIRFilter::~FIRFilter()
{
}


void FIRFilter::updateWeights(long fract* weights)
{
	for(int i = 0; i < filter_taps_; i++)
	{
		w[i] = weights[i];
	}
}

long fract * FIRFilter::getDelayLine(void ){

	return delayLine;
}

void FIRFilter::process(short* , short* , short* , short len)
{}

#if NORMAL_BUFFER
void FIRFilter::filterProcess(short* input, short* output, short len)
{
	fract *x = (fract *)input;
	fract *y = (fract *)output;
	long fract yTmp = 0;

	for(int n = 0; n < len; n++){

		for(int m = filter_taps_ - 1;  m > 0; m--)	{
			delayLine[m] = delayLine[m-1];
		}

		// Delaylines
		delayLine[0] = x[n];

		// Convolution
		yTmp = 0.0lr;

		for(int m = 0; m < filter_taps_; m++){
			yTmp += (w[m] * delayLine[m]);
		}

		y[n] = (fract)yTmp;
	}
}

#elif CIRCULAR_BUFFER
void FIRFilter::filterProcess(short* input, short* output, short len)
{
	fract *x = (fract*)input;
	fract *y = (fract*)output;
	long fract y_ = 0; //9.31

	int n = 0; int m = 0;
	long fract * delay; //1.31

	for(n = 0; n < len; n++){

		*cir_ptr = x[n];

		cir_ptr = (long fract *)circptr(cir_ptr, sizeof(long fract), delayLine, sizeof(long fract)*filter_taps_);
		delay = (long fract *)cir_ptr;

		y_ = 0.0lr;

		for(m = 0; m < filter_taps_; m++){
			y_ += w[m] * (*delay);
			delay = (long fract *)circptr(delay, sizeof(long fract), delayLine, sizeof(long fract)*filter_taps_);
		}

		y[n] = (fract)y_;
	}
}

#endif

void FIRFilter::create(uint8_t filterTaps){
	// Clear coefficients and delay lines

	delayLine = new long fract[filterTaps];
	w = new long fract[filterTaps];

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
