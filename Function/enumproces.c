#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <Psapi.h>

#define NPROC_IDS		1000

void ExitSys(LPCSTR lpszMsg);

int main(void)
{
	DWORD dwProcessIds[NPROC_IDS];
	DWORD dwNeeded;
	DWORD i;

	if (!EnumProcesses(dwProcessIds, sizeof(dwProcessIds), &dwNeeded))
		ExitSys("EnumProcesses");

	for (i = 0; i < dwNeeded / sizeof(DWORD); ++i)
		printf("%lu\n", (unsigned long)dwProcessIds[i]);

	printf("%lu process Ids listed...\n", dwNeeded / sizeof(DWORD));

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

	exit(EXIT_FAILURE);
}