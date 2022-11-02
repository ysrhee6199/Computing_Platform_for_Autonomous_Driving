#include "ee.h"
#include "Arduino.h"
#include "serial.h"
#include "Sense.h"
#include "Compute.h"
#include "Actuate.h"/* Model's header file */
#include "rtwtypes.h"


void mdelay(unsigned long delay_ms);

void StartupHook(void)
{
	/* write below your code */
	Sense_initialize();
	Compute_initialize();
	Actuate_initialize();
               /*end*/

    printfSerial("\nOS Begins... ", 0ul);
}

/* Timer1 ISR2 */
ISR2(TimerISR)
{
    static long c = -5;
    IncrementCounter(counter1);
    printfSerial("\n%4ld: ", ++c);
}


/* write below your code */

TASK(Task_Sense) {
	 Sense_step();
	 Compute_U.in = Sense_Y.out;
	 printfSerial(":\t%f\n",  Sense_Y.out);
	 TerminateTask();
};

TASK(Task_Compute) {
	Compute_step();
	Actuate_U.in = Compute_Y.out;
	printfSerial(":\t\t-> %f\n", Compute_Y.out);
	TerminateTask();
};

TASK(Task_Actuate) {
	Actuate_step();
	printfSerial(":\t\t->\t\t-> %f\n", Actuate_Y.out);
	TerminateTask();
};


        /*end*/

