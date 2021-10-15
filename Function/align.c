#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*#pragma pack(1)*/ // arada boşluk bırakmıyor pedingleri atlıyor.

struct BITMAP_HEADER{
    char magic[2];      /*2 byte*/
    uint32_t size;      /*4 byte*/
    uint16_t reserved1; /*2 byte*/
    uint16_t reserved2; /*2 byte*/
    uint32_t dataloc;   /*4 byte*/

};

/*int main(void)
{
    FILE *f;
    struct BITMAP_HEADER bh;

    if ((f = fopen("Test.bmp", "rb")) == NULL) {
        fprintf(stderr, "Cannot open file!..\n");
        getchar();
        exit(EXIT_FAILURE);
    }

    fread(&bh, sizeof(struct BITMAP_HEADER), 1, f);

    printf("Magic: %C%C", bh.magic[0], bh.magic[1]);
    printf("%u\n", bh.size);
    printf("%u\n", bh.dataloc);

    fclose(f);

    getchar();
    return 0;
}*/

/*
struct SAMPLE {
    int a;
    char b;
    int c;
};

int main(void)
{
    printf("%u\n", sizeof(struct SAMPLE));
    
    getchar();
    return 0;
}*/

struct something1 {
    char a;
    int b;
    char c;
    int d;
};

struct something2 {
    char a;
    char c;
    int b;
    int d;
};

int main(void)
{
    struct something1 s1;
    struct something2 s2;

    printf("Birinci sirali: %u\n", sizeof(s1));
    printf("ikinci sirali: %u\n", sizeof(s2));

    size_t a = _Alignof(double); // duouble için kaç byte lazımdır.
    printf("gerekli byte: %u\n", a);

    getchar();
    return 0;
}