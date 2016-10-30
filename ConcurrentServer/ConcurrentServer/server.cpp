#include "../CommonCode/common_code.h"
#include <iostream>
#include <list>

using namespace std;

enum talkers_command{
	START = 1,
	STOP = 2,
	EXIT = 3,
};

DWORD WINAPI AcceptServer(LPVOID Param){
	DWORD Result = 0;

	ExitThread(Result);
	return(Result);
}

DWORD WINAPI ConsolePipe(LPVOID Param){
	DWORD Result = 0;
	
	
	
	ExitThread(Result);
	return(Result);
}

DWORD WINAPI GarbageCleaner(LPVOID Param){
	DWORD Result = 0;

	ExitThread(Result);
	return(Result);
}

int main(int argc, char** argv){
	
	volatile talkers_command cmd = START;

	HANDLE AcceptServerHandle;
	HANDLE ConsolePipeHandle;
	HANDLE GarbageCleanerHandle;

	DWORD AcceptThreadId;
	AcceptServerHandle = CreateThread(0, 0, AcceptServer, (LPVOID)&cmd, 0, &AcceptThreadId);
	DWORD ConsoleThreadId;
	ConsolePipeHandle = CreateThread(0, 0, ConsolePipe, (LPVOID)&cmd, 0, &ConsoleThreadId);
	DWORD GarbageThreadId;
	ConsolePipeHandle = CreateThread(0, 0, GarbageCleaner, (LPVOID)&cmd, 0, &GarbageThreadId);

	WaitForSingleObject(AcceptServerHandle, INFINITE);
	CloseHandle(AcceptServerHandle);
	WaitForSingleObject(ConsolePipeHandle, INFINITE);
	CloseHandle(ConsolePipeHandle);
	WaitForSingleObject(GarbageCleanerHandle, INFINITE);
	CloseHandle(GarbageCleanerHandle);


	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 0), &WsaData);



	WSACleanup();

	system("pause");
	return 0;
}