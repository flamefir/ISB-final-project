///////////////////////////////////////////////////////////////////////////////
//
// 	
//  Experiment 7.4 talk-through program using BF533 EZ-KIT
//  FILE name: ISR.c
//
//  Description: C file containing the interrupt service routine for SPORT0_RX.
//		 This ISR is executed after a complete frame of input data 	
//		 has been received. 
//  
//  For the book "Embedded Signal Processing with the Micro Signal Architecture"
//		  By Woon-Seng Gan and Sen M. Kuo
//		  Publisher: John Wiley and Sons, Inc.
//
//  Tools used: VisualDSP++ v4.0 (running on BF533 EZ-KIT)
//  Modified: 6/8-2014 - KBE
//
///////////////////////////////////////////////////////////////////////////////
#include "HAL.h"

EX_INTERRUPT_HANDLER(Sport0_RX_ISR)
{
	int i;
	static short j=0,k=0;
	
	// confirm interrupt handling
	//BF533 Hardware Reference pg 9-32
	*pDMA1_IRQ_STATUS = 0x0001;
	
	// Move data from receive buffer to local buffer
	//#pragma no_alias
	for (i = 0; i < INPUT_SIZE; i++)
	{
		// Retrieve all the samples from receive buffer to process buffer
		sCh0LeftIn[i] = sDataBufferRX[INTERNAL_ADC_L0+j];
		sCh0RightIn[i] = sDataBufferRX[INTERNAL_ADC_R0+j];
		//sCh1LeftIn[i] = sDataBufferRX[INTERNAL_ADC_L1+j];
		//sCh1RightIn[i] = sDataBufferRX[INTERNAL_ADC_R1+j];
		
		// use the builtin circular buffer to update the index
		j = circindex(j, 4, 4*INPUT_SIZE*TOTAL_FRAME);
	}
	
	Process();
	
	//#pragma no_alias
	for (i=0; i<INPUT_SIZE; i++)
	{
		sDataBufferTX[INTERNAL_DAC_L0+k] = sCh0LeftOut[i];
		// use the builtin circular buffer to update the index
		k = circindex(k, 4, 4*INPUT_SIZE*TOTAL_FRAME);
		
	}	
}

EX_INTERRUPT_HANDLER(Timer_ISR)
{
	*pTIMER_STATUS = 0x0001;
	
	//if((ucLED = ucLED >> 1) == 0x00) ucLED = 0x20; // Toggle LED
	
}

