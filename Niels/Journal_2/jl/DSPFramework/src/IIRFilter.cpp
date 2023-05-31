/*
 * IIRFilter.cpp
 *
 *  Created on: 28. feb. 2018
 *      Author: Kim Bjerge
 */

#include "IIRFilter.h"
#include "math.h"

IIRFilter::IIRFilter()
{
	// Clear coefficients and delay lines
	for (short i = 0; i < NUM_IIR_COEFFS; i++) {
		bq.a[i] = 0;
		bq.b[i] = 0;
		if (i < NUM_IIR_COEFFS-1) {
			bq.x[i] = 0;
			bq.y[i] = 0;
		}
	}
}

void IIRFilter::process(short* input, short* output, short len)
{
	// Performs 2. order IIR filtering using Native fractional types
	fract *x = (fract *)input;
	fract *y = (fract *)output;
	accum ylf;
	for (short i = 0; i < len; i++) {
		ylf = bq.b[0]*x[i] + bq.b[1]*bq.x[0] + bq.b[2]*bq.x[1] - bq.a[1]*bq.y[0] - bq.a[2]*bq.y[1];
	    bq.y[1] = bq.y[0];
	    bq.y[0] = ylf/bq.a[0];
	    y[i] = (fract)bq.y[0];
	    bq.x[1] = bq.x[0];
	    bq.x[0] = x[i];
	}
}

/** Sets the filter up to act as a peaking EQ filter centered around a
    frequency (fc), with a variable Q and gain (A), given by sample frequency fs
*/
void IIRFilter::makePeakEQ(const float fs,
						   const float fc,
						   const float Q,
						   const float A)
{
	// TODO insert code to calculate Peak filter, by setting coefficients based on input parameters
	float w0 = 2*3.14159265358979*(fc/fs);
	float alpha = sin(w0)/(2*Q);

	float temp1[NUM_IIR_COEFFS];
	float temp2[NUM_IIR_COEFFS];

	temp1[0] = 1+alpha/A;
	temp1[1] = -2*cos(w0);
	temp1[2] = 1-alpha/A;

	temp2[0] = 1+alpha*A;
	temp2[1] = -2*cos(w0);
	temp2[2] = 1-alpha*A;


	for (short i = 0; i < NUM_IIR_COEFFS; i++) {
		bq.a[i] = temp1[i]/(2*temp1[0]);
		bq.b[i] = temp2[i]/(2*temp1[0]);
	}


}

// Only for testing
// Setting a default notch filter 1 kHz, fs = 48 kHz, r = 0.8
// const fract aTest[NUM_IIR_COEFFS] = {0.5r, -0.7932r, 0.3200r};
// const fract bTest[NUM_IIR_COEFFS] = {0.5r, -0.9914r, 0.5000r};

void IIRFilter::create(void)
{
	// Initialization of coefficients
	// TODO change method to make a pass through filter (a0 = 1.0, b0 = 1.0)
	bq.a[0] = 1.0;
	bq.a[1] = 0;
	bq.a[2] = 0;

	bq.b[0] = 1.0;
	bq.b[1] = 0;
	bq.b[2] = 0;

	/*
	for (short i = 0; i < NUM_IIR_COEFFS; i++) {
		bq.a[i] = aTest[i];
		bq.b[i] = bTest[i];
	}
	*/
}
