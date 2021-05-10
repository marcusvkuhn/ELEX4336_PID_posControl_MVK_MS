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
#include "cmdParser.h"


#define dcoFreq 20 // MHz.

/**
 * main.c
 */
void main(void){

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
    unsigned char oscFail = 1;
    char rxString[50];
//    char speedStr[30];
//    int clrLenght;

    // set clock frequency to 20MHz
    ucsSelSource(1,1,1,1);
    oscFail = ucsDcoFreqSet (dcoFreq, 2, 1);          //set sclk to dcoFreq
    if (oscFail)
      return 1;

	initEncDec();
	usciA1UartInit();
    CMD cmds[MAX_CMDS]; //this is an array of vnh7070Cmds of type CMD
    initCmds(cmds);

    // set PWM freq
	timerA0Init(10000);

	// example 180deg
	posTarget = 2300;

	// enable global interrupts (SR.GIE bit)
    __enable_interrupt();


    int cmdIndex;

    while(1){
	    __delay_cycles(1000000);            // 50ms delay
	    pidControlLoop(2, 1, 1, 0.01); // Kp, Kd, Ki, dt

        do{
            usciA1UartGets(rxString);
            cmdIndex = parseCmd(cmds, rxString);
            if (cmdIndex != -1){
                if (cmdIndex != QUIT_IDX){
                    executeCmd(cmds, cmdIndex);
                }
            }
            else
                usciA1UartTxString("Invalid command.");
        } while (cmdIndex != QUIT_IDX);


//        if (screenWrite == 1){
//        for (clrLenght = 40; clrLenght != 0; --clrLenght)
//            usciA1UartTxChar(' ');                          // this loop clears the console
//
//        usciA1UartTxChar('\r');                         // returns to beginning of line
//
//        sprintf(speedStr, "posCount = %d, command = %f", posCount, controlCmd);
//        usciA1UartTxString(speedStr);
//
//        screenWrite = 0;                                // reset enabler to write data to screen
	}
}
