#include <stdio.h>

char *mygets(char *str)
{
	int ch;
	size_t i;

	for (i = 0; (ch = getchar()) != '\n' && ch != EOF; ++i)
		str[i] = ch;



	str[i] = '\0';

	return i == 0 && ch == EOF ? NULL : str;
}

int main(void)
{
	char s[100];
	
	mygets(s);
	puts(s);

    getchar();
	return 0;
}