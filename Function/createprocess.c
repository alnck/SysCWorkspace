#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	char szPath[] = "C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe";
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	PROCESS_INFORMATION pa;

	if (!CreateProcess("C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe", szPath, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pa))
		ExitSys("CreateProcess");

	printf("Ok\n");

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