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
	FIRFilter();
	virtual void process(short* input, short* input2, short* output, short len);
    void FilterProcess(short* input, short* output, short len);
	virtual void create(void);
	virtual void create(uint8_t filterTaps);

	void updateWeights(fract*);
	fract * getDelayLine(void );


private:
	uint8_t filter_taps_;

	fract w[MAX_TAPS];
	fract delayLine[MAX_TAPS];

	void setFilterTaps(uint8_t numTaps);
};

#endif /* FIRFILTER_H_ */
