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

/*#include <stdio.h>

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
}*/

//----------------------------------------------------

/*#include <stdio.h>

void revstr(char *str)
{
	size_t n, i;
	char temp;

	for (n = 0; str[n] != '\0'; ++n)
		;

	for (i = 0; i < n / 2; ++i) {
		temp = str[n - 1 - i];
		str[n - 1 - i] = str[i];
		str[i] = temp;
	}
}

int main(void)
{
	char s[] = "ankara";
	
	revstr(s);
	puts(s);

    getchar();
	return 0;
}*/

//-----------------------------------------------------------

/*#include <stdio.h>
#include <string.h>

void revstr(char *str, size_t left, size_t right)
{
	char temp;

	while (left < right) {
		temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		++left, --right;
	}
}

int main(void)
{
	char s[] = "ankara";
	
	revstr(s, 0, strlen(s) - 1);
	puts(s);

	getchar();
	return 0;
}*/

//---------------------------------------------------------------------

/*#include <stdio.h>
#include <string.h>

void revstr(char *str, size_t left, size_t right)
{
	char temp;

	while (left >= right)
		return;
	
	temp = str[left];
	str[left] = str[right];
	str[right] = temp;

	revstr(str, left + 1, right - 1);
}

int main(void)
{
	char s[] = "ankara";
	
	revstr(s, 0, strlen(s) - 1);
	puts(s);

	getchar();
	return 0;
}*/

//------------------------------------------------------------------------

#include <stdio.h>

void revstr_recur(char *str, size_t left, size_t right)
{
	char temp;

	while (left >= right)
		return;
	
	temp = str[left];
	str[left] = str[right];
	str[right] = temp;

	revstr_recur(str, left + 1, right - 1);
}

void revstr(char *str)
{
	size_t i;

	for (i = 0; str[i] != '\0'; ++i)
		;

	revstr_recur(str, 0, i - 1);
}

int main(void)
{
	char s[] = "ankara";
	
	revstr(s);
	puts(s);

	getchar();
	return 0;
}