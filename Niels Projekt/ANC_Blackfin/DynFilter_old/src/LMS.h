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

	LMS(int sampleRate);
	virtual ~LMS();

	virtual void process(short* input, short* output, short len);
	virtual void create(void);

	void calcError(fract* x_signal, fract* d_signal);
	void setError(fract);
	void adaptWeights(fract* x_signal);


protected:
	FIRFilter m_FIRFilter;
	cycle_stats_t m_stats; // Used for cycle counter measure


private:
	fract error_;
	fract mu_;

};

#endif // !defined(_DYNAMIC_FILTER_INCLUDED_)
