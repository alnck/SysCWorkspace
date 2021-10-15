#include <stdio.h>
#include <stdarg.h>

int myprintf(const char *format, ...)
{
    va_list va;
    int result;
    
    va_start(va, format);

    result = vprintf(format, va);

    va_end(va);

    return result;
}

int main(void)
{
    int a = 10, b = 20, c = 30;

    myprintf("a = %d, b = %d, c = %d", a, b, c);

    getchar();
    return 0; 
}