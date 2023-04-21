///////////////////////////////////////////////////////////
//  Process.cpp
//  Implementation of Process
//  Created on:      06-aug-2014 09:30:58
//  Original author: kbe
///////////////////////////////////////////////////////////
#include "HAL.h"
#include "Algorithm.h"

Algorithm *pAlgoLMS = 0;
Algorithm *pAlgoSecondary = 0;

short buffer[INPUT_SIZE];

void InitProcess(Algorithm *LMS, Algorithm * secondaryPath){

	pAlgoLMS = LMS;
	pAlgoSecondary = secondaryPath;
}

extern "C" {

	// Interface to SPORT interrupt
	void Process(void)
	{
		/* Not used - extra channel Ch1 left/right
		int i;
		for (i=0; i<INPUT_SIZE; i++)
		{
			sCh1LeftOut[i] = sCh1LeftIn[i];
			sCh1RightOut[i] = sCh1RightIn[i];
		}
		*/

												       //    Ref        buf     Size
		if (pAlgoSecondary) pAlgoSecondary->filterProcess(sCh0LeftIn, buffer, INPUT_SIZE); // Secondary path, koeffs
										//Fx	   Error        Output        Size
		if (pAlgoLMS) pAlgoLMS->process(buffer, sCh0RightIn, sCh0LeftOut, INPUT_SIZE);

	}

}
