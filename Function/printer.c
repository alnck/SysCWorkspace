#include <stdio.h>
#include <stdarg.h>

void printerr(const char * format, ...)
{
    va_list va;

    va_start(va, format);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, format, va);

    va_end(va);
}

int main(void)
{
    int errcode = 123;

    printerr("%d\n", errcode);

    getchar();
    return 0;
}