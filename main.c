#include <msp430.h>

#include "quadEncDec.h"
#include "pid.h"


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	initEncDec();
	initPidTimerA1(100);

	while(1){
	    // if updateTime == 1
	    pidControlLoop(500, 375, 25, 0.01);
	}

	return 0;
}
