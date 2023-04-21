

#if !defined(ALGORITHM_INCLUDED_)
#define ALGORITHM_INCLUDED_

#include <stdint.h>

class Algorithm
{

public:
	Algorithm();
	virtual ~Algorithm();

	virtual void filterProcess(short* input, short* output, short len) = 0;
	virtual void process(short* input, short*, short* output, short len) = 0;
	virtual void create(uint8_t filterTaps) = 0;
	//virtual short* getWeights() = 0;
	//virtual short* getErrors() = 0;

};
#endif // !defined(ALGORITHM_INCLUDED_)
