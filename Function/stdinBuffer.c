#include <stdio.h>

void clear_stdin(void)
{
	int ch;

	while ((ch = getchar()) != '\n' && ch != EOF)
		;
}

int main(void)
{
	int ch;

	ch = getchar();
	printf("%c\n", ch);
	
	clear_stdin();
	
	ch = getchar();
	printf("%c\n", ch);
    
	return 0;
}