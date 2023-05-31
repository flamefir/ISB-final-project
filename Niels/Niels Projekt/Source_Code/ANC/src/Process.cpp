
#include "HAL.h"
#include "Algorithm.h"
#include <stdio.h>
#include <cycle_count.h>
#include <cycles.h>

Algorithm *pAlgoLMS = 0;
Algorithm *pAlgoSecondary = 0;
Algorithm *pAlgoTertiary = 0;

uint16_t counter = 0;
cycle_stats_t m_stats;

void InitProcess(Algorithm *LMS, Algorithm * secondaryPath, Algorithm * thirdPath){

	CYCLES_INIT(m_stats);

	pAlgoLMS = LMS;
	pAlgoSecondary = secondaryPath;
	pAlgoTertiary = thirdPath;
}

extern "C" {

	// Interface to SPORT interrupt
	void Process(void)
	{
		if(counter == 100)
				CYCLES_START(m_stats);

		if (pAlgoSecondary) pAlgoSecondary->filterProcess(sCh0LeftIn, buffer_1, INPUT_SIZE); // Secondary path, koeffs
										//Fx	   Error        Output        Size
		if (pAlgoLMS) pAlgoLMS->process(buffer_1, sCh0RightIn, buffer_2, INPUT_SIZE);

		if (pAlgoTertiary) pAlgoTertiary->filterProcess(buffer_2, sCh0LeftOut, INPUT_SIZE); // Secondary path, koeffs
	       //    Ref        buf     Size

		if(counter == 100){
				CYCLES_STOP(m_stats);
				CYCLES_PRINT(m_stats);
				CYCLES_RESET(m_stats);
				counter = 0;
			}
		counter++;

	}

}
