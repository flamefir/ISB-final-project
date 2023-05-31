///////////////////////////////////////////////////////////
//  LMS.h
//  Implementation of the Class Equalizer
//  Created on:      13-marts-2018 10:15:01
//  Original author: kbe
///////////////////////////////////////////////////////////

#if !defined(_DYNAMIC_FILTER_INCLUDED_)
#define _DYNAMIC_FILTER_INCLUDED_

#include <filter.h>
#include <cycles.h>
#include "HAL.h"
#include "Algorithm.h"
#include "FIRFilter.h"


class LMS : public Algorithm
{

public:

	LMS(int filterTaps);
	virtual ~LMS();

	virtual void process(short* refInput, short* errorInput, short* output, short len);
	virtual void create(void);

	void calcError(short* d_signal, short* y_signal );
	void setError(fract);
	void adaptWeights();

	short* getWeights();
	short* getErrors();


protected:
	FIRFilter m_FIRFilter;
	cycle_stats_t m_stats; // Used for cycle counter measure


private:
	fract error_;
	fract mu_;

	uint8_t filterTaps_;

	fract weights_[MAX_TAPS];
	fract errors_[INPUT_SIZE];
};

#endif // !defined(_DYNAMIC_FILTER_INCLUDED_)
