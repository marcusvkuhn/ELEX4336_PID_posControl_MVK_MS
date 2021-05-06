#include <msp430.h>
#include <stdlib.h>

#include "pid.h"
#include "quadEncDec.h"
#include "pwmTimerA0.h"
#include "vnh7070API.h"

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

void pidControlLoop(int Kp, int Ki, int Kd, double dt){


    volatile int clamping = 0, sign = 0;    // sign = 1 is positive, sign = -1 is negative;

    posCountDeg = posCount * DEG_PER_PULSE;
    posTargetDeg = posTarget * DEG_PER_PULSE;


    // Control Logic
    error = posTargetDeg - posCountDeg;

    errorInt = errorInt + dt*error;

    errorDeriv = (error-errorPrev)/dt;

    // prototype clamping algorithm

    controlCmd = Kp*error + Ki*errorInt + Kd*errorDeriv;

    // syntax is:
    // result   =   (condition)   ?  (value if true)  :  (value if false)
    // saves value to result

    if(controlCmd >= 0){
        controlCmdAW = (controlCmd > MAX_COMMAND) ? MAX_COMMAND : controlCmd;
        sign = 1;
    }
    else if(controlCmd < 0){
        controlCmdAW = (controlCmd < -MAX_COMMAND) ? MAX_COMMAND : controlCmd;
        sign = -1;
    }

    // compare the two actuator commands

    if (controlCmd != controlCmdAW){
        // checks whether sign of error and control command are equal by XOR
        // if they are both equal (00 or 11), XOR returns 0
        if (!((error > 0) ^ (controlCmd > 0)))
            clamping = 1;
    }

    if (clamping && sign == 1)
        controlCmd = MAX_COMMAND;
    else if(clamping && sign == -1)
        controlCmd = -MAX_COMMAND;

    errorPrev = error;

    if(controlCmd >= 0){
        timerA0DutyCycleSet(abs(controlCmd));
        vnh7070CW(currentDS);
    }
    else if(controlCmd < 0){
        timerA0DutyCycleSet(abs(controlCmd));
        vnh7070CCW(currentDS);
    }

}
