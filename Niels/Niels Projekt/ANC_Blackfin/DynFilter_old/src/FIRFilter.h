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

#define MAX_TAPS 200


class FIRFilter : Algorithm {
public:
	FIRFilter(uint8_t filterTaps);
	virtual void process(short* input, short* output, short len);
	virtual void create(void);

	void updateWeights(fract*);
private:
	uint8_t FILTER_TAPS_ = 50;

	fract w[MAX_TAPS];
	fract delayLine[MAX_TAPS - 1];

	void setFilterTaps(uint8_t numTaps);
};

#endif /* FIRFILTER_H_ */
