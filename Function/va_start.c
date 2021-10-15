#include <stdio.h>
#include <stdarg.h>

void vputs(const char *str, ...)    //elipsisten önceki parametreiyi va_start'a verilmeli 2 parametre olarak.
{
    va_list va;
    const char *arg;

    va_start(va, str);

    arg = str;

    for (;;) {
        if (arg == NULL)
            break;
        puts(arg);
        arg = va_arg(va, const char *);
    }

    va_end(va);
}

int main(void)
{
    vputs("ali", "veli", "selami", (char *)NULL);

    getchar();
    return 0; 
}