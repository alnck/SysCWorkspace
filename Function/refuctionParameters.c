#include <stdio.h>

void foo(int a)
{
	printf("Giris: a = %d\n", a);

	if (a == 0)
		return;

	foo(a - 1);

	printf("Cikis: a = %d\n", a);
}

int main(void)
{
	foo(5);

    getchar();
	return 0;
}