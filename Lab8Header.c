/*
 * Lab8Header.c
 *
 *  Created on: Nov 22, 2015
 *      Author: Kyle
 */

#include <DSP28x_Project.h>
#include "Lab8Header.h"
#include "DSP_KB.h"


void init_xybuffers(){
	int i;
	for(i = 0;i<4;i++){
		xArray[i] = 0;
		yArray[i] = 0;
	}

}

void setSpeed(){

	EALLOW;
	ConfigCpuTimer(&CpuTimer2, 150, 1000000*1/samplingRate2Test*.5);
	CpuTimer2Regs.TCR.bit.TSS = 0;
	PieVectTable.TINT2 = &cpu_timer2_isr;
	EALLOW;
}
interrupt void cpu_timer2_isr(void){
	//test
	setSpeed();
	moveDelay();

}

void calcPosition(){
	delayPos = currentPos;
	delayPos = delayPos - reverbDelay;

	if(delayPos < dStart){

		unsigned int distance = dStart - delayPos; //how far under dStart delayPos is
		delayPos = dEnd - distance;

	}




}
void moveDelay(){

	if(reverbDelay == 0xFF){
		upORdown = 1;
	}
	if(upORdown == 1){
		reverbDelay--;
	}
	else{
		reverbDelay++;
	}

	if(reverbDelay == 0){
		upORdown = 0;
		reverbDelay = 1;
	}

}

interrupt void weirdThings_ISR(void){
	unsigned int input = ADC_get();
	*currentPos = input;

	calcPosition();

	unsigned long output;
	unsigned int value2 = *delayPos;
	output = (input+0.5*value2)/2;
	DAC_set((unsigned int)output);
	currentPos++;
	if(currentPos > dEnd){
		currentPos = dStart;
	}





}

interrupt void IIRlowpass_ISR(void){

	unsigned int input = ADC_get();

	*xstart = input;
	xstart++;
	cBuffer = xstart;

	int i;
	float out = 0;
	float out2 = 0;
	unsigned int temp;
	for(i = 0;i<sizeof(xArray);i++){
		cBuffer--;
		if(cBuffer < xArrayStart){
			cBuffer = xArrayEnd;
		}
		temp = *cBuffer;
		out += bCoef[i]*temp;


	}
	if(xstart>xArrayEnd){
		xstart = xArrayStart;
	}

	cBuffer = ystart;

	for(i = 1;i<sizeof(yArray);i++){
		cBuffer--;
		if(cBuffer < yArrayStart){
			cBuffer = yArrayEnd;
		}
		temp = *cBuffer;
		out2 += aCoef[i]*temp;
	}
	out = out - out2;
	*ystart = out;

	ystart++;
	if(ystart>yArrayEnd){
		ystart = yArrayStart;
	}
	DAC_set(out);

}


