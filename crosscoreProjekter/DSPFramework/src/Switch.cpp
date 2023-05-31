///////////////////////////////////////////////////////////
//  Switch.cpp
//  Implementation of Switch
//  Created on:      06-aug-2014 09:30:58
//  Original author: kbe
///////////////////////////////////////////////////////////
#include "Controller.h"

// Controller reference
Controller *pCtrlRight;
Controller *pCtrlLeft;

void InitSwitch(Controller *left, Controller *right)
{
	pCtrlLeft = left;
	pCtrlRight = right;
}

extern "C" {

    void PressedSwitch(short sw)
    {
    	pCtrlLeft->pressedSwitch(sw);
    	pCtrlRight->pressedSwitch(sw);
    }

}
