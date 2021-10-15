#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define NTHREADS				30
#define MAX_THREAD_NAME			32

void ExitSys(LPCSTR lpszMsg);
DWORD __stdcall ThreadProc(LPVOID lpvParam);
void Read(LPCSTR lpszThreadName);
void Write(LPCSTR lpszThreadName);

SRWLOCK g_srwLock;

int main(void)
{
	HANDLE hThreads[NTHREADS];
	DWORD dwThreadIDs[NTHREADS];
	int i;
	LPCSTR lpszThreadName;
	
	srand(time(NULL));

	InitializeSRWLock(&g_srwLock);

	for (i = 0; i < NTHREADS; ++i) {
		if ((lpszThreadName = (LPCSTR)malloc(MAX_THREAD_NAME)) == NULL) {
			fprintf(stderr, "Cannot allocate memory!..\n");
			exit(EXIT_FAILURE);
		}
		sprintf(lpszThreadName, "Thread-%d", i + 1);

		if ((hThreads[i] = CreateThread(NULL, 0, ThreadProc, lpszThreadName, 0, &dwThreadIDs[i])) == NULL)
			ExitSys("CreateThread");
	}

	WaitForMultipleObjects(NTHREADS, hThreads, TRUE, INFINITE);
	
	return 0;
}


DWORD __stdcall ThreadProc(LPVOID lpvParam)
{
	int i;
	LPCSTR lpszThreadName = (LPCSTR)lpvParam;

	for (i = 0; i < 10; ++i) {
		if (rand() % 2 == 0)
			Write(lpvParam);
		else
			Read(lpvParam);
	}

	free(lpvParam);

	return 0;
}

void Read(LPCSTR lpszThreadName)
{
	AcquireSRWLockShared(&g_srwLock);
	printf("%s READING starts...\n", lpszThreadName);
	Sleep(rand() % 50);
	printf("%s READING ends...\n", lpszThreadName);
	ReleaseSRWLockShared(&g_srwLock);
}

void Write(LPCSTR lpszThreadName)
{
	AcquireSRWLockExclusive(&g_srwLock);
	printf("%s WRITING starts...\n", lpszThreadName);
	Sleep(rand() % 50);
	printf("%s WRINTING ends...\n", lpszThreadName);
	ReleaseSRWLockExclusive(&g_srwLock);
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