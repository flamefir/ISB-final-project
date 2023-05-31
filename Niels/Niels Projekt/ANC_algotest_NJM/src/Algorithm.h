///////////////////////////////////////////////////////////
//  Algorithm.h
//  Implementation of the Class Algorithm
//  Created on:      06-aug-2014 09:30:58
//  Original author: kbe
///////////////////////////////////////////////////////////

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
