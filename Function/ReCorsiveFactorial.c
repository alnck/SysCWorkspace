/*#include <stdio.h>

unsigned long factorial(int n)
{
	unsigned long f = 1;
	int i;

	for (i = 2; i <= n; ++i)
		f *= i;

	return f;
}

int main(void)
{
	unsigned long result;

	result = factorial(2);
	printf("%lu\n", result);
    
    getchar();
	return 0;
}*/

//-------------------------------------------------------------------

#include <stdio.h>

unsigned long long factorial(int n)
{
	if (n == 0)
		return 1;

    return n * factorial(n - 1);
}

int main(void)
{
	unsigned long long result;

	result = factorial(6);
	printf("%llu\n", result);

    getchar();
	return 0;
}