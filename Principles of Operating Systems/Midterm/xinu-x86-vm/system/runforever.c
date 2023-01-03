/* runforever.c - runforever */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  runforever  -  run forever in an infinite while-loop
 *------------------------------------------------------------------------
 */
void runforever(void)
{
	printf("PID of created process is: %d\n", currpid);
	while(1);
}
