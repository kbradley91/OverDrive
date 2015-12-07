/*
 * main.c
 */
#include <DSP28x_Project.h>
#include "DSP_KB.h"

#include <math.h>
/*
 *  The current goal is to attemp to filter out the guitar sounds and add gain to those values manually, increasing the effect of the guitar in the sample, I believe that the guitar will
 *  be in the higher range of frequiences, 200hz - 1000hz. I believe that drums and voice will lie outside the range of these, and should not be effected by the filter
 *
 *
 */
interrupt void overDrive(void);

unsigned long ISRvalue = &overDrive;

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

	timerINIT(ISRvalue, samplingRate);

	while(1){


	}


	return 0;
}

interrupt void overDrive(void){
	int input = ADC_get();
	input = input - 0x7FFF;
	float test1;
	test1 = input;
	test1 = test1/(65535);
	if(test1 >= 0){
		test1 = ((1-0.25/(test1+0.25)));
	}
	else if(test1 < 0){
		test1 = ((1+0.25/(test1-0.25)));
	}
	test1 = test1 * 65535;


	DAC_set(test1);

}

interrupt void overDrive2(void){

	int input = ADC_get();
	input = input - 0x7FFF;
	float test1 = input;
	test1 = test1/(65535/2);
	if(abs(test1)<1/3){
		test1 = test1*2;
	}
	else if(abs(test1)){

	}




}


