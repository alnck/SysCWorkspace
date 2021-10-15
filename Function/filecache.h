#ifndef FILECACHE_H_
#define FILECACHE_H_

/* Symbolic Constants*/

#define NCACHE_LINES   50
#define LINE_SIZE      30

/*Type Definitions */

typedef struct tagCACHELINE {
    char buf[LINE_SIZE];
    size_t offset;
}  CACHE_LINE;

typedef struct tagCACHEE {
    int fd;
    CACHE_LINE clines[NCACHE_LINES];
} CACHE, *HCACHE;

/* Function Prototypes */

HCACHE_FILE open_file(conts char *path, int flags, mode_t mode);

#endif