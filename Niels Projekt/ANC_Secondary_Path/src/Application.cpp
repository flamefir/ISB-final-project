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
// Initialization of sample block processing inputs
void InitProcess(Algorithm *left, Algorithm *right);
// Initialization of control for switch inputs
void InitSwitch(Controller *left, Controller *right);

fract secPathKoeffs[SEC_PATH_KOEFFS] =
	{0.322366788042028r,  0.264395928385794r,  0.206066242868475r,  0.149776532650045r,
     0.097695841230382r,  0.051660017922076r,  0.013088842315497r, -0.017072109157242r,
	-0.038382133062154r, -0.050907479756676r, -0.055195360322059r, -0.052221980344917r,
	-0.043318145936232r, -0.030077203844141r, -0.014250997635853r,  0.002359899280098r,
	 0.018015211095060r,  0.031136960681540r,  0.040398700677130r,  0.044797097989259r
};


// Instance of dummy algorithm for left and right stereo channels
LMS FilterANC(100);
FIRFilter FilterX;

// Instance of controller left and right
Controller CtrlANC(&FilterANC);

void InitAlgoProcess(void)
{
	// Initialization of boundary interfaces (interrupts)
	FilterANC.create();
	FilterX.create(SEC_PATH_KOEFFS);      // Sekundær path
	FilterX.updateWeights(secPathKoeffs); // Initalise weights

	InitProcess(&FilterANC, NULL);
	InitSwitch(&CtrlANC, NULL);
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

#if 0// TODO Set to 1 for testing
	InitAlgoProcess(); // Initialization of processing algorithms

	AlgoTester algoTest(&FilterANC);
	algoTest.runTest("..\\src\\x_signal.txt", "..\\src\\y_signal.txt");
#else
	InitSystemHardware(); // Initialization of BF533
	InitAlgoProcess(); // Initialization of processing algorithms
	printf("Application running: SW4 turns filter on, SW5 turns filter off\r\n");
	Init_Interrupt(); // Enable interrupts
	Enable_DMA();
#endif

	cycle_t start_count;
	cycle_t final_count;

	//uint16_t counter = 0;

	while(1)
	{
		//FilterLeft.updateDynFilter();


	}; // wait forever
}
