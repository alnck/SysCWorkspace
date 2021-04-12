//Fonksiyon adresine geri dönen fonskiyon
#include <stdio.h>
int bar(int a)
{
    printf("bar: %f\n", a);
}

int (*foo(void)) (double)
{
    return bar;
}

int main(void)
{
    int (*pf)(double);

    pf = foo();

    pf(1.2);
    
    getchar();
    return 0;
}
//int (*foo(void)) (double) // geri dönüş değeri bir fonksiyon olması için bu satırda * atomu parantez içine alınır.
//sol tarafına dönülecek fonksiyonun geri dönüş degeri. sagına fonksiyonun parametre türü yazılır.

//foo(void)     :
//*foo(void)    : geri dönüşü bire adres demek.
//(*foo(void))  : geri dönüş değeri bir fonksiyon adresi demek.