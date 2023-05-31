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

// Used for debugging
//fract16	m_real_magnitude[FFT_SIZE];

 // TODO Threshold value to be adjusted
#define PEAK_THRESHOLD   3000


LMS::LMS(int filterTaps) : m_FIRFilter()
{
	filterTaps_ = filterTaps; // Temporary
	error_ = 0;
    mu_ = 0.001r;
	//m_updateNotch = false;
}

LMS::~LMS(){

}

//uint16_t counter = 0;

void LMS::process(short* refInput, short * errorInput, short* output, short len)
{

	/*if(counter == 100)
		CYCLES_START(m_stats);*/

	fract *errorPointer = (fract *)errorInput;

	// Perform FIR
	//m_FIRFilter.filterProcess(refInput, output, len);

	for(int i = 0; i < len; i++)
	{

		m_FIRFilter.filterProcess(&refInput[i], &output[i], 1);

		error_ = errorPointer[i];
		//calcError(&refInput[i], &output[i]);   // Calculate errors

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

/*void LMS::updateFirFilter(void)
{

	if (m_updateNotch)
	{
		// TODO Change code to handle update of notch filter when new peak found
		m_IIRFilter.makeNotch(m_sampleRate, m_fnotch, 0.95);

		//m_IIRFilter.makeNotch(m_sampleRate, 1000, 0.95); // TODO for testing only 1 kHz notch, to be removed
		m_updateNotch = false;
	}

}*/


void LMS::create(void)
{
	m_FIRFilter.create(filterTaps_);   // Create FIR Filter

	for(uint8_t i = 0; i < filterTaps_; i++)
	{
		weights_[i] = 0;
	}


}
