/* checkprio.c - checkprio */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  checkprio  -  Called by clock interrupt handler to update priorities of processes.
 *------------------------------------------------------------------------
 */
void	checkprio(void)
{
	struct	procent	*prptr;		/* pointer to process		*/
	int32	i;			/* index into process table		*/
	for (i = 1; i < NPROC; i++) {
		prptr = &proctab[i];
		/* skip unused slots. Do not increment priority of current process */
		if ((prptr->prstate == PR_FREE)||(prptr->prstate == PR_CURR)) {
			continue;
		}
		/* if process has been current in last 2 seconds, do not increment priority. */
		if(prptr->prdirty == 1){
			prptr->prdirty = 0; /* reset dirty flag */
			continue;
		}
		prptr->prprio++; /* increment priority in process table */
		queuetab[i].qkey = prptr->prprio; /* copy priority to key of process in queuetab */
		kprintf("PID%d changed priority: %d\n", i, prptr->prprio);
	}
	return;
}