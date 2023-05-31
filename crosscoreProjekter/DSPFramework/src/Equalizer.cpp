///////////////////////////////////////////////////////////
//  Equalizer.cpp
//  Implementation of the Class Equalizer
//  Created on:      06-aug-2014 09:31:01
//  Modified:        28-feb-2018 09:32:00
//  Original author: kbe
///////////////////////////////////////////////////////////
#include "Equalizer.h"

#include <stdio.h>
#include <string.h>
#include <stdfix.h>

Equalizer::Equalizer(int sampleRate)
{
	m_sampleRate = sampleRate;
	m_filterOn = false;
}

Equalizer::~Equalizer()
{

}

void Equalizer::process(short* input, short* output, short len)
{
	// TODO change code to processing all IIR filters
	if (m_filterOn)
		m_IIRfilter[0].process(input, output, len);
	else
		// Pass through, just copy input block to output
		for (short i = 0; i < len; i++)
			output[i] = input[i];
}

void Equalizer::create(void)
{
	for (short band = 0; band < NUM_EQ_BANDS; band++)
	{
		m_IIRfilter[band].create();
	    m_EQParams[band].gain = 1; // Default gain
		m_EQParams[band].Q = 10; // Default Q
	}
	// Setting default peak bands center frequency
	m_EQParams[0].fc = 200;
	m_EQParams[1].fc = 600;
	m_EQParams[2].fc = 2000;
	m_EQParams[3].fc = 6000;
}

float Equalizer::incParameter(short band, PARAMETER param, float delta)
{
	// TODO change code to increment parameter for IIR filters (See slides) - call updateEQParamters
    float value = 0;
    m_filterOn = true; // For test only
	return value;
}

float Equalizer::decParameter(short band, PARAMETER param, float delta)
{
	// TODO change code to decrement parameter for IIR filters - call updateEQParamters
    float value = 0;
    m_filterOn = false; // For test only
	return value;
}

void Equalizer::setParameter(short band, PARAMETER param, float value)
{
    bool update = false;

	if (band < NUM_EQ_BANDS)
	{
		switch (param)
		{
			case PM_GAIN:
				if (m_EQParams[band].gain != value) {
					m_EQParams[band].gain = value;
					update = true;
				}
			  break;
			case PM_FREQ:
				if (m_EQParams[band].fc != value) {
					m_EQParams[band].fc = value;
					update = true;
				}
			  break;
			case PM_Q:
				if (m_EQParams[band].Q != value) {
					m_EQParams[band].Q = value;
					update = true;
				}
			  break;
		}
		if (update) updateEQParameters(band);
	}
}

void Equalizer::updateEQParameters(short band)
{
	// Parameter limitations
	if (m_EQParams[band].gain > MAX_GAIN)
		m_EQParams[band].gain = MAX_GAIN;
	if (m_EQParams[band].gain < MIN_GAIN)
		m_EQParams[band].gain = MIN_GAIN;
	if (m_EQParams[band].fc > MAX_FREQ)
		m_EQParams[band].fc = MAX_FREQ;
	if (m_EQParams[band].fc < MIN_FREQ)
		m_EQParams[band].fc = MIN_FREQ;
	if (m_EQParams[band].Q > MAX_Q)
		m_EQParams[band].Q = MAX_Q;
	if (m_EQParams[band].Q < MIN_Q)
		m_EQParams[band].Q = MIN_Q;

	// Call creating peaking filter for IIR filter band
	m_IIRfilter[band].makePeakEQ(m_sampleRate,
							      m_EQParams[band].fc,
								  m_EQParams[band].Q,
								  m_EQParams[band].gain);

}
