#include <stdio.h>
#include <string.h>

/*char *mystrtok(char *str, const char *delim)
{
    static char *pos;
    char *beg;

    if (str != NULL)
    {
        pos = str;
    }

    while (*pos != '\0' && strchr(delim, *pos) != NULL)
    {
        ++pos;
    }
    if (*pos == '\0')
        return NULL;

    beg = pos;

    while (*pos != '\0' && strchr(delim, *pos) == NULL)
    {
        ++pos;
    }
    if (*pos != '\0')
    {
        *pos++ = '\0';
    }
    
    return beg;

}*/

char *mystrtok(const char *str, const char *delim, char *dest)
{
    static const char *pos;
    const char *beg;

    if (str != NULL)
    {
        pos = str;
    }

    while (*pos != '\0' && strchr(delim, *pos) != NULL)
    {
        ++pos;
    }
    if (*pos == '\0')
        return NULL;

    beg = pos;

    while (*pos != '\0' && strchr(delim, *pos) == NULL)
    {
        ++pos;
    }

    strncpy(dest, beg, pos - beg); //strcpy n kadar kopyala demek: nereye kopyala 'dest'e neyi 'beg'i ne kadar 'pog -beg' kadar
    dest[pos -beg] = '\0';

    return dest;

}

int main(void)
{
    char text[] = ",,,,,,,,,ali,,,,,,,veli,,,,,,,selami";
    char str[100];
    char *pstr;
    
    
    for (pstr = mystrtok(text, ",", str); pstr != NULL; pstr = mystrtok(NULL, ",", str))
    {
        puts(pstr); 
    }

    getchar();
    return 0;
}