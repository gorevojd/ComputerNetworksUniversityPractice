#include "../CommonCode/common_code.h"
#include <iostream>
#include <list>

using namespace std;

struct server_thread_context{
	talkers_command Command;
};

static CRITICAL_SECTION OurCriticalSection;
static bool GlobalRunning = true;
static bool IsListeningClients;

void GetPipe(){
	
}

DWORD WINAPI AcceptServer(LPVOID Param){
	DWORD Result = 0;

	EnterCriticalSection(&OurCriticalSection);
	//TODO(Dima): Add element to the list
	LeaveCriticalSection(&OurCriticalSection);

	ExitThread(Result);
	return(Result);
}

DWORD WINAPI ConsolePipe(LPVOID Param){
	DWORD Result = 0;
	
	char NamedPipeName[] = "\\\\.\\pipe\\NP_NAME";
	HANDLE ServerHandle = CreateNamedPipeA(
		NamedPipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
		1,
		0,
		0,
		INFINITE,
		0);

	if (ServerHandle != INVALID_HANDLE_VALUE){
		ConnectNamedPipe(ServerHandle, 0);

		while (GlobalRunning == true){
			void* Contents = VirtualAlloc(0, MESSAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			DWORD BytesRead;
			ReadFile(ServerHandle, (char*)Contents, MESSAGE_SIZE, &BytesRead, 0);
			//TODO(Dima):

			talkers_command OurCommand = TC_DONOTHING;
			if (strcmp((char*)Contents, "EXIT") == 0){
				OurCommand = TC_EXIT;
			}
			else if (strcmp((char*)Contents, "START") == 0){
				OurCommand = TC_START;
			}
			else if (strcmp((char*)Contents, "WAIT") == 0){
				OurCommand = TC_WAIT;
			}
			else if (strcmp((char*)Contents, "STAT") == 0){
				OurCommand = TC_STAT;
			}
			else if (strcmp((char*)Contents, "STOP") == 0){
				OurCommand = TC_STOP;
			}
			else if (strcmp((char*)Contents, "SHUTDOWN") == 0){
				OurCommand = TC_SHUTDOWN;
			}
			else if (strcmp((char*)Contents, "GETCOMMAND") == 0){
				OurCommand = TC_GETCOMMAND;
			}

			switch (OurCommand){
				case(TC_START) : {

				}break;
				case(TC_STOP) : {

				}break;
				case(TC_EXIT) : {

				}break;
				case(TC_WAIT) : {

				}break;
				case(TC_STAT) : {

				}break;
				case(TC_SHUTDOWN) : {

				}break;
				case(TC_GETCOMMAND) : {

				}break;
				default:{

				}
			}

			VirtualFree(Contents, 0, MEM_RELEASE);
		}
	}

	ExitThread(Result);
	return(Result);
}

DWORD WINAPI GarbageCleaner(LPVOID Param){
	DWORD Result = 0;

	EnterCriticalSection(&OurCriticalSection);
	//TODO(Dima): Remove element from list
	LeaveCriticalSection(&OurCriticalSection);

	ExitThread(Result);
	return(Result);
}

int main(int argc, char** argv){

	InitializeCriticalSection(&OurCriticalSection);

	volatile talkers_command cmd = TC_START;

	HANDLE AcceptServerHandle;
	HANDLE ConsolePipeHandle;
	HANDLE GarbageCleanerHandle;

	DWORD AcceptThreadId;
	AcceptServerHandle = CreateThread(0, 0, AcceptServer, (LPVOID)&cmd, 0, &AcceptThreadId);
	DWORD ConsoleThreadId;
	ConsolePipeHandle = CreateThread(0, 0, ConsolePipe, (LPVOID)&cmd, 0, &ConsoleThreadId);
	DWORD GarbageThreadId;
	GarbageCleanerHandle = CreateThread(0, 0, GarbageCleaner, (LPVOID)&cmd, 0, &GarbageThreadId);

	WaitForSingleObject(AcceptServerHandle, INFINITE);
	CloseHandle(AcceptServerHandle);
	WaitForSingleObject(ConsolePipeHandle, INFINITE);
	CloseHandle(ConsolePipeHandle);
	WaitForSingleObject(GarbageCleanerHandle, INFINITE);
	CloseHandle(GarbageCleanerHandle);

	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 0), &WsaData);



	WSACleanup();

	DeleteCriticalSection(&OurCriticalSection);
	
	system("pause");
	return 0;
}