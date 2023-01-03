/*  main.c  - Lab 3 Task 2 */

#include <xinu.h>
#include <stdio.h>

#define MAX_COUNT 15
void producer(int* );
void consumer(int* , int );
int buffer[MAX_COUNT];
int count = 0;
sid32 psem;

int main(int argc, char **argv)
{
	psem = semcreate(MAX_COUNT);
	resume(create(producer, 1024, 40, "prod", 1, buffer));
	resume(create(consumer, 1024, 20, "cons", 2, buffer, MAX_COUNT));
	return OK;
}

void producer(int* buf)
{
	static int data = 0;
	count = 0;
	while (1)
	{
		wait(psem);
		buf[count] = ++data;
		++count;
	}
}

void consumer(int* buf, int bufsize)
{
	int i;
	while (1)
	{
		for (i=0; i<count; ++i)
			kprintf("array[%d] = %d\n", i, buf[i]);
		kprintf("\n");
		sleep(5); // Slows down terminal output for human eyes
		count = 0;
		signaln(psem, bufsize);
	}
}

