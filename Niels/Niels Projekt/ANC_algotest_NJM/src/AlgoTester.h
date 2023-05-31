/*
 * AlgoTester.h
 *
 *  Created on: 28. feb. 2018
 *      Author: Kim Bjerge
 */

#ifndef ALGOTESTER_H_
#define ALGOTESTER_H_
#include "Algorithm.h"

class AlgoTester {
public:
	AlgoTester(Algorithm *pAlgo);
	short runTest(char *inFileName, char *outFileName, char *weightsFileName, char *errorsFileName);

private:
	short readSignal(short buffer[], char *name);
	short writeSignal(short buffer[], char *name);
	short writeWSignal(short buffer[], char *name);
	Algorithm *m_pAlgo;
};

#endif /* ALGOTESTER_H_ */

