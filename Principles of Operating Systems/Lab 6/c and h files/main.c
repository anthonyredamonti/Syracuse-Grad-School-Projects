/* main.c - main */
#include <xinu.h>
void m1();void m2();
pid32 m1pid, m2pid;

void main(void)
{
    m1pid=create(m1, 1024, 40,"m1",0);
    m2pid=create(m2, 1024, 20,"m2",0);
    resume(m1pid);
    resume(m2pid);
    return OK; 
}

void m1(){
	uint32 i;
    umsg32 message[10] = {1,2,3,4,5,6,7,8,9,10};
	kprintf("contents of array before sending: ");
	for(i = 0; i < 10; i++){
		kprintf("%d ", message[i]);
	}
	kprintf("\n");
    sendk(m2pid, message, 10);
}

void m2(){
    int32 i;
    umsg32 *message;
	kprintf("contents of array received: ");
    message = receivek(5);
    for(i = 0; i < 5; i++){
        kprintf("%d ", message[i]);
    }
	freemem(message, 40);
}