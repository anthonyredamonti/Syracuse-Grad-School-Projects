/* main.c - main */
#include <xinu.h>
void m1();void m2();void m3();
pid32 m1pid, m2pid, m3pid;

void main(void)
{
	int16 walkready;
	walkready = firstid(readylist);
	kprintf("first id: %d\n", walkready);
	kprintf("priority: %d\n", queuetab[walkready].qkey);

	walkready = lastid(readylist);
	kprintf("last id: %d\n", walkready);
	kprintf("priority: %d\n", queuetab[walkready].qkey);

	
	/*
    m1pid=create(m1, 1024, 40,"m1",0);
    m2pid=create(m2, 1024, 35,"m2",0);
	m3pid=create(m3, 1024, 25,"m3",0);
    resume(m1pid);
    resume(m2pid);
    */
	return OK; 
}

void m1(){
	kprintf("PID: %d", currpid);
	while(slnonempty){};
	sleep(2);
}

void m2(){
	kprintf("PID: %d", currpid);
	while(slnonempty){};
	sleep(2);
}

void m3(){
	kprintf("PID: %d", currpid);
	while(slnonempty){};
	sleep(2);
}
