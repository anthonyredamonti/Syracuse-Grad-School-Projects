/* main.c - main */
#include <xinu.h>
void m1();void m2();
sid32 sem;
pid32 m1pid, m2pid;
void main(void)
{
    sem = semcreate(20); 
    m1pid=create(m1, 1024, 40,"m1", 0);
    m2pid=create(m2, 1024, 20,"m2", 0);
    resume(m1pid);
    resume(m2pid);
    return OK; 
}

void m1(){
    int32 i;
    for (i = 1; i <= 2000; i++) {
        kprintf("%d ", i); 
        wait(sem); 
    } 
    kill(m2pid);
}

void m2(){
    while(1) { 
        kprintf(" signaler is running ");
        signaln(sem,5);
    }
}