#include <stdio.h>

/*int tar(long a)
{
    printf("tar: %ld\n", a);
}

int (*bar(double a))(long)
{
    return tar;
}

int (*(*foo(void))(double))(long)
{
    printf("foo\n");

    return bar;
}

int main(void)
{
    int (*(*pf1)(double))(long);
    int (*pf2)(long);

    pf1 = foo();
    pf2 = pf1(0);
    pf2(0);

    getchar();
    return 0;
}*/

//---------------------------------------------------------------------

// typdef ile düzenlenmiş hali

typedef int (*PF1)(long);

int tar(long a)
{
    printf("tar: %ld\n", a);
}

PF1 bar(double a)
{
    return tar;
}

typedef PF1 (*PF2)(double);

PF2 foo(void)
{
    printf("foo\n");

    return bar;
}

int main(void)
{
    PF2 pf2;
    PF1 pf1;
    
    pf2 = foo();
    pf1 = pf2(0);
    pf1(0);

    getchar();
    return 0;
}