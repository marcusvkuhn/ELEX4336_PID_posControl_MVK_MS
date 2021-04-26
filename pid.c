#include <msp430.h>
#include <stdlib.h>

#include "pid.h"
#include "quadEncDec.h"

/*
 * pid.c
 *
 *  Created on: Apr 19, 2021
 *      Author: Marcus
 */

//void initPidTimerA1(int freq){
//    volatile int m, validPwmFreq = -1;
//
//    // TA1CCTL0, use ACLK (32786hz), /1, up mode, clear and enable interrupts.
//    TA1CTL = TASSEL_1 | ID__1 | MC_1 | TACLR | TAIE;
//    TA1EX0 |= TAIDEX_0;    // expansion clk divider to 1
//
//    // find m value for given freq
//    m = (int)(ACLKFREQ/freq);
//
//    /* write m to TA1CCR0,
//     timer will count up it and trigger an interrupt to set control loop up update rate */
//    if(m >= 9 && m <= 65356)
//        TA1CCR0 = m - 1;
//}

void pidControlLoop(int Kp, int Ki, int Kd, int dt){

    volatile int clamping = 0;

    // Control Logic
    error = posDelta - posCount;

    errorDeriv = (error-errorPrev)/dt;

    errorInt = errorInt + dt*1*error;

    // prototype clamping algorithm

    controlCmd = Kp*error + Ki*errorInt + Kd*errorDeriv;

    // syntax is:
    // result   =   (condition)   ?  (value if true)  :  (value if false)
    // saves value to result

    controlCmdAW = (abs(controlCmd) > MAX_COMMAND) ? MAX_COMMAND : controlCmd;

    // compare the two actuator commands

    if (controlCmd != controlCmdAW){
        // checks whether sign of error and control command are equal by XOR
        // if they are both equal (00 or 11), XOR returns 0
        if (!((error > 0) ^ (controlCmd > 0)))
            clamping = 1;
    }

    if (clamping)
        controlCmd = MAX_COMMAND;

    // Anti-windup
//    if(abs(controlCmd) >= MAX_COMMAND && (((error >= 0) && (errorInt >= 0)) || ((error < 0) && (errorInt < 0)))){
//
//        if(antiWindup)
//            errorInt = errorInt;
//        else  // If no antiwindup
//            errorInt = errorInt + dt*1*error;  // rectangular integration
//        //P1OUT &= ~BIT0;
//    }
//    else
//    {
//        errorInt = errorInt + dt*1*error;  // rectangular integration
//        //P1OUT |= BIT0;
//    }

    errorPrev = error;

//    if(controlCmd >= 0){
//        // change to vnh7070 functions
//        setDIR(0);
//        setPWM(abs(controlCmd));
//    }
//    else{
//        // change to vnh7070 functions
//        setDIR(1);
//        setPWM(abs(controlCmd));
//    }

//    if(abs(controlCmd) < MAX_COMMAND)
//        //P1OUT &= ~BIT0;
//    else
//        //P1OUT |= BIT0;
//
}
