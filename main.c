    //=============================================================================//
    //      Controlling the Left Motor using MSP430 Robot shield Ver 1.0           //
    //=============================================================================//
    //                                                                             //
    //       MSP430G2553            L293D                                          //
    //      +------------+       +------------+                                    //
    //      |            |       |            |                                    //
    //      |       P2.3 |-------|3A          |        +-------+                   //
    //      |       P2.4 |-------|4A        3Y|--------|   0   |                   //
    //      |            |       |          4Y|--------|       |                   //
    //      |       P2.6 |-------|3&4_EN      |        +-------+                   //
    //      |            |       |            |          MOTOR                     //
    //      +------------+       +------------+     (DC Brushed Motor)             //
    //        Launchpad           Robot Sheild                                     //
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
void main(void){

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
	posDelta = 2300;

	while(1){
	    __delay_cycles(2000000);            // 100ms delay
	    pidControlLoop(500, 375, 25, 0.01); // Kp, Kd, Ki, dt
	}

}
