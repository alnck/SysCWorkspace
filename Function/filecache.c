#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "filecache.h"

HCACHE open_file(conts char *path, int flags)
{
    HCACHE *hc;

    if ((hc = (HCACHE)malloc(sizeof(CACHE))) == NULL)
        return NULL;

    if ((hc->fd = open(path, flags)) == -1){
        free(hc);
        return NULL;
    }
}