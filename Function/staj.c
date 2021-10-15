#include <stdio.h>

int main(void)
{
	char *s = "ankara";

	*s = 'x';		/* read-only sayfaya erişim! */
    puts(s);

    getchar();
	return 0;
}
