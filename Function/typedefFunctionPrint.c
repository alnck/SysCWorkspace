#include <stdio.h>

void foo(void)
{
    printf("foo\n");
}

typedef void (*PF)(void);

int main(void)
{
    PF pf;      /* void (*p)(void) pf; */

    pf = foo;
    pf();

    getchar();
    return 0;
}