#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);
DWORD __stdcall ThreadProc1(LPVOID lpvParam);
DWORD __stdcall ThreadProc2(LPVOID lpvParam);

long g_count;

int main(void)
{
	HANDLE hThread1, hThread2;
	DWORD dwThreadID1, dwThreadID2;


	if ((hThread1 = CreateThread(NULL, 0, ThreadProc1, NULL, 0, &dwThreadID1)) == NULL)
		ExitSys("CreateThread");

	if ((hThread2 = CreateThread(NULL, 0, ThreadProc2, NULL, 0, &dwThreadID2)) == NULL)
		ExitSys("CreateThread");

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	printf("%ld\n", g_count);

    getchar();
	return 0;
}

DWORD __stdcall ThreadProc1(LPVOID lpvParam)
{
	long i;

	for (i = 0; i < 1000000; ++i)
		InterlockedIncrement(&g_count); //long bir nesnesin adresini atomik bir biçimde bir arttırır.
        //InterlockedExchange   : nesneye belli bir değer atamak için kullanılr. Nesnesin önceki değeri ile geri döner.
        //Interlockedadd        : nesneye belli bir değer eklemek için kullanılır. Nesnesin önceki değeri ile geri döner.

	return 0;
}


DWORD __stdcall ThreadProc2(LPVOID lpvParam)
{
	long i;

	for (i = 0; i < 1000000; ++i)
		InterlockedIncrement(&g_count);

	return 0;
}

void ExitSys(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}

	exit(EXIT_FAILURE);
}