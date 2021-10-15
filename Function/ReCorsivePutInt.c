/*#include <stdio.h>
#include <math.h>

void putint(int n)
{
    char s[32];
    int i, nflag;
    
    if (n < 0){
        n = -n;
        nflag = 1;
    }

    i = (int)log10(n) + 1 + nflag;
    s[i--] = '\0';

    while (n) {
    s[i--] = n % 10 + '0';
    n /= 10;
}
    for (i = 0; s[i] != '\0'; i++)
    {
        putchar(s[i]);
    }
    putchar('\n');
}

int main(void)
{
    putint(9999);

    getchar();
    return 0;
}*/

//-----------------------------------------------------------

#include <stdio.h>

void putint(int n)
{
    if (n < 0){
        n = -n;
        putchar('-');
    }
 
    if (n / 10){
        putint(n / 10);
    }
    putchar(n % 10 + '0');
}

int main(void)
{
    putint(-1234);

    getchar();
    return 0;
}