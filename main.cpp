#include "deklaracje.h"
#include "SockNet.h"

extern DWORD WINAPI connect_thread_func(LPVOID lpParam );

using namespace std;

int main()
{
    HANDLE WINAPI threadhandle = CreateThread( NULL, 0, connect_thread_func, NULL, 0, NULL);

	WaitForSingleObject(threadhandle, INFINITE);
}
