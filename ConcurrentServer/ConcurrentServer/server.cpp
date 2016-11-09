#include "../CommonCode/common_code.h"
#include "../CommonCode/extern_functions.h"
#include <iostream>
#include <list>

using namespace std;

struct server_thread_context{
	talkers_command Command;
	int PortNumber;
};

static CRITICAL_SECTION OurCriticalSection;
static bool GlobalRunning = true;
static bool GlobalListeningClients;
static int GlobalPortNumber;
static SOCKET GlobalServerSock;

static list_contact Contacts;

DWORD WINAPI AcceptServer(LPVOID Param){
	DWORD Result = 0;

	talkers_command* Command = (talkers_command*)Param;

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	CheckNetError();

	GlobalServerSock = socket(AF_INET, SOCK_STREAM, NULL);
	CheckNetError();

	SOCKADDR_IN serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(GlobalPortNumber);
	serv.sin_addr.s_addr = INADDR_ANY;

	bind(GlobalServerSock, (LPSOCKADDR)&serv, sizeof(serv));
	CheckNetError();

	listen(GlobalServerSock, SOMAXCONN);
	CheckNetError();

	unsigned long nonblk;
	int tr = ioctlsocket(GlobalServerSock, FIONBIO, &(nonblk = 1));
	
#ifndef ACCEPT_CYCLE_PARAM
#define ACCEPT_CYCLE_PARAM 10
#endif

	int NumberOfTries = 0;

	while (*Command != TC_EXIT){
		switch (*Command){
			case(TC_START) : {
				NumberOfTries = ACCEPT_CYCLE_PARAM;
				GlobalListeningClients = true;
				*Command = TC_GETCOMMAND;
			}break;
			case(TC_STOP) : {
				NumberOfTries = 0;
				*Command = TC_GETCOMMAND;
			}break;
			case(TC_EXIT) : {
				GlobalRunning = false;
			}break;
			case(TC_WAIT) : {
				//HANDLE* ThreadsArray = (HANDLE*)malloc(Contacts.size() * sizeof(HANDLE));
				//list_contact::iterator it = Contacts.begin();
				//for (int i = 0; it != Contacts.end(); it++, i++){
				//	ThreadsArray[i] = (*it).ThreadHandle;
				//}
				//WaitForMultipleObjects()
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
		
		contact Cont = CreateContact(WAIT_TS_ACCEPT, "Hello");
		bool ClientIsConnected = false;
		int TmpCopy = NumberOfTries;
		while (TmpCopy > 0 && ClientIsConnected == false){

			if ((Cont.Sock = accept(GlobalServerSock, (sockaddr*)&Cont.SockAddr, &Cont.SockAddrLen)) == INVALID_SOCKET){
				if (WSAGetLastError() == WSAEWOULDBLOCK){
					//CheckNetError();
				}
			}
			else{
				ClientIsConnected = true;
				
				int BytesReceived = recv(Cont.Sock, Cont.Message, MESSAGE_SIZE, 0);
				CheckNetError();

				EnterCriticalSection(&OurCriticalSection);
				Contacts.push_front(Cont);
				LeaveCriticalSection(&OurCriticalSection);
				Contacts.front().WaitingState = WAIT_TS_CONTACT;

				printf("Got the client\n");
			}
			TmpCopy--;
		}
		/*
		if (ClientIsConnected == true){
			*Command = TC_GETCOMMAND;
			
			HMODULE OurLib = LoadLibraryA("SSS.dll");
			(sss_prototype*) OurSSS = (sss_prototype*)GetProcAddress(OurLib, "SSS");
			HANDLE TmpHandle;
			if (OurSSS && (TmpHandle = OurSSS("EchoServer", Command)) != INVALID_HANDLE_VALUE){
				WaitForSingleObject(TmpHandle, INFINITE);
			}
			FreeLibrary(OurLib);
		}
		else{
			//SleepEx(0, TRUE);
		}
		*/
	}


	closesocket(GlobalServerSock);
	CheckNetError();

	WSACleanup();
	CheckNetError();

	ExitThread(Result);
	return(Result);
}

DWORD WINAPI ConsolePipe(LPVOID Param){
	DWORD Result = 0;
	
	/*START - Allows clients to connect to server*/
	/*STOP - Prevent connecting clients to server*/
	/*EXIT - Finishes server program*/
	/*STAT - Statistics: common connections count, active connections count, denied count*/
	/*WAIT - Pause client connections until the last client done*/
	/*SHUTDOWN - The same as WAIT then EXIT*/
	/*GETCOMMAND - Server ready to receive and serve next command(Server only, not from Control Console)*/

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

			talkers_command* OurCommand = (talkers_command*)Param;
			if (strcmp((char*)Contents, "EXIT") == 0){
				*OurCommand = TC_EXIT;
			}
			else if (strcmp((char*)Contents, "START") == 0){
				*OurCommand = TC_START;
			}
			else if (strcmp((char*)Contents, "WAIT") == 0){
				*OurCommand = TC_WAIT;
			}
			else if (strcmp((char*)Contents, "STAT") == 0){
				*OurCommand = TC_STAT;
			}
			else if (strcmp((char*)Contents, "STOP") == 0){
				*OurCommand = TC_STOP;
			}
			else if (strcmp((char*)Contents, "SHUTDOWN") == 0){
				*OurCommand = TC_SHUTDOWN;
			}
			else if (strcmp((char*)Contents, "GETCOMMAND") == 0){
				*OurCommand = TC_GETCOMMAND;
			}

			switch (*OurCommand){
				case(TC_START) : {
					OutputDebugStringA("START\n");
				}break;
				case(TC_STOP) : {
					OutputDebugStringA("STOP\n");
				}break;
				case(TC_EXIT) : {
					OutputDebugStringA("EXIT\n");
				}break;
				case(TC_WAIT) : {
					OutputDebugStringA("WAIT\n");
				}break;
				case(TC_STAT) : {
					OutputDebugStringA("STAT\n");
				}break;
				case(TC_SHUTDOWN) : {
					OutputDebugStringA("SHUTDOWN\n");
				}break;
				case(TC_GETCOMMAND) : {
					OutputDebugStringA("GETCOMMAND\n");
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

DWORD WINAPI DispatchServer(LPVOID Param){
	DWORD Result = 0;

	printf("Dispatch Server\n");

	talkers_command* Command = (talkers_command*)Param;
	
	while(GlobalRunning == true){
	
		list_contact::iterator it = Contacts.begin();
		for (it; it != Contacts.end(); it++){
			if ((*it).WaitingState == WAIT_TS_CONTACT && (*it).WorkingState == WORK_TS_DEFAULT){
				HMODULE OurLib = LoadLibraryA("SSS.dll");
				(sss_prototype*)OurSSS = (sss_prototype*)GetProcAddress(OurLib, "SSS");
				HANDLE TmpHandle;
				if (OurSSS && (TmpHandle = OurSSS("EchoServer", &(*it))) != INVALID_HANDLE_VALUE){
					
					WaitForSingleObject(TmpHandle, INFINITE);
				}
				FreeLibrary(OurLib);
			}
		}
	}

	ExitThread(Result);
	return(Result);
}

DWORD WINAPI EchoServer(LPVOID Param){
	DWORD Result = 0;

	printf("Echo server\n");

	contact* Cont = (contact*)Param;
	Cont->WorkingState = WORK_TS_WORK;

	char OutputBuffer[50] = "Wtf Server";
	char* InputBuffer = (char*)malloc(MESSAGE_SIZE * sizeof(char));

	int ReceivedBytesCount = recv(Cont->Sock, InputBuffer, MESSAGE_SIZE, NULL);
	CheckNetError();
	cout << InputBuffer << endl;

	int SentBytesCount = send(Cont->Sock, OutputBuffer, strlen(OutputBuffer) + 1, NULL);
	CheckNetError();

	Cont->WorkingState = WORK_TS_FINISH;

	ExitThread(Result);
	return(Result);
}



int main(int argc, char** argv){

	GlobalPortNumber = 2000;
	if (argc > 1){
		sscanf(argv[1], "%d", &GlobalPortNumber);
	}

	InitializeCriticalSection(&OurCriticalSection);

	volatile talkers_command cmd = TC_START;

	HANDLE AcceptServerHandle;
	HANDLE ConsolePipeHandle;
	HANDLE GarbageCleanerHandle;
	HANDLE DispatchServerHandle;

	DWORD AcceptThreadId;
	AcceptServerHandle = CreateThread(0, 0, AcceptServer, (LPVOID)&cmd, 0, &AcceptThreadId);
	DWORD DispatchThreadId;
	DispatchServerHandle = CreateThread(0, 0, DispatchServer, (LPVOID)&cmd, 0, &DispatchThreadId);
	DWORD ConsoleThreadId;
	ConsolePipeHandle = CreateThread(0, 0, ConsolePipe, (LPVOID)&cmd, 0, &ConsoleThreadId);
	DWORD GarbageThreadId;
	GarbageCleanerHandle = CreateThread(0, 0, GarbageCleaner, (LPVOID)&cmd, 0, &GarbageThreadId);

	WaitForSingleObject(AcceptServerHandle, INFINITE);
	CloseHandle(AcceptServerHandle);
	WaitForSingleObject(DispatchServerHandle, INFINITE);
	CloseHandle(DispatchServerHandle);
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