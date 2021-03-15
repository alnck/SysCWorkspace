#include <stdio.h>

void foo(void)
{
    printf("foo\n");
}

int main(void)
{
    void (*pf)(void);

    pf = &foo;      /* eşdeğeri: pf = foo */

    (*pf)();        /* eşdeğer: pf() */
    
    getchar();
    return 0;
}