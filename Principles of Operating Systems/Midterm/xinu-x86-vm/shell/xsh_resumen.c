/* xsh_resumen.c - xsh_resumen */

#include <xinu.h>
#include <stdio.h>
#include <string.h>

/*------------------------------------------------------------------------
 * xsh_resumen - shell command to resume processes
 *------------------------------------------------------------------------
 */
shellcmd xsh_resumen(int nargs, char *args[])
{
	pid32	pid;	    /* process priority > 0		*/
	char	ch;				/* next character of argument	*/
	char	*chptr;			/* walks along argument string	*/
	int32	i;

	/* Output info for '--help' argument */

	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s Priority\n\n", args[0]);
		printf("Description:\n");
		printf("\tcreates a process\n");
		printf("Options:\n");
		printf("\tPriority \tthe priority of a process to create\n");
		printf("\t\t If no priority provided, a default value\n");
		printf("\t\t of 20 is used\n");
		printf("\t--help\tdisplay this help and exit\n");
		return OK;
	}

	/* Check argument count */

	if (nargs < 2) {
		fprintf(stderr, "%s: incorrect argument\n", args[0]);
		fprintf(stderr, "Try '%s --help' for more information\n", args[0]);
		return SYSERR;
	}

	/* compute priority from argument string */
	for(i = 0; i < nargs-1; i++){	
		chptr = args[1];
		ch = *chptr++;
		pid = 0;
		while(ch != NULLCH) {
			if ( (ch < '0') || (ch > '9') ) {
				fprintf(stderr, "%s: non-digit in process ID\n",
					args[0]);
				return 1;
			}
			pid = 10*pid + (ch - '0');
			ch = *chptr++;
		}
		resume(pid);
	}
	return 0;
}
