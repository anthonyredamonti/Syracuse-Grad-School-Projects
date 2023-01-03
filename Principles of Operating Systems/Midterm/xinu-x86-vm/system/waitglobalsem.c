/* runforever.c - runforever */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  runforever  -  run forever in an infinite while-loop
 *------------------------------------------------------------------------
 */
void waitglobalsem(void)
{
	printf("PID of created process is: %d\n", currpid);
	wait(globalsemaphore);
}
