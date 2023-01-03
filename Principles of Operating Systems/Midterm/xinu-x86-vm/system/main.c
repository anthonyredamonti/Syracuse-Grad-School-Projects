/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	uint32 retval;
	pid32 pid1;
	pid32 pid2;
	pid32 pid3;
	pid1 = create(runandend, 1024, 20, "p 1", 0);
	pid2 = create(runandend, 1024, 19, "p 2", 0);
	pid3 = create(runandend, 1024, 18, "p 3", 0);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	globalsemaphore = semcreate(0);
	/* Wait for shell to exit and recreate it */

	recvclr();
	while (TRUE) {
		retval = receive();
		kprintf("\n\n\rMain process recreating shell\n\n\r");
		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	}
	while (1);

	return OK;
}
