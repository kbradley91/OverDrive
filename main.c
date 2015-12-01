/*
 * main.c
 */
#include <DSP28x_Project.h>
#include "DSP_KB.h"
#include "Lab9.h"
#include "FPU.h"
#include <math.h>

RFFT_F32_STRUCT fft;


void fft_init();
unsigned long ISRvalue = &sampleGet_ISR;


int main(void) {
	
	DisableDog();
	CPUinit();
	EALLOW;
	outputEnable();
	LCDinit();
	LCDclear();
	initADC();
	DAC_init();
//	SRAMwrite(0);
//	SRAMaddress = 0x260000; //shouldn't need SRAM here
	fft_init();
	initBuffers();

	timerINIT(ISRvalue, samplingRate);




	while(1){

	}
	return 0;
}

void fft_init(){
	fft.InBuf = sampleBuffer;
	fft.OutBuf = outBuffer;
	fft.CosSinBuf = TwiddleBuffer;
	fft.FFTSize = FFT_SIZE;
	fft.FFTStages = FFT_STAGES;
	fft.MagBuf = MagBuffer;
	RFFT_f32_sincostable(&fft);


}



