///////////////////////////////////////////////////////////
//  DynamicFilter.cpp
//  Implementation of the Class Equalizer
//  Created on:      13-marts-2018 10:15:01
//  Original author: kbe
///////////////////////////////////////////////////////////

#include "DynamicFilter.h"

#include <string.h>
#include <stdio.h>
#include <cycle_count.h>

// Used for debugging
//fract16	m_real_magnitude[FFT_SIZE];

 // TODO Threshold value to be adjusted
#define PEAK_THRESHOLD   3000


DynamicFilter::DynamicFilter(int sampleRate):m_IIRFilter()
{
	m_sampleRate = sampleRate;
	m_fnotch = 0.0;
	m_updateNotch = false;
}

DynamicFilter::~DynamicFilter(){

}

void DynamicFilter::process(short* input, short* output, short len)
{
	int block_exponent;

	// Perform notch filtering
	m_IIRFilter.process(input, output, len);

	// TODO add code to perform FFT and magnitude and call findMax
	rfft_fr16(input, m_fft_output, m_twiddle_table, 1, N_FFT, &block_exponent, 2);

	fft_magnitude_fr16(m_fft_output, m_real_magnitude, N_FFT, block_exponent, 1);

	findMax(PEAK_THRESHOLD);
 }

void DynamicFilter::updateDynFilter(void)
{

	if (m_updateNotch)
	{
		// TODO Change code to handle update of notch filter when new peak found
		m_IIRFilter.makeNotch(m_sampleRate, m_fnotch, 0.95);

		//m_IIRFilter.makeNotch(m_sampleRate, 1000, 0.95); // TODO for testing only 1 kHz notch, to be removed
		m_updateNotch = false;
	}

}

// Find maximum peak in FFT magnitude response
void DynamicFilter::findMax(fract16 threshold)
{
	short i, i_max;
	fract16 max = 0;

	// TODO Verify and improve code below to
	// find maximum amplitude in frequency spectrum
	for (i = 1; i < FFT_SIZE; i++)
	{
		if (m_real_magnitude[i] > max)
		{
			i_max = i;
			max = m_real_magnitude[i_max];
		}
	}

	// Check maximum peak above threshold
	if (max >= threshold)
	{
		float fres = (float)m_sampleRate / N_FFT;
		float fnotch = i_max * (fres);
		printf("%f \n", fnotch);
		printf("%f \n", fres);
		if (fnotch != m_fnotch)
		{
			m_fnotch = fnotch;
			// Signal to main loop update notch filter
			m_updateNotch = true;
		}
	}
}

void DynamicFilter::create(void) 
{
	// TODO Compute FFT twiddle factors
	twidfftrad2_fr16(m_twiddle_table, N_FFT);

	// Clear FFT magnitude response
	for (int i = 0; i < FFT_SIZE; i++)
		m_real_magnitude[i] = 0;

	// Initialize IIR cascade filter
	m_IIRFilter.create();

	m_updateNotch = true;

	CYCLES_INIT(m_stats);
}
