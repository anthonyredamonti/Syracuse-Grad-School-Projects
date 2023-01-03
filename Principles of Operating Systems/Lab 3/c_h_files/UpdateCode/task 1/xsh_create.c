/* lab3 task 1 - shell command assignment */

#include <xinu.h>

void child_func(int);
int read_int(char*, int*);

/*------------------------------------------------------------------------
 * xsh_create - shell command to create a process
 *------------------------------------------------------------------------
 */
shellcmd xsh_create(int nargs, char* args[])
{
	int prio = 20;
	char* pname = "create-child";
	int behavior = 1;

	/* Output info for '--help' argument */
	if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
		printf("Usage: %s [Priority] [Looping]\n\n", args[0]);
		printf("Description:\n");
		printf("\tcreates a process\n");
		printf("Options:\n");
		printf("\tPriority \tthe priority of a process to create\n");
		printf("\t\t\tIf no priority provided, a default value\n");
		printf("\t\t\tof 20 is used\n");
		printf("\tLooping \t0 means process will terminate\n");
		printf("\t\t\t1 means process will run forever\n");
		printf("\t--help\tdisplay this help and exit\n");
		return OK;
	}

	/* Read in priority parameter */
	if (nargs > 1)
		read_int(args[1], &prio);

	/* Read in looping parameter */
	if (nargs > 2)
		read_int(args[2], &behavior);

	if (prio < 1)
	{
		kprintf("invalid priority: %d\n", prio);
		restore(mask);
		return SYSERR;
	}

	/* Create child process */
	kprintf("Creating process= %s\n", pname);
	kprintf("Priority= %d\n", prio);
	kprintf("Run forever= %d\n", behavior!=0);
	resume(create(child_func, 1024, prio, pname, 1, behavior));

	return OK;
}

/* Reads an integer from a string, similar to sscanf(s, "%d", &i) */
int read_int(char* s, int* val)
{
	int first = 1;
	int i = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			if (first)
			{
				*val = 0;
				first = 0;
			}
			*val = ((*val) * 10) + (s[i] - '0');
		}
		else
		{
			break;
		}
		++i;
	}
	if (first)
		return 0;
	return 1;
}

/* function for child process */
void child_func(int run_forever)
{
    printf("Inside the child process PID=%d\n", getpid());
	if (run_forever)
		while (1);
}
