/* resched.c - resched */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* ptr to table entry for old process	*/
	struct procent *ptnew;	/* ptr to table entry for new process	*/
	struct procent *pupdate; /* ptr to table entry to update priority */
	struct procent *ptfirstreadyprocess; /* ptr to table entry for first ready process */
	int16 walkready;			/* used to walk ready list starting at first process */
	int16 secondready;          /* used to walk ready list starting at second process */
	
	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	walkready = firstid(readylist);

	if (ptold->prstate == PR_CURR){  /* process remains running */
		if (ptold->prprio > firstkey(readylist)) {
			if(preempt <= 0){ /* increment priority of all ready processes (except NULLPROC) */
				while(queuetab[walkready].qnext != queuetail(readylist)){
					queuetab[walkready].qkey++;
					pupdate = &proctab[walkready];
					pupdate->prprio = queuetab[walkready].qkey;
					kprintf("PID%d changed priority: %d\n", walkready, pupdate->prprio);
					walkready = queuetab[walkready].qnext;
				}
				preempt = QUANTUM;		/* reset time slice for process	*/
				return;
			}
			/* do nothing if quantum hasn't expired */
			else{
				return;
			}
		}
	}
	
	if (ptold->prstate == PR_CURR){  /* process remains running */
	
	/* Old process will no longer remain current */
	ptold->prstate = PR_READY;
	insert(currpid, readylist, ptold->prprio);
	}

	if(queuetab[walkready].qnext != queuetail(readylist)){ /* if first process in ready list not NULLPROC */
		ptfirstreadyprocess = &proctab[walkready]; /* pointer to first process in ready list */
		secondready = queuetab[walkready].qnext; /* PID of second ready process */
		
		/* while second ready process is not NULLPROC */
		while(queuetab[secondready].qnext != queuetail(readylist)){
			/* The priority of second ready process (and after) must be less than the 
			priority of the current process and the first ready process if it is to 
			be incremented. */
			if((queuetab[secondready].qkey < ptold->prprio)&&(queuetab[secondready].qkey < ptfirstreadyprocess->prprio)){
				queuetab[secondready].qkey++;
				pupdate = &proctab[secondready];
				pupdate->prprio = queuetab[secondready].qkey;
				kprintf("PID%d changed priority: %d\n", secondready, pupdate->prprio);
			}
			secondready = queuetab[secondready].qnext;
		}
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}
