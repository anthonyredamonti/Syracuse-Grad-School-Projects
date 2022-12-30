/* main.c - main */
#include <xinu.h>
void m1();void m2();void m3();
pid32 m1pid, m2pid, m3pid;

int main(void)
{
    int* count2 = (int*)getmem(64);
	int* count3 = (int*)getmem(64);
	count2[0] = 0;
	count3[0] = 0;
	m1pid=create(m1, 1024, 18,"m1",2,count2,count3);
    m2pid=create(m2, 1024, 15,"m2",2,count2,count3);
	m3pid=create(m3, 1024, 10,"m3",2,count2,count3);
    resume(m1pid);
    resume(m2pid);
	resume(m3pid);
	return OK; 
}

void m1(int* count2, int* count3){
	while(1){
		count2[0] = 0;
		count3[0] = 0;
		kprintf("RUNNING PID: %d\n", currpid);
		sleep(2);
	}
}

void m2(int* count2, int* count3){
	while(1){
		count3[0] = 0;
		if(count2[0] == 0){
			kprintf("RUNNING PID: %d\n", currpid);
			count2[0] = 1;
		}
	}
}

void m3(int* count2, int* count3){
	while(1){
		count2[0] = 0;
		if(count3[0] == 0){
			kprintf("Hooray! RUNNING PID: %d\n", currpid);
			count3[0] = 1;
		}
	}
}
