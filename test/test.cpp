// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <Windows.h>  
#include <tchar.h>  
#include <iostream>  
using namespace std;
int _tmain(int argc, _TCHAR* argv[]) {
	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;
	HANDLE filehandle;
	TCHAR ID[] = TEXT("Local\\sharedmemory");
	char* memory;
	if (argc == 1)
	{
		filehandle = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, ID);
		memory = (char*)MapViewOfFile(filehandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		sprintf_s(memory, 1024, "%s", "Data from first process");
		cout << "First process:" << memory << endl;
		ZeroMemory(&process_info, sizeof(process_info));
		ZeroMemory(&startup_info, sizeof(startup_info));
		startup_info.cb = sizeof(startup_info);

		wchar_t cmdline[256];
		wsprintf(cmdline, L"\"%s\" Child\n", argv[0]);
		CreateProcessW(argv[0], cmdline, 0, 0, 0, 0, 0, 0, &startup_info, &process_info);
		WaitForSingleObject(process_info.hProcess, INFINITE);

		UnmapViewOfFile(memory);
		CloseHandle(filehandle);
	}
	else {
		filehandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, 0, ID);
		memory = (char*)MapViewOfFile(filehandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		cout << "Second process: " << memory;
		UnmapViewOfFile(memory);
		CloseHandle(filehandle);
	}
	getchar();
	return 0;
}

