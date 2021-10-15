#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define FILA_MAPPING_NAME   "SampleFileMappingExample" //Her iki procesde aynı isimli dosya vererek yapılmaktadır. Bu işletim sistemi tarafından haberleşme olacagını anlamaktadır.

void ExitSys(LPCSTR lpszMsg);

// CreateFileMapping fonksiyonu ile haberleşme dosyası oluşturulur.
// MapViewOfFile ile sayfa tablosunda  farklı sanal adreslerle aynı fiziksel adresi gösterecek şekilde ayarlar.
int main(void)
{
    HANDLE hFileMapping;
    LPVOID pvAddr;
	int *pi;
	int i;

    if ((hFileMapping = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 4096, FILA_MAPPING_NAME)) == NULL) // fonksiyon başaraılı olursa açılan dsoyanın handle değerine geri döner. Başarısız olursa NULL döner.
        ExitSys("CreateFileMapping");

    if ((pvAddr = MapViewOfFile(hFileMapping, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 4096 )) == NULL) // Geri dönüş değeri sanal adrestir.
        ExitSys("MapViewOfFile");

	pi = (int *)pvAddr;

	printf("Press ENTER To continue...\n"); 
	getchar();
	
	for (i = 0; i < 1024; ++i)
		printf("%d ", pi[i]);
	printf("\n");
	
	getchar();
    return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastError = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastError,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

    getchar();
	exit(EXIT_FAILURE);
}
