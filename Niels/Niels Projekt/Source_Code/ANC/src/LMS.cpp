

#include "LMS.h"

#include <string.h>
#include <stdio.h>
#include <cycle_count.h>
#include <math.h>


LMS::LMS() : m_FIRFilter()
{

}

LMS::~LMS(){

}

uint16_t counter_error = 0;

void LMS::process(short* refInput, short * errorInput, short* output, short len)
{
	fract *errorPointer = (fract *)errorInput;

	for(int i = 0; i < len; i++)
	{
		//printf("%d \n",i);
		m_FIRFilter.filterProcess(&refInput[i], &output[i], 1);

		error_ = errorPointer[i];
		//calcError(&refInput[i], &output[i], &errorInput[i]);   // Calculate errors

		adaptWeights();
	}
 }

void LMS::calcError(short* d_signal, short* y_signal, short* e_signal)
{
	fract *d = (fract *)d_signal;
	fract *y = (fract *)y_signal;
	fract *e = (fract *)e_signal;
	error_ = -d[0] - y[0];
	e[0] = error_;
}

void LMS::setError(fract num)
{
	error_ = num;
}

void LMS::adaptWeights()
{
	long fract * delayLine = m_FIRFilter.getDelayLine();

    long fract wT = 0;
	for(uint8_t i = 0; i < filterTaps_; i++)
	{
		weights_[i] = weights_[i] + (mu_ * error_ * delayLine[i]);
	}
}

void LMS::create(uint8_t filterTaps)
{
	filterTaps_ = filterTaps; // Temporary
	error_ = 0;
    mu_ = 0.001;

	for(uint8_t i = 0; i < filterTaps_; i++)
	{
		weights_[i] = 0;
	}
	m_FIRFilter.create(filterTaps_);
}
