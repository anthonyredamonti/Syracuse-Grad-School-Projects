/* main.c - main */
#include <xinu.h>
void m1();void m2();
sid32 sem;
pid32 m1pid, m2pid;
int32 array[15];

void main(void)
{
    sem = semcreate(15); 
    m1pid=create(m1, 1024, 40,"m1", 0);
    m2pid=create(m2, 1024, 20,"m2", 0);
    resume(m1pid);
    resume(m2pid);
    return OK; 
}

void m1(){
    int32 i;
	int32 count = 0;
    for (i = 1; i <= 2000; i++) {
        wait(sem); 
		array[count] = i;
		if(++count == 15){
			count = 0;
		}
    } 
    kill(m2pid);
}

void m2(){
	int32 j;
	while(1) { 
		for(j = 0; j < 15; j++){
			kprintf("array[%d] = %d\n", j, array[j]);
		}
        signaln(sem,15);
    }
}