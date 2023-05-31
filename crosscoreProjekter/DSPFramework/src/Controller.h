///////////////////////////////////////////////////////////
//  Controller.h
//  Implementation of the Class Controller
//  Created on:      06-aug-2014 23:31:01
//  Original author: kbe
///////////////////////////////////////////////////////////

#if !defined(CONTROLLER__INCLUDED_)
#define CONTROLLER__INCLUDED_

#include "Equalizer.h"
#include "HAL.h"

class Controller
{

public:

	Controller(Equalizer *eq);
	virtual ~Controller();

	void incBand();
	void incParam();
	void incParamValue();
	void decParamValue();
	void pressedSwitch(short sw);

protected:
    void updateUI();
	Equalizer *m_eq;
	short m_band;
};

#endif // !defined(CONTROLLER__INCLUDED_)
