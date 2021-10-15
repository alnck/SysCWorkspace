// fgets'i gets gibi kullanma yöntemi. (gets standart c fonksiyonu degil artık)

#include <stdio.h>
#include <string.h>

int main(void)
{
	char s[10];
	char *str;

	if ((str = fgets(s, 10, stdin)) != NULL)
		if ((str = strchr(s, '\n')) != NULL)	
			*str = '\0';

	printf("%c\n", s[1]);		
	puts(s);
	
	getchar();
	return 0;
}