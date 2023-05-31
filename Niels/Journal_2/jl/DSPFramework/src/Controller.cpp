///////////////////////////////////////////////////////////
//  Controller.cpp
//  Implementation of the Class Controller
//  Created on:      06-aug-2014 23:31:01
//  Original author: kbe
///////////////////////////////////////////////////////////

#include "Controller.h"

Controller::Controller(Equalizer *eq) : m_band(0)
{
	m_eq = eq;
}

Controller::~Controller()
{

}

void Controller::updateUI()
{
	SetMaskLed(0x0f, m_band<<4);
}

void Controller::incBand()
{
	// Selects the next EQ band
	m_band++;
	if (m_band >= NUM_EQ_BANDS)
		m_band = 0;
	updateUI();
}

void Controller::incParam()
{
	// TODO Optional to insert code to select next parameter in algorithm
}

void Controller::incParamValue()
{
	// Increments parameter value for PM_GAIN
	float val = m_eq->incParameter(m_band, PM_GAIN, 0.1);

	// Update LED UI
	unsigned char tmp = (val > 2 ? val: val*10);
	SetMaskLed(0x38, tmp & 0x07);
}

void Controller::decParamValue()
{
	// Decrements parameter value for PM_GAIN
	float val = m_eq->decParameter(m_band, PM_GAIN, 0.1);

	// Update LED UI
	unsigned char tmp = (val > 2 ? val: val*10);
	SetMaskLed(0x38, tmp & 0x07);
}

void Controller::pressedSwitch(short sw)
{
	switch (sw) {
		case KEY_SW4:
			incParamValue(); // Increment selected parameter value
			break;
		case KEY_SW5:
			decParamValue(); // Decrement selected parameter value
			break;
		case KEY_SW6:
			incParam(); // Select parameter - optional not implemented
			break;
		case KEY_SW7:
			incBand(); // Select equalizer band to adjust
			break;
	}
}

