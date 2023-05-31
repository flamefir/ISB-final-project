/*
 * IIRFilter.h
 *
 *  Created on: 28. feb. 2018
 *      Author: Kim Bjerge
 */

#ifndef IIRFILTER_H_
#define IIRFILTER_H_

#include "Algorithm.h"
#include <stdfix.h>

#define NUM_IIR_COEFFS 3

typedef struct
{
	long fract a[NUM_IIR_COEFFS]; 		// a coefficients, a[0] used for scaling
	long fract b[NUM_IIR_COEFFS]; 		// b coefficients
	fract x[NUM_IIR_COEFFS-1]; 			// x delay line x(n-1), x(n-2)
	long fract y[NUM_IIR_COEFFS-1]; 	// y delay line y(n-1), y(n-2), store y in format 1.31 to minimize product quantization
} IIR_BIQUAD;

class IIRFilter : public Algorithm {
public:
	IIRFilter();
	virtual void process(short* input, short* output, short len);
	virtual void create(void);

	// Sets the filter as a peaking EQ filter
    void makePeakEQ (const float fs,
                     const float fc,
                     const float Q,
                     const float A);

private:
	IIR_BIQUAD bq;
};

#endif /* IIRFILTER_H_ */
