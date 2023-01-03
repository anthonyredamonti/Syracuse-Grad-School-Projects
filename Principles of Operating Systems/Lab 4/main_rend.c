/* main.c - main */
#include <xinu.h>

void m(sid32, sid32, int);
int coin_flip();

static char* messages[2][2] = {
    {"A1 ", "A2 "},
    {"B1 ", "B2 "}
    };
static int flip1;
static int flip2;
static int index = -1;
static int rand_table[8] = {
    0, 0,
    0, 1,
    1, 0,
    1, 1
    };

int main(void)
{
    int i;
    for (i=0; i<4; ++i)
    {
        worker();
        kprintf("\n");
    }
    return OK;
}

void worker()
{
    flip1 = coin_flip();
    flip2 = coin_flip();

    sid32 sem1 = semcreate(0);
    sid32 sem2 = semcreate(0);

    resume(create(m, 1024, 21, "m1", 3, sem1, sem2, 0));
    resume(create(m, 1024, 21, "m2", 3, sem2, sem1, 1));
}

int coin_flip()
{
    ++index;
    if (index == 8)
        index = 0;
    return rand_table[index];
}

void m(sid32 s1, sid32 s2, int proc)
{
    if (flip1 == proc)
        signal(s1);

    wait(s1);
    kprintf("%s", messages[proc][0]);
    signal(s2);

    wait(s1);
    if (flip2 == proc)
        signal(s1);
    else
        signal(s2);

    wait(s1);
    kprintf("%s", messages[proc][1]);
    signal(s2);
    if (flip2 == proc)
        signal(s2);
}
