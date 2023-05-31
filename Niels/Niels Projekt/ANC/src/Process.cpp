///////////////////////////////////////////////////////////
//  Process.cpp
//  Implementation of Process
//  Created on:      06-aug-2014 09:30:58
//  Original author: kbe
///////////////////////////////////////////////////////////
#include "HAL.h"
#include "Algorithm.h"
#include <stdio.h>
#include <cycle_count.h>
#include <cycles.h>

Algorithm *pAlgoLMS = 0;
Algorithm *pAlgoSecondary = 0;

short buffer[INPUT_SIZE];

uint16_t counter = 0;
cycle_stats_t m_stats;

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
		if(counter == 100)
				CYCLES_START(m_stats);
												       //    Ref        buf     Size
		//if (pAlgoSecondary) pAlgoSecondary->filterProcess(sCh0LeftIn, buffer, INPUT_SIZE); // Secondary path, koeffs
										//Fx	   Error        Output        Size
		if (pAlgoLMS) pAlgoLMS->process(buffer, sCh0RightIn, sCh0LeftOut, INPUT_SIZE);

		if(counter == 100){
				CYCLES_STOP(m_stats);
				CYCLES_PRINT(m_stats);
				CYCLES_RESET(m_stats);
				counter = 0;
			}
		counter++;

	}

}
