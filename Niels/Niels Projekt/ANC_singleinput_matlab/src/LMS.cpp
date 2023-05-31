///////////////////////////////////////////////////////////
//  LMS.cpp
//  Implementation of the Class Equalizer
//  Created on:      13-marts-2018 10:15:01
//  Original author: kbe
///////////////////////////////////////////////////////////

#include "LMS.h"

#include <string.h>
#include <stdio.h>
#include <cycle_count.h>
#include <math.h>


LMS::LMS(int filterTaps) : m_FIRFilter()
{
	filterTaps_ = filterTaps; // Temporary
	error_ = 0;
    mu_ = 0.001;
}

LMS::~LMS(){

}

uint16_t counter = 0;
uint16_t counter_error = 0;

void LMS::process(short* refInput, short * errorInput, short* output, short len)
{

	/*if(counter == 100)
		CYCLES_START(m_stats);*/

	// Perform notch filtering
	//m_FIRFilter.FilterProcess(refInput, output, len);

	for(int i = 0; i < len; i++)
	{

		m_FIRFilter.FilterProcess(&refInput[i], &output[i], 1);


		calcError(&refInput[i], &output[i]);   // Calculate errors

		adaptWeights();

		m_FIRFilter.updateWeights(weights_);
	}



	/*if(counter == 100){
		CYCLES_STOP(m_stats);
		CYCLES_PRINT(m_stats);
		CYCLES_RESET(m_stats);
		counter = 0;
	}
	counter++;*/

 }


void LMS::calcError(short* d_signal, short* y_signal)
{
	fract *d = (fract *)d_signal;
	fract *y = (fract *)y_signal;

	error_ = -d[0] - y[0];
	errors_[counter_error] = error_;
	counter_error++;
	//printf("%d\n", error_);
}

void LMS::setError(fract num)
{
	error_ = num;
}

void LMS::adaptWeights()
{
	fract * delayLine = m_FIRFilter.getDelayLine();

	for(uint8_t i = 0; i < filterTaps_; i++)
	{
		weights_[i] = weights_[i] + (mu_ * error_ * delayLine[i]);
	}

}

short* LMS::getWeights()
{

	return (short*)weights_;

}

short* LMS::getErrors()
{
	return (short*)errors_;
}

void LMS::create(void)
{
	m_FIRFilter.create(filterTaps_);   // Create FIR Filter

	for(uint8_t i = 0; i < filterTaps_; i++)
	{
		weights_[i] = 0;
	}

	//CYCLES_INIT(m_stats);
}
