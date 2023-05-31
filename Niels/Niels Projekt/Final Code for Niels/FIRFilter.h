/*
 * IIRFilter.h
 *
 *  Created on: 28. feb. 2018
 *      Author: Kim Bjerge
 */

#ifndef FIRFILTER_H_
#define FIRFILTER_H_

#include "Algorithm.h"
#include <stdint.h>
#include <stdfix.h>
#include <fract.h>

#define MAX_TAPS 200
#define NORMAL_BUFFER 1
#define CIRCULAR_BUFFER 0

class FIRFilter : public Algorithm {
public:
	FIRFilter();
	~FIRFilter();
	virtual void process(short* input, short* input2, short* output, short len);
    virtual void filterProcess(short* input, short* output, short len);
	virtual void create(uint8_t filterTaps);

	void updateWeights(long fract*);
	long fract * getDelayLine(void );

private:
	uint8_t filter_taps_;

#if CIRCULAR_BUFFER
    long fract * cir_ptr;
#endif

	long fract* w;
	long fract* delayLine;

	void setFilterTaps(uint8_t numTaps);
};

#endif /* FIRFILTER_H_ */
