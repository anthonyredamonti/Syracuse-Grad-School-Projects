/* main.c - main */
#include <xinu.h>
void m1();void m2();
sid32 sem1, sem2;
pid32 m1pid, m2pid;

void main(void)
{
    sem1 = semcreate(0); 
    sem2 = semcreate(0);
	m1pid=create(m1, 1024, 21,"m1", 0);
    m2pid=create(m2, 1024, 20,"m2", 0);
    resume(m1pid);
    resume(m2pid);
    return OK; 
}

void m1(){
	signal(sem2);
	wait(sem1);
    kprintf("My first statement appears before Bob's second statement.\n");
    signal(sem2);	
	wait(sem1);
	kprintf("This is Alice's second statment.\n");
}

void m2(){
	signal(sem1);	
	wait(sem2);
	kprintf("My first statement appears before Alice's second statement.\n");
	signal(sem1);
	wait(sem2);
	kprintf("This is Bob's second statment.\n");
}