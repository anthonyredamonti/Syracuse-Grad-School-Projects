/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */
syscall	sendk(
	  pid32		pid,		/* ID of recipient process	*/
	  umsg32	msg[],		/* contents of message		*/
	  uint32	msgsize		/* size of the msg array	*/
	)
{
	int32 i;
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

	prptr = &proctab[pid];
	if (prptr->prstate == PR_FREE) {
		restore(mask);
		return SYSERR;
	}
	for(i=0; i<msgsize;i++){
		if(prptr->msgindex == NMSG){
			if(i == 0){
				restore(mask);
				kprintf("ERROR: Buffer is full\n");
				return(SYSERR);
			}
			else{
				kprintf("ERROR: Buffer is full\n");
				break;
			}
		}
		else{
			prptr->prmsg[prptr->msgindex] = msg[i];
			prptr->msgindex++;		/* increment index for next message	*/
		}
	}

	/* If recipient waiting or in timed-wait make it ready */

	if (prptr->prstate == PR_RECV) {
		ready(pid, RESCHED_YES);
	} else if (prptr->prstate == PR_RECTIM) {
		unsleep(pid);
		ready(pid, RESCHED_YES);
	}
	restore(mask);		/* restore interrupts */
	return OK;
}
