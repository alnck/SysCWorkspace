#include <stdio.h>
#include <stdarg.h>

// Printf fonksiyonunun nasıl yazılmış oldugunu anlamak adına (fikir vermesi için) yapılmıştır.

int myprintf(const char *format, ...)
{
    va_list va;
    int argi;
    double argd;
    char argc;
    int count;

    va_start(va, format);
    count = 0;

    while (*format != '\0') {
        if (*format == '%')
            switch (*++format){
                case 'd':
                    argi = va_arg(va, int);
                    count += printf("%d", argi);
                    break;
                case 'f':
                    argd = va_arg(va, double);
                    count += printf("%f", argd);
                    break;
                case 'c':
                    argc = va_arg(va, int);
                    count +=printf("%c", argc);
                    break;
            }
        else {
            putchar(*format);
            ++count;
        }
        ++format;
    }

    va_end(va);
    return count;
}

int main(void)
{
    int a = 123;
    double b = 12.3;
    char c = 'x';
    int result;
    
    myprintf("a = %d, b = %f, c = %c", a, b, c);
    printf("\n");
    printf("%d\n", result);

    getchar();
    return 0;
}