/*#include <stdio.h>

void binprint(unsigned int n)
{
	int i;

	for (i = sizeof(n) * 8 - 1; i >= 0; --i)
		if (n >> i & 1)
			break;

	for (; i >= 0; --i)
		putchar((n >> i & 1) + '0');
	putchar('\n');
}

int main(void)
{
	binprint(21);

    getchar();
	return 0;
}*/

//---------RECOrESİVE------------------

#include <stdio.h>

void binprint(unsigned int n)
{
	if (n == 0)
		return;
	binprint(n >> 1);
	putchar((n & 1) + '0');
}

int main(void)
{
	binprint(21);

    getchar();
	return 0;
}