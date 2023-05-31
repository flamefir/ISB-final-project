///////////////////////////////////////////////////////////////////////////////
//
// 	DSP Design Framework (C++) for stereo 16 bit sample block processing
//  Prepared for a 4 bands equalizer
//  
//  Main program and initialization
//
//  28. feb. 2018 KBE
///////////////////////////////////////////////////////////////////////////////
#include "stdio.h"
#include "HAL.h"
#include "sysreg.h"  //definition of reg_SYSCFG
#include "ccblkfn.h" //definition of built-in function
					 //  in this program:sysreg_write()
#include "Controller.h"
#include "AlgoTester.h"
#include "cycle_count.h"
#include "FIRFilter.h"
#include "LMS.h"

#define SEC_PATH_KOEFFS 20
#define LOW_PASS_KOEFFS 53
#define LMS_KOEFFS 200
// Initialization of sample block processing inputs
void InitProcess(Algorithm *first);//, Algorithm * second, Algorithm * third);

// Initialization of control for switch inputs
//void InitSwitch(Controller *left, Controller *right);

// Instance of dummy algorithm for left and right stereo channels
LMS FilterANC;

// Instance of controller left and right
//Controller CtrlANC(&FilterANC);

void InitAlgoProcess(void)
{
	uint8_t filterTaps = 50;
	// Initialization of boundary interfaces (interrupts)
	FilterANC.create(LMS_KOEFFS);
	//FilterX.create();
	//LowPass.create();

	//FilterX.updateWeights(secPathKoeffs); // Initalise weights
    //LowPass.updateWeights(lowPassKoeffs); // Initalise weights

	InitProcess(&FilterANC);//, &FilterX, &LowPass);
	//InitSwitch(&CtrlANC, NULL);
}

void InitSystemHardware(void)
{
	ucLED = 0x3F; // Turn all LEDs on

	Init_EBIU();
	Init_LED();
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
/*
#if 1// TODO Set to 1 for testing
	InitAlgoProcess(); // Initialization of processing algorithms

	AlgoTester algoTest(&FilterANC);
	algoTest.runTest("..\\src\\Matlab\\x_signal.txt", "..\\src\\Matlab\\y_signal.txt", "..\\src\\Matlab\\w_signal.txt", "..\\src\\Matlab\\e_signal.txt");
*/

#if 1
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
	printf("Application running: SW4 turns filter on, SW5 turns filter off\r\n");
	Init_Interrupt(); // Enable interrupts
	Enable_DMA();
#endif

	cycle_t start_count;
	cycle_t final_count;

	while(1)
	{

	}; // wait forever
}
