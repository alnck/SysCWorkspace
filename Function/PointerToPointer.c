#include <stdio.h>

/*int main(void)
{
	int a = 10;
	int *pi;
	int **ppi;

	pi = &a;
	ppi = &pi;

	printf("%d\n", **ppi);

	**ppi = 20;
	printf("%d\n", a);

    getchar();
	return 0;
}
#include <stdio.h>*/

int main(void)
{
	char *names[] = { "ali", "veli", "selami" };
	char **str;

	str = names;

	puts(*str);

	++str;

	puts(*str);

	++str;

	puts(*str);

    getchar();
	return 0;
}