/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32*	receivek(uint32 numofmsgs)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32*	msg;			/* message to return		*/
	int32 i;
	uint32 bytesneeded = 8 * numofmsgs;

	mask = disable();
	prptr = &proctab[currpid];

	msg = (umsg32*)getmem(bytesneeded);

	for(i = 0; i < numofmsgs; i++){
		if (prptr->msgindex == 0) {
			prptr->prstate = PR_RECV;
			resched();		/* block until all messages arrive	*/
		}
		msg[i] = prptr->prmsg[prptr->msgindex-1];		/* retrieve message		*/
		if(prptr->msgindex > 0){
			prptr->msgindex--;	/* if messages present, decrement message index for next message	*/
		}
	}
	restore(mask);
	return msg;
}
