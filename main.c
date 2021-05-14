    //=============================================================================//
    //                            MSP430 H-BRIDGE MOTOR 1.0                        //
    //=============================================================================//
    //                                                                             //
    //       MSP430F5529             VNH7070                                       //
    //      +------------+       +------------+                                    //
    //      |       P1.2 |-------|PWM         |                                    //
    //      |       P3.0 |-------|INa         |                                    //
    //      |       P3.1 |-------|INb         |          MOTOR                     //
    //      |       P3.2 |-------|SEL         |        +-------+                   //
    //      |            |       |        OUTA|--------|A      |                   //
    //      |            |       |        OUTB|--------|B      |                   //
    //      |            |       +------------+        +-------+                   //
    //      |       P2.0 |-----------------------------|CH_I   |                   //
    //      |       P2.4 |-----------------------------|CH_A   |                   //
    //      |       P2.5 |-----------------------------|CH_B   |                   //
    //      +------------+                             +-------+                   //
    //        Launchpad                                 ENCODER                    //
    //                                                                             //
    //=============================================================================//

#include <msp430.h>
#include <stdio.h>


#include "quadEncDec.h"
#include "pid.h"
#include "pwmTimerA0.h"
#include "UcsControl.h"
#include "usciUart.h"
#include "vnh7070API.h"


#define dcoFreq 20 // MHz.

/**
 * main.c
 */

int main(void){

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    unsigned char oscFail = 1;

    // set clock frequency to 20MHz
    ucsSelSource(1,1,1,1);
    oscFail = ucsDcoFreqSet (dcoFreq, 2, 1);          //set sclk to dcoFreq
    if (oscFail)
      return 1;

	initEncDec();
	usciA1UartInit();
    timerA0Init(10000); // set PWM freq

	// example -90deg move
	posTargetDeg = -90;

	// enable global interrupts (SR.GIE bit)
    __enable_interrupt();

    while(1){
	    __delay_cycles(100000);            // 5ms delay
	    pidControlLoop(2.5, 3.6, 0, 0.01); // Kp, Ki, Kd, dt
    }
    return 0;
}

