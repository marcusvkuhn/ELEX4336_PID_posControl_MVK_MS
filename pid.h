/*
 * pid.h
 *
 *  Created on: Apr 19, 2021
 *      Author: Marcus
 */

#ifndef PID_H_
#define PID_H_

#define ACLKFREQ 32786

#define MAX_COMMAND 65535

void initPidTimerA1(int freq);
void pidControlLoop(int Kp, int Kd, int Ki, int dt);

volatile int posDelta,
             //Kp, Kd, Ki,
             antiWindup;

volatile double error,
                controlCmd,
                controlCmdAW,
                errorInt,
                errorDeriv,
                errorPrev,
                dt;

//volatile int control_type = 10;
//volatile int antiWindup;
//volatile int btnFlag = 0;

#endif /* PID_H_ */
