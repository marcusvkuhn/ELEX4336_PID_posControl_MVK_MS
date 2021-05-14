/*
 * timerA0.h
 *
 *  Created on: Jan 7, 2021
 *      Author: a01064898
 */

#ifndef PWMTIMERA0_H_
#define PWMTIMERA0_H_

#define SMCLK_20MHZ_D16 1250000

unsigned int timerA0Init(unsigned int pwmFreq);
char timerA0PwmFreqSet(unsigned int pwmFreq);
char timerA0DutyCycleSet(unsigned char dutyCycle);

volatile int currentDS;

#endif /* PWMTIMERA0_H_ */
