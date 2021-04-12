#include <stdio.h>

int main(void)
{
    int s[3][2];

    int (*p)[2];

    p = s;
//----------------------------------------------------------
    int a[2] = {10, 20};
    int (*pia)[];
    int val;

    pia = &a;

    val = (*pia)[0];
    printf("%d\n", val);

    val = (*pia)[1];
    printf("%d\n", val);
//------------------------------------------------------------
printf("------------------------------------------------------");

    int b[3][2] = { {1, 2}, {3, 4}, {5, 6} };
    int (*pa)[2];

    pa = b;

    printf("%d\n", (*pa)[0]);
    printf("%d\n", (*pa)[1]);
    
    printf("%d\n", pa[1][0]);
    printf("%d\n", pa[1][1]);
    
    printf("%d\n", pa[2][0]);
    printf("%d\n", pa[2][1]);

    getchar();
    return 0;
}