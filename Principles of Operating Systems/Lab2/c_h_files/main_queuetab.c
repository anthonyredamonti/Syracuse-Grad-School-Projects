/* main.c - main*/
#include <xinu.h>

void procA(void), procB(void), procC(void);

/* main - Example of creating processes in Xinu */
void main(void)
{
resume(create(procA, 1024, 20, "p 1", 0));
resume(create(procB, 1024, 20, "p 2", 0));
resume(create(procC, 1024, 20, "p 3", 0));
int i = 0;
while(i < NQENT){
    kprintf("i: %d, Key: %d, Prev: %d, Next: %d\n", i, queuetab[i].qkey, queuetab[i].qprev, queuetab[i].qnext);
    i++;
}
}

void procA(void)
{
	while(1);
}

void procB(void)
{
	while(1);
}

void procC(void)
{
	while(1);
}