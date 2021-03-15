#include <stdio.h>
#include <string.h>

/*int main(void)
{
    char s[] = {"Ali,    Veli  ,  Selami     "};
    char *pstr;
    
    
    for (pstr = strtok(s, ", "); pstr != NULL; pstr = strtok(NULL, ", "))
    {
        puts(pstr);
    }
    
    /*puts(pstr); 

    pstr = strtok(NULL, ", ");
    puts(pstr);*//*

    getchar();
    return 0;

}*/

int main(void)
{
    char s[] = "12/11/2009";
    char *pstr;
    
    
    for (pstr = strtok(s, "/"); pstr != NULL; pstr = strtok(NULL, "/"))
    {
        puts(pstr); 
    }

    getchar();
    return 0;
}