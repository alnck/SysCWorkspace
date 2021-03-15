#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE        4096

int main(void)
{
    FILE *f;
    char line[MAX_LINE];
    char *str;

    if ((f = fopen("test.csv", "r")) == NULL)
    {
        fprintf(stderr, "cannot open file!..\n");
        exit(EXIT_FAILURE);
    }
    
    while (fgets(line, MAX_LINE, f) != NULL){
        if ((str = strchr(line, '\n') != NULL))
        if (*str == '\n')
            *str = '\0';

        for (str = strtok(line, ","); str != NULL; str = strtok(NULL, ","))
            {
                printf("%s", str);
            }
            printf("\n");
    }

    fclose(f);

    getchar();
    return 0;
}