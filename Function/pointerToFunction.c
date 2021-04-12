#include <stdio.h>

void foo(int a)
{
	printf("foo: %d\n", a);
}

int main(void)
{
	void *pv;
	void (*pf)(int) = foo;		/* geçerli */

	pv = *(void **)&pf;			/* kandırmaca yol, ama standart bakımından geçerli */
	/* ... */

    getchar();
	return 0;
}