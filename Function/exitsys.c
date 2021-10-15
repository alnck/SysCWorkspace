#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdring.h>

void exit_sys(const char *format, ...);

int main (int argc, char *argv[])
{
    int fd;
    if (argc != 2) {
        fprintf(stderr, "wrong number of arguments!..\n");
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argc[1], O_RDONLY)) == -1)
        exit_sys("Error open file %s\n", argv[1]);

    close(fd);

    return 0;
}

void exit_sys(const char *format, ...)
{
    va_list va;

    va_start(va, format);
    
    vfprintf(stderr, format, va);
    fprintf(stderr, ": %s\n", strerror(errno));

    va_end(va);

    exit(EXIT_FAILURE);
}