/*
 * pid.h
 *
 *  Created on: Apr 19, 2021
 *      Author: Marcus
 */

#ifndef PID_H_
#define PID_H_

#define ACLKFREQ 32786

#define MAX_COMMAND 100
#define DEG_PER_PULSE 0.07826086956

void initPidTimerA1(int freq);
void pidControlLoop(int Kp, int Kd, int Ki, double dt);

volatile int posTarget,
             //Kp, Kd, Ki,
             antiWindup;

volatile double error,
                controlCmd,
                controlCmdAW,
                errorInt,
                errorDeriv,
                errorPrev,
                dt,
                posCountDeg,
                posTargetDeg;

//volatile int control_type = 10;
//volatile int antiWindup;
//volatile int btnFlag = 0;

#endif /* PID_H_ */
