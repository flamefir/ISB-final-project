///////////////////////////////////////////////////////////////////////////////
//
// 	DSP Design Framework (C++) for stereo 16 bit sample block processing
//  Prepared for a dynamic notch filter controlled by FFT analysis (N=1024)
//  
//  Main program and initialization
//
//  13. marts. 2018 KBE
///////////////////////////////////////////////////////////////////////////////
#include "stdio.h"
#include "HAL.h"
#include "sysreg.h"  //definition of reg_SYSCFG
#include "ccblkfn.h" //definition of built-in function
					 //  in this program:sysreg_write()
#include "Controller.h"
#include "Equalizer.h"
#include "AlgoTester.h"

// Initialization of sample block processing inputs
void InitProcess(Algorithm *left, Algorithm *right);
// Initialization of control for switch inputs
void InitSwitch(Controller *left, Controller *right);

// Instance of dummy algorithm for left and right stereo channels
Equalizer FilterLeft(SAMPLE_FS);
Equalizer FilterRight(SAMPLE_FS);

// Instance of controller left and right
Controller CtrlLeft(&FilterLeft);
Controller CtrlRight(&FilterRight);

void InitAlgoProcess(void)
{
	// Initialization of boundary interfaces (interrupts)
	FilterLeft.create();
	FilterRight.create();
	InitProcess(&FilterLeft, &FilterRight);
	InitSwitch(&CtrlLeft, &CtrlRight);
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
#if 0
	// TODO Set to 1 for testing
	InitAlgoProcess(); // Initialization of processing algorithms
	FilterLeft.setBypass(false);
	AlgoTester algoTest(&FilterLeft);
	algoTest.runTest("..\\src\\x_signal.txt", "..\\src\\y_signal.txt");
#else
	InitSystemHardware(); // Initialization of BF533
	InitAlgoProcess(); // Initialization of processing algorithms
	printf("Application running: SW4 turns filter on, SW5 turns filter off\r\n");
	Init_Interrupt(); // Enable interrupts
	Enable_DMA();
#endif

	while(1)
	{
		// TODO insert background processing code as necessary
	}; // wait forever
}
