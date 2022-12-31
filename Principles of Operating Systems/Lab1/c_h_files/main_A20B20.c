/* main.c - main*/
#include <xinu.h>

void sndA(void), sndB(void);

/* main - Example of creating processes in Xinu */
void main(void)
{
resume(create(sndA, 1024, 20, "p 1", 0));
resume(create(sndB, 1024, 20, "p 2", 0));
}

/* sndA - Repeatedly emit 'A' on console */

void sndA(void)
{
while(1){
putc(CONSOLE, 'A');
}
}
/* sndB - Repeatedly emit 'B' on console */

void sndB(void)
{
while(1){
putc(CONSOLE, 'B');
}
}