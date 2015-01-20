// SecuTalk.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "deklaracje.h"
#include "SockNet.h"

extern DWORD WINAPI connect_thread_func(LPVOID lpParam);


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE WINAPI threadhandle = CreateThread(NULL, 0, connect_thread_func, NULL, 0, NULL);

	WaitForSingleObject(threadhandle, INFINITE);
	return 0;
}

