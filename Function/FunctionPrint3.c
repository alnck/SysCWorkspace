#include <stdio.h>

void foo(int a, int (*pf)(int))
{
    int result;

    result = pf(a);

    printf("%d\n", result);
}

int bar(int a)
{
    return a * a;
}

int main(void)
{
    foo(10, bar);

    getchar();
    return 0;
}