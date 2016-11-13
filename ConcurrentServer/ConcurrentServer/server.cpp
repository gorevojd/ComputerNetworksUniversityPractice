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
static int GlobalListSize;
static SOCKET GlobalServerSock;
static HMODULE OurLib;

HANDLE AcceptServerHandle;
HANDLE ConsolePipeHandle;
HANDLE GarbageCleanerHandle;
HANDLE DispatchServerHandle;

static list<contact> Contacts;

VOID CALLBACK ASWTimer(
	LPVOID lpArgToCompletionRoutine,
	DWORD  dwTimerLowValue,
	DWORD  dwTimerHighValue)
{
	printf("AP TIMEOUT\n");
	PrintTime();

	contact* Cont = (contact*)lpArgToCompletionRoutine;
	EnterCriticalSection(&OurCriticalSection);
	Cont->WorkingState = WORK_TS_TIMEOUT;
	closesocket(Cont->Sock);
	LeaveCriticalSection(&OurCriticalSection);
}

VOID CALLBACK EchoStartAP(ULONG_PTR Param){	
	printf("AP START\n");
	PrintTime();
}

VOID CALLBACK EchoFinishAP(ULONG_PTR Param){
	printf("AP FINISH\n");
	PrintTime();
	
	CancelWaitableTimer(((contact*)Param)->TimerHandle);
}

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
		
		if (*Command != TC_EXIT && NumberOfTries > 0){
			contact Cont = CreateContact(WAIT_TS_ACCEPT, "Hello");
			Cont.AccServHandle = AcceptServerHandle;
			Cont.DispServHandle = DispatchServerHandle;
			bool ClientIsConnected = false; 
			int Tmp = NumberOfTries;
			while (Tmp > 0 && ClientIsConnected == false){

				Cont.Sock = accept(GlobalServerSock, (sockaddr*)&Cont.SockAddr, &Cont.SockAddrLen);
				if (Cont.Sock == INVALID_SOCKET){
					if (WSAGetLastError() == WSAEWOULDBLOCK){
						//CheckNetError();
					}
					closesocket(Cont.Sock);
					//CheckNetError();
				}
				else{
					ClientIsConnected = true;
					
					int BytesReceived = recv(Cont.Sock, Cont.Message, MESSAGE_SIZE, 0);
					CheckNetError();

					EnterCriticalSection(&OurCriticalSection);
					Contacts.push_front(Cont);
					LeaveCriticalSection(&OurCriticalSection);
					Contacts.front().WaitingState = WAIT_TS_CONTACT;

					printf("Got the client...\n");
				}
				
				Tmp--;
			}
			if (ClientIsConnected == true){
				*Command = TC_GETCOMMAND;
			}
			//SleepEx(0, TRUE);
			
		}
	}

	closesocket(GlobalServerSock);
	CheckNetError();

	WSACleanup();
	CheckNetError();

	printf("AcceptServer finished\n");
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

	return(Result);
}

DWORD WINAPI EchoServer(LPVOID Param){
	DWORD Result = 0;
	printf("Echo server\n");
	contact* Cont = (contact*)Param;
	Cont->WorkingState = WORK_TS_WORK;

	QueueUserAPC(EchoStartAP, Cont->DispServHandle, (ULONG_PTR)Param);

	char OutputBuffer[50] = "Wtf Server";
	char* InputBuffer = (char*)malloc(MESSAGE_SIZE * sizeof(char));

	int ReceivedBytesCount = recv(Cont->Sock, InputBuffer, MESSAGE_SIZE, NULL);
	CheckNetError();
	cout << InputBuffer << endl;

	int SentBytesCount = send(Cont->Sock, OutputBuffer, strlen(OutputBuffer) + 1, NULL);
	CheckNetError();

	Cont->WorkingState = WORK_TS_FINISH;

	QueueUserAPC(EchoFinishAP, Cont->DispServHandle, (ULONG_PTR)Param);

	printf("Echo server thread exited with code: %u\n", Result);
	return(Result);
}

DWORD WINAPI DispatchServer(LPVOID Param){
	DWORD Result = 0;

	printf("Dispatch Server\n");

	talkers_command* Command = (talkers_command*)Param;
	
	while (GlobalRunning == true){
		EnterCriticalSection(&OurCriticalSection);
		for (int i = 0; i < Contacts.size(); i++){
			list_contact::iterator it = Contacts.begin();
			std::advance(it, i);
			if (it != Contacts.end()){
				if (it->WaitingState == WAIT_TS_CONTACT && it->WorkingState == WORK_TS_DEFAULT){

					if (strcmp(it->Message, "EchoServer") != 0 &&
						strcmp(it->Message, "TimeServer") != 0 &&
						strcmp(it->Message, "0001") != 0)
					{
						it->WorkingState = WORK_TS_ABORT;
						closesocket(it->Sock);
						CheckNetError();
					}
					else{
						it->TimerHandle = CreateWaitableTimer(0, FALSE, 0);
						LARGE_INTEGER Li;
						int Seconds = 5;
						Li.QuadPart = -(10000000 * Seconds);
						SleepEx(0, TRUE);
						//WaitForSingleObject(it->TimerHandle, INFINITE);
						SetWaitableTimer(it->TimerHandle, &Li, 0, ASWTimer, (LPVOID)&(*it), FALSE);
						it->ThreadHandle = OurSSS(it->Message, &(*it));
						if (it->ThreadHandle != INVALID_HANDLE_VALUE){
							WaitForSingleObject(it->ThreadHandle, INFINITE);
							CloseHandle(it->ThreadHandle);
						}
						else{
							printf("Can not service this client. Sent abort message.\n");
							it->WorkingState = WORK_TS_ABORT;
							CancelWaitableTimer(it->TimerHandle);
							closesocket(it->Sock);
							CheckNetError();
						}
					}
				}
			}
		}
		LeaveCriticalSection(&OurCriticalSection);
	}
	
	printf("Exiting DISPATCH thread.\n");
	return(Result);
}

DWORD WINAPI GarbageCleaner(LPVOID Param){
	DWORD Result = 0;

	talkers_command* Command = (talkers_command*)Param;

	while (GlobalRunning == true){
		EnterCriticalSection(&OurCriticalSection);
		for (int i = 0; i < Contacts.size(); i++){
			list_contact::iterator it = Contacts.begin();
			std::advance(it, i);
			if (it != Contacts.end()){
				working_thread_state Ts = it->WorkingState;
				
				if (Ts == WORK_TS_FINISH || Ts == WORK_TS_ABORT || Ts == WORK_TS_TIMEOUT){
					if (Ts == WORK_TS_FINISH){

					}
					else if (Ts == WORK_TS_ABORT || Ts == WORK_TS_TIMEOUT){

					}
					CloseHandle(it->ThreadHandle);
					CloseHandle(it->TimerHandle);
					closesocket(it->Sock);
					it = Contacts.erase(it);
				}
				else{
					//WaitForSingleObject(it->ThreadHandle, INFINITE);
					//CloseHandle(it->ThreadHandle);
				}
			}
		}
		LeaveCriticalSection(&OurCriticalSection);
	}

	printf("Exiting the GARBAGE CLEANER thread.\n");
	return(Result);
}


int main(int argc, char** argv){

	GlobalPortNumber = 2000;
	if (argc > 1){
		sscanf(argv[1], "%d", &GlobalPortNumber);
	}

	HMODULE OurLib = LoadLibraryA("SSS.dll");
	(sss_prototype*)OurSSS = (sss_prototype*)GetProcAddress(OurLib, "SSS");

	InitializeCriticalSection(&OurCriticalSection);

	volatile talkers_command cmd = TC_START;

	AcceptServerHandle = CreateThread(0, 0, AcceptServer, (LPVOID)&cmd, 0, 0);
	DispatchServerHandle = CreateThread(0, 0, DispatchServer, (LPVOID)&cmd, 0, 0);
	ConsolePipeHandle = CreateThread(0, 0, ConsolePipe, (LPVOID)&cmd, 0, 0);
	GarbageCleanerHandle = CreateThread(0, 0, GarbageCleaner, (LPVOID)&cmd, 0, 0);


	WaitForSingleObject(AcceptServerHandle, INFINITE);
	WaitForSingleObject(DispatchServerHandle, INFINITE);
	WaitForSingleObject(ConsolePipeHandle, INFINITE);
	WaitForSingleObject(GarbageCleanerHandle, INFINITE);

	CloseHandle(AcceptServerHandle);
	CloseHandle(DispatchServerHandle);
	CloseHandle(ConsolePipeHandle);
	CloseHandle(GarbageCleanerHandle);

	DeleteCriticalSection(&OurCriticalSection);

	FreeLibrary(OurLib);
	
	system("pause");
	return 0;
}