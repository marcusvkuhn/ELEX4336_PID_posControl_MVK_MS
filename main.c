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

	// example 180deg
	posTarget = 2300;

	while(1){
	    __delay_cycles(2000000);            // 100ms delay
	    pidControlLoop(500, 375, 25, 0.01); // Kp, Kd, Ki, dt
	}

	return 0;
}
