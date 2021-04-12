/*#include <stdio.h>

void putsrev(const char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; ++i)
		;

	for (--i; i >= 0; --i)
		putchar(str[i]);

	putchar('\n');
}


int main(void)
{
	putsrev("ankara");

    getchar();
	return 0;
}*/

//--------------------------------------------------

#include <stdio.h>

void putsrev(const char *str)
{
	if (*str == '\0')
		return;

	putsrev(str + 1);
	putchar(*str);
}

int main(void)
{
	putsrev("ankara");
	putchar('\n');

    getchar();
	return 0;
}