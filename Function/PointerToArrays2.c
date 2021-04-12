/*#include <stdio.h>

void foo(int (*pa)[2], size_t size)
{
	size_t i, k;

	for (i = 0; i < size; ++i) {
		for (k = 0; k < 2; ++k)
			printf("%d ", pa[i][k]);
		printf("\n");
	}
}

int main(void)
{
	int a[3][2] = { {1, 2}, {3, 4}, {5, 6} };

	foo(a, 3);		
    
    getchar();
	return 0;
}*/
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	int (*pa)[2];
	int i, k;

	pa = (int(*)[2]) malloc(5 * sizeof(*pa));
	if (pa == NULL) {
		fprintf(stderr, "cannot allocate memory!..\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < 5; ++i)
		for (k = 0; k < 2; ++k)
			pa[i][k] = i + k;

	for (i = 0; i < 5; ++i) {
		for (k = 0; k < 2; ++k)
			printf("%d ", pa[i][k]);
		printf("\n");
	}

	free(pa);

    getchar();
	return 0;
}