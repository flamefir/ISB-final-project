

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
	LMS();
	virtual ~LMS();

	virtual void filterProcess(short* input, short* output, short len){};
	virtual void process(short* refInput, short* errorInput, short* output, short len);
	virtual void create(uint8_t filterTaps);

	void calcError(short* d_signal, short* y_signal, short* e_signal );
	void setError(fract);
	void adaptWeights();

protected:
	FIRFilter m_FIRFilter;

private:
	fract error_;
	fract mu_;
	long fract weights_[MAX_TAPS];
	uint8_t filterTaps_;
};

#endif // !defined(_DYNAMIC_FILTER_INCLUDED_)
