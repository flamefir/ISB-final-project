
#include "stdio.h"
#include "HAL.h"
#include "sysreg.h"  //definition of reg_SYSCFG
#include "ccblkfn.h" //definition of built-in function
					 //  in this program:sysreg_write()
#include "AlgoTester.h"
#include "cycle_count.h"
#include "FIRFilter.h"
#include "LMS.h"
#include "koeffs.h"

// Initialization of sample block processing inputs
void InitProcess(Algorithm *first, Algorithm * second, Algorithm * third);

// Algorithm object construction
LMS FilterANC;
FIRFilter FilterX;
FIRFilter LowPass;

void InitAlgoProcess(void)
{
	FilterANC.create(LMS_KOEFFS);
	FilterX.create(SEC_PATH_KOEFFS);
	LowPass.create(LOW_PASS_KOEFFS);

	FilterX.updateWeights((long fract* )secPathKoeffs); // Initalise weights
    LowPass.updateWeights((long fract* )lowPassKoeffs); // Initalise weights

	InitProcess(&FilterANC, &FilterX, &LowPass);
}

void InitSystemHardware(void)
{
	Init_EBIU();
	Init_1836();
	Init_Sport();
	Init_DMA();
	Init_PF();
	Init_Timer();
}

void main(void)
{
	sysreg_write(reg_SYSCFG, 0x32); //Enable 64-bit,free-running cycle-counter
		  			     	   		//BF533 Hardware Reference pg 4-6 NB!!!

#if 0
	uint16_t numberOfFiles = 2000;
	char x_signal_filename[35];
	char y_signal_filename[35];
	char e_signal_filename[35];

	InitAlgoProcess(); // Initialization of processing algorithms
	AlgoTester algoTest(&FilterANC);

	for(uint16_t i = 0; i < numberOfFiles; i++)
	{
		sprintf(x_signal_filename, "..\\src\\Matlab\\x_signal_%d.txt", i);
		sprintf(y_signal_filename, "..\\src\\Matlab\\y_signal_%d.txt", i);
		sprintf(e_signal_filename, "..\\src\\Matlab\\e_signal_%d.txt", i);
		algoTest.runTest(x_signal_filename, y_signal_filename, "..\\src\\Matlab\\w_signal.txt", e_signal_filename);
	}

#else
	InitSystemHardware(); // Initialization of BF533
	InitAlgoProcess(); // Initialization of processing algorithms
	printf("Application running");
	Init_Interrupt(); // Enable interrupts
	Enable_DMA();
#endif

	cycle_t start_count;
	cycle_t final_count;

	while(1)
	{
	}; // wait forever
}
