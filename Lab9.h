/*
 * Lab9.h
 *
 *  Created on: Dec 1, 2015
 *      Author: Kyle
 */

#ifndef LAB9_H_
#define LAB9_H_

#define FFT_SIZE 64
#define FFT_STAGES 6 //log base 2 (FFT_size)


static float sampleBuffer[FFT_SIZE];
static float outBuffer[FFT_SIZE];
static float TwiddleBuffer[FFT_SIZE];
static float MagBuffer[FFT_SIZE/2];
static float SumSpectrum[FFT_SIZE/2];

static int sampleCount = 0;
static int sampleBufferFull = 0; //variable used to denote whether the buffer has been filled

interrupt void sampleGet_ISR(void);
void initBuffers();



#endif /* LAB9_H_ */
