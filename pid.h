/*
 * pid.h
 *
 *  Created on: Apr 19, 2021
 *      Author: Marcus
 */

#ifndef PID_H_
#define PID_H_

#define MAX_COMMAND 100
#define DEG_PER_PULSE 0.07826086956

void pidControlLoop(int Kp, int Ki, int Kd, double dt);

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

#endif /* PID_H_ */
