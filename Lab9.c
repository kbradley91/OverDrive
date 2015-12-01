/*
 * Lab9.c
 *
 *  Created on: Dec 1, 2015
 *      Author: Kyle
 */



#include <DSP28x_Project.h>
#include "DSP_KB.h"
#include "Lab9.h"
#include "FPU.h"

interrupt void sampleGet_ISR(void){
	unsigned int input = ADC_get();

	sampleBuffer[sampleCount] = input;
	sampleCount++;
	if(sampleCount == FFT_SIZE){
		sampleCount = 0;
		sampleBufferFull = 1;
		DINT; //disables interrupts, if doesn't work can send to dummy interrupt vector
	}

}

void initBuffers(){
	int i,k;
	for(i = 0; i<FFT_SIZE;i++){
		sampleBuffer[i] = 0;
	}

	for(k = 0; i<FFT_SIZE/2;i++){
			SumSpectrum[i] = 0;
	}

}
