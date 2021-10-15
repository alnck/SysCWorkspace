//Özyinelemeli şekilde bir dizin agacını gezme. Ezberlesen Çok iyi olur hatta ezberle.

//-------------------------------------------------------------------------------------

/*
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void WalkDir(LPCSTR lpszPath)
{
    HANDLE hFF;
    WIN32_FIND_DATA wfd;

    if (!SetCurrentDirectory(lpszPath))
        return;
    
    if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (!strcmp(wfd.cFileName, ".")|| !strcmp(wfd.cFileName, ".."))
            continue;

        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
            printf("%s\n", wfd.cFileName);
            WalkDir(wfd.cFileName);
            if (!SetCurrentDirectory(".."))
                goto EXIT;
        }

    } while (FindNextFile(hFF, &wfd));

EXIT:
    FindClose(hFF);
}

int main(void)
{
    WalkDir("E:\\Develop");

    getchar();
    return 0;
}
*/

//---------------------------------------------------------------------------------

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void PutErrMsg(LPCSTR lpszMsg);

void WalkDir(LPCSTR lpszPath)
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if (!SetCurrentDirectory(lpszPath)) {
		PutErrMsg(lpszPath);
		return;
	}

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("%s\n", wfd.cFileName);
			WalkDir(wfd.cFileName);
			if (!SetCurrentDirectory("..")) {
				PutErrMsg("..");
				goto EXIT;
			}
		}
	
	} while (FindNextFile(hFF, &wfd));
EXIT:
	FindClose(hFF);
}

void PutErrMsg(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}
}

int main(void)
{
	WalkDir("c:\\");

    getchar();
	return 0;
}
*/

//------------------------------------------------------------------------------------------

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TABSIZE		4

void PutErrMsg(LPCSTR lpszMsg);

void WalkDir(LPCSTR lpszPath, int level)
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if (!SetCurrentDirectory(lpszPath))
		return;

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("%*s%s\n", level * TABSIZE, "", wfd.cFileName);
			WalkDir(wfd.cFileName, level + 1);
			if (!SetCurrentDirectory(".."))
				goto EXIT;
		}
	
	} while (FindNextFile(hFF, &wfd));
EXIT:
	FindClose(hFF);
}

void PutErrMsg(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}
}

int main(void)
{
	WalkDir("f:\\dropbox\\kurslar\\sysprog-1", 0);

    getchar();
	return 0;
}
*/

//---------------------------------------------------------------------------------------------------------------

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <windows.h>

#define TABSIZE		4

void PutErrMsg(LPCSTR lpszMsg);

void WalkDirRecur(LPCSTR lpszPath, int level)
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;

	if (!SetCurrentDirectory(lpszPath)) {
		printf("%*s:%s:\n", level * TABSIZE, "", lpszPath);
		return;
	}

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			printf("%*s%s\n", level * TABSIZE, "", wfd.cFileName);
			WalkDirRecur(wfd.cFileName, level + 1);
			if (!SetCurrentDirectory(".."))
				goto EXIT;
		}
	
	} while (FindNextFile(hFF, &wfd));
EXIT:
	FindClose(hFF);
}

void WalkDir(LPCSTR lpszPath)
{
	char cwd[MAX_PATH];
	
	if (!GetCurrentDirectory(MAX_PATH, cwd))
		PutErrMsg("GetCurrentDirectory");

	if (_access(lpszPath, 0)) {
		fprintf(stderr, "Path not found: %s\n", lpszPath);
		return;
	}

	WalkDirRecur(lpszPath, 0);

	if (!SetCurrentDirectory(cwd))
		PutErrMsg("SetCurrentDirectory");
}

void PutErrMsg(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}
}

int main(void)
{
	WalkDir("f:\\dropbox\\kurslar\\sysprog-1");

    getchar();
	return 0;
}
*/

//------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <windows.h>

void PutErrMsg(LPCSTR lpszMsg);

BOOL WalkDirRecur(LPCSTR lpszPath, BOOL (*Proc)(const WIN32_FIND_DATA *, int), int level)
{
	HANDLE hFF;
	WIN32_FIND_DATA wfd;
	BOOL result;

	result = TRUE;
	if (!SetCurrentDirectory(lpszPath))
		return;

	if ((hFF = FindFirstFile("*.*", &wfd)) == INVALID_HANDLE_VALUE)
		return;

	do {
		if (!Proc(&wfd, level)) {
			result = FALSE;
			break;
		}
			
		if (!strcmp(wfd.cFileName, ".") || !strcmp(wfd.cFileName, ".."))
			continue;
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (!WalkDirRecur(wfd.cFileName, Proc, level + 1)) {
				result = FALSE;
				break;
			}

			if (!SetCurrentDirectory(".."))
				break;
		}
	
	} while (FindNextFile(hFF, &wfd));

	FindClose(hFF);

	return result;
}

BOOL WalkDir(LPCSTR lpszPath, BOOL (*Proc)(const WIN32_FIND_DATA *, int))
{
	char cwd[MAX_PATH];
	BOOL result;
	
	if (_access(lpszPath, 0)) {
		fprintf(stderr, "Path not found: %s\n", lpszPath);
		return;
	}

	if (!GetCurrentDirectory(MAX_PATH, cwd))
		PutErrMsg("GetCurrentDirectory");

	result = WalkDirRecur(lpszPath, Proc, 0);

	if (!SetCurrentDirectory(cwd))
		PutErrMsg("SetCurrentDirectory");

	return result;
}

void PutErrMsg(LPCSTR lpszMsg)
{
	DWORD dwLastErr = GetLastError();
	LPTSTR lpszErr;

	if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwLastErr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpszErr, 0, NULL)) {
		fprintf(stderr, "%s: %s", lpszMsg, lpszErr);
		LocalFree(lpszErr);
	}
}

BOOL Proc(const WIN32_FIND_DATA *wfd, int level)
{
	printf("%*s%s %s\n", level * 4, "", wfd->cFileName, wfd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "<DIR>" : "");

	if (!_strcmpi(wfd->cFileName, "sample.c"))
		return FALSE;

	return TRUE;
}

int main(void)
{
	BOOL result;

	result = WalkDir("C:\\", Proc);
	
	printf("%s\n", result ? "\nFonksiyon ağacı tamamen dolaştı\n" : "Fonksiyon erken sonlandı\n");

	getchar();
	return 0;
}