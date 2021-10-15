#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void ExitSys(LPCSTR lpszMsg);
DWORD __stdcall ThreadProc1(LPVOID lpvParam);
DWORD __stdcall ThreadProc2(LPVOID lpvParam);
void DoMachine(LPCSTR szName);

HANDLE g_hSemaphore;

int main(void)
{
	HANDLE hThread1, hThread2;
	DWORD dwThreadID1, dwThreadID2;
	
	srand(time(NULL));

	if ((g_hSemaphore = CreateSemaphore(NULL, 1, 1, NULL)) == NULL)
		ExitSys("CreateSemaphore");

	if ((hThread1 = CreateThread(NULL, 0, ThreadProc1, NULL, 0, &dwThreadID1)) == NULL)
		ExitSys("CreateThread");

	if ((hThread2 = CreateThread(NULL, 0, ThreadProc2, NULL, 0, &dwThreadID2)) == NULL)
		ExitSys("CreateThread");

	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	CloseHandle(g_hSemaphore);

    getchar();
	return 0;
}

DWORD __stdcall ThreadProc1(LPVOID lpvParam)
{
	int i;

	for (i = 0; i < 10; ++i) 
		DoMachine("Thread1");
	
	return 0;
}

DWORD __stdcall ThreadProc2(LPVOID lpvParam)
{
	int i;

	for (i = 0; i < 10; ++i)
		DoMachine("Thread2");

	return 0;
}

void DoMachine(LPCSTR lpszName)
{
	WaitForSingleObject(g_hSemaphore, INFINITE);
	printf("-----------------\n");
	printf("1) %s\n", lpszName);
	Sleep(rand() % 500);
	printf("2) %s\n", lpszName);
	Sleep(rand() % 500);
	printf("3) %s\n", lpszName);
	Sleep(rand() % 500);
	printf("4) %s\n", lpszName);
	Sleep(rand() % 500);
	printf("5) %s\n", lpszName);
	Sleep(rand() % 500);
	ReleaseSemaphore(g_hSemaphore, 1, NULL);
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

    getchar();
	exit(EXIT_FAILURE);
}