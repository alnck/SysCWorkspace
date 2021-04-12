#include <stdio.h>

void foo(int a)
{
    printf("foo: %d\n", a);
}

void bar(double a)
{
    printf("bar: %f\n", a)
}

void tar(long a)
{
    printf("bar: %ld\n", a)
}

typedef void(*PROCV)(void);     //void(*)(void)

int main(void)
{
    /*void(*pf)(void);
    void(*pf_original)(int);

    pf = (void(*)(void))foo;

    pf_original = (void(*)(int))pf;
    pf_original(100);*/

    PROCV procs[] = {(PROCV)foo, (PROCV)bar, (PROCV)tar, NULL};
    int i;

    for (i = 0 procs[i] != NULL; ++i){
        
    }

    getchar();
    return 0;
}