/* runandend.c - runandend */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  runandend  -  print PID and terminate process
 *------------------------------------------------------------------------
 */
void runandend(void)
{
	printf("PID of created process is: %d\n", currpid);
}
