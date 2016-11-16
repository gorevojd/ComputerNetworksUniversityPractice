#include "../CommonCode/common_code.h"
#include "../CommonCode/extern_functions.h"
#include <iostream>
#include <list>
#include <time.h>

using namespace std;

struct server_thread_context{
	talkers_command Command;
	int PortNumber;
};

static HANDLE OurEvent = CreateEvent(0, FALSE, FALSE, 0);
static CRITICAL_SECTION OurCriticalSection;
static bool GlobalListeningClients;
static int GlobalPortNumber;
static int GlobalListSize;

static SOCKET GlobalServerSock;
static HMODULE OurLib;

static HANDLE AcceptServerHandle;
static HANDLE ConsolePipeHandle;
static HANDLE GarbageCleanerHandle;
static HANDLE DispatchServerHandle;

static list<contact> Contacts;

static volatile DWORD CurrentlyWorkingClients;
static volatile DWORD FinishedClients;
static volatile DWORD NotFinishedClients;

VOID CALLBACK ASWTimer(
	LPVOID lpArgToCompletionRoutine,
	DWORD  dwTimerLowValue,
	DWORD  dwTimerHighValue)
{
	printf("AP TIMEOUT\n");
	PrintTime();

	contact* Cont = (contact*)lpArgToCompletionRoutine;
	//Here we sending empty string so client know that timer has been ended
	int BytesSent = send(Cont->Sock, "", 1, 0);

	EnterCriticalSection(&OurCriticalSection);
	Cont->IsTimerEnded = true;
	LeaveCriticalSection(&OurCriticalSection);
}

VOID CALLBACK EchoStartAP(ULONG_PTR Param){	
	printf("AP START\n");
	PrintTime();

	InterlockedIncrement(&CurrentlyWorkingClients);
}

VOID CALLBACK EchoFinishAP(ULONG_PTR Param){
	printf("AP FINISH\n");
	PrintTime();

	//contact* Cont = (contact*)Param;
	//Cont->WorkingState = WORK_TS_FINISH;

	InterlockedDecrement(&CurrentlyWorkingClients);
	CancelWaitableTimer(((contact*)Param)->TimerHandle);
}

static void WaitForClients(){
	bool IsEmpty = false;
	while (!IsEmpty){
		EnterCriticalSection(&OurCriticalSection);
		IsEmpty = Contacts.empty();
		LeaveCriticalSection(&OurCriticalSection);
		SleepEx(0, TRUE);
	}
}

DWORD WINAPI AcceptServer(LPVOID Param){
	DWORD Result = 0;

	printf("Accept server\n");

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
				*Command = TC_EXIT;
			}break;
			case(TC_WAIT) : {
				WaitForClients();
				*Command = TC_GETCOMMAND;
				NumberOfTries = ACCEPT_CYCLE_PARAM;
			}break;
			case(TC_STAT) : {

			}break;
			case(TC_SHUTDOWN) : {
				WaitForClients();
				*Command = TC_EXIT;
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
					EnterCriticalSection(&OurCriticalSection);
					Contacts.push_front(Cont);
					LeaveCriticalSection(&OurCriticalSection);
					Contacts.front().WaitingState = WAIT_TS_CONTACT;
					SetEvent(OurEvent);
					printf("Got the client...\n");
				}
				
				Tmp--;
			}
			if (ClientIsConnected == true){
				*Command = TC_GETCOMMAND;
			}
			SleepEx(0, TRUE);
			
		}
	}

	closesocket(GlobalServerSock);
	CheckNetError();

	WSACleanup();
	CheckNetError();

	printf("Exiting ACCEPT SERVER thread\n");
	return(Result);
}

DWORD WINAPI ConsolePipe(LPVOID Param){
	DWORD Result = 0;

	printf("Console pipe\n");
	
	talkers_command* Command = (talkers_command*)Param;

	while (*Command != TC_EXIT){
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

			while (*Command != TC_EXIT){
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

				char* TempStr;
				DWORD BytesWritten;
				bool WouldWriteStat = false;
				if (*OurCommand != TC_STAT){
					TempStr = "No stat";
				}
				else{
					WouldWriteStat = true;
					TempStr = "Stat mazafaka";
				}
				DWORD WriteRes = WriteFile(ServerHandle, TempStr, strlen(TempStr) + 1, &BytesWritten, 0);

				if (WouldWriteStat == true){
					char* StatStr = (char*)malloc(MESSAGE_SIZE * sizeof(char));
					sprintf(StatStr, "FINISHED: %u\nWORKING: %u\nABORTED: %u\n", FinishedClients, CurrentlyWorkingClients, NotFinishedClients);
					DWORD StatStrWritten;
					BOOL WriteStatRes = WriteFile(ServerHandle, StatStr, strlen(StatStr) + 1, &StatStrWritten, 0);
					free(StatStr);
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
		CloseHandle(ServerHandle);
	}
	printf("Exiting CONSOLE PIPE thread\n");
	return(Result);
}

DWORD WINAPI TimeServer(LPVOID Param){
	DWORD Result = 0;
	contact* Cont = (contact*)Param;

	QueueUserAPC(EchoStartAP, Cont->AccServHandle, (ULONG_PTR)Param);

	char* AnswerStr = (char*)malloc(MESSAGE_SIZE * sizeof(char));
	SYSTEMTIME St;
	GetLocalTime(&St);
	sprintf(AnswerStr,
		"%Time: %u:%u:%u:%u. Date: %u.%u.%u\n",
		St.wHour, St.wMinute, St.wSecond, St.wMilliseconds,
		St.wDay, St.wMonth, St.wYear);

	int SentBytesCount = send(Cont->Sock, AnswerStr, strlen(AnswerStr) + 1, NULL);
	CheckNetError();
	//printf("Sent time: %s\n", AnswerStr);
	//printf("Bytes sent: %d\n", SentBytesCount);

	QueueUserAPC(EchoFinishAP, Cont->AccServHandle, (ULONG_PTR)Param);
	Cont->WorkingState = WORK_TS_FINISH;

	free(AnswerStr);
	printf("Time server thread exited with code: %u\n", Result);
	return(Result);
}

DWORD WINAPI RandServer(LPVOID Param){
	DWORD Result = 0;
	contact* Cont = (contact*)Param;
	
	srand((unsigned)time(NULL));

	QueueUserAPC(EchoStartAP, Cont->AccServHandle, (ULONG_PTR)Param);

	DWORD RandomNumber = (DWORD)((rand() & 0xFF) << 8 | (rand() & 0xFF) << 16 | (rand() & 0xFF) << 24);

	char* ResultStr = (char*)malloc(MESSAGE_SIZE * sizeof(char));
	sprintf(ResultStr, "%u", RandomNumber);

	int SentBytesCount = send(Cont->Sock, ResultStr, strlen(ResultStr) + 1, NULL);
	CheckNetError();

	QueueUserAPC(EchoFinishAP, Cont->AccServHandle, (ULONG_PTR)Param);
	Cont->WorkingState = WORK_TS_FINISH;

	printf("Time server thread exited with code: %u\n", Result);
	free(ResultStr);
	return(Result);
}

DWORD WINAPI EchoServer(LPVOID Param){
	DWORD Result = 0;
	printf("Echo server\n");
	contact* Cont = (contact*)Param;

	Cont->WorkingState = WORK_TS_WORK;

	QueueUserAPC(EchoStartAP, Cont->AccServHandle, (ULONG_PTR)Param);

	bool ContinueLoop = true;
	while (ContinueLoop == true && Cont->IsTimerEnded == false){
		char* InputBuffer = (char*)malloc(MESSAGE_SIZE * sizeof(char));
		int ReceivedBytesCount = recv(Cont->Sock, InputBuffer, MESSAGE_SIZE, NULL);

		if (ReceivedBytesCount != -1){
			printf("%s\n", InputBuffer);
			if (strlen(InputBuffer) == 0){
				ContinueLoop = false;
				break;
			}
			int SentBytesCount = send(Cont->Sock, InputBuffer, strlen(InputBuffer) + 1, NULL);
		}

		free(InputBuffer);
	}
	
	QueueUserAPC(EchoFinishAP, Cont->AccServHandle, (ULONG_PTR)Param);
	if (Cont->IsTimerEnded == false){
		Cont->WorkingState = WORK_TS_FINISH;
		CancelWaitableTimer(Cont->TimerHandle);
	}
	else{
		Cont->WorkingState = WORK_TS_TIMEOUT;
	}

	printf("Echo server thread exited with code: %u\n", Result);
	return(Result);
}

DWORD WINAPI DispatchServer(LPVOID Param){
	DWORD Result = 0;

	printf("Dispatch Server\n");

	talkers_command* Command = (talkers_command*)Param;
	
	while (*Command != TC_EXIT){
		if (WaitForSingleObject(OurEvent, 300) == WAIT_OBJECT_0){
			EnterCriticalSection(&OurCriticalSection);
			for (int i = 0; i < Contacts.size(); i++){
				list_contact::iterator it = Contacts.begin();
				std::advance(it, i);
				if (it != Contacts.end()){
					
					int BytesReceived = recv(it->Sock, it->Message, MESSAGE_SIZE, 0);
					
					if (it->WaitingState == WAIT_TS_CONTACT && it->WorkingState == WORK_TS_DEFAULT){

						if (strcmp(it->Message, "Echo") != 0 &&
							strcmp(it->Message, "Time") != 0 &&
							strcmp(it->Message, "Rand") != 0)
						{
							printf("ERROR IN QUERY\n");
							it->WorkingState = WORK_TS_ABORT;
							closesocket(it->Sock);
							CheckNetError();
						}
						else{

							it->TimerHandle = CreateWaitableTimer(0, FALSE, 0);
							LARGE_INTEGER Li;
							int Seconds = 3;
							Li.QuadPart = -(10000000 * Seconds);
							it->IsTimerEnded = false;
							SetWaitableTimer(it->TimerHandle, &Li, 0, ASWTimer, (LPVOID)&(*it), FALSE);
							
							//Here we resending commnad that client has been requested
							int ResendingBytesSent = send(it->Sock, it->Message, strlen(it->Message) + 1, 0);

							it->ThreadHandle = OurSSS(it->Message, &(*it));
							if (it->ThreadHandle != INVALID_HANDLE_VALUE){
								//SleepEx(0, TRUE);
								//if (WaitForSingleObject(it->TimerHandle, Seconds * 1000) == WAIT_OBJECT_0){
								//	printf("Dispatch server: Waitable timer entered sygnal state\n");
								//	SleepEx(0, TRUE);
								//}
								//WaitForSingleObject(it->ThreadHandle, INFINITE);
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
		else{
			SleepEx(0, TRUE);
		}
	}
	
	printf("Exiting DISPATCH thread.\n");
	return(Result);
}

DWORD WINAPI GarbageCleaner(LPVOID Param){
	DWORD Result = 0;

	printf("Garbage cleaner\n");

	talkers_command* Command = (talkers_command*)Param;

	while (*Command != TC_EXIT){
		EnterCriticalSection(&OurCriticalSection);
		for (int i = 0; i < Contacts.size(); i++){
			list_contact::iterator it = Contacts.begin();
			std::advance(it, i);
			if (it != Contacts.end()){
				working_thread_state Ts = it->WorkingState;
				
				if (Ts == WORK_TS_FINISH || Ts == WORK_TS_ABORT || Ts == WORK_TS_TIMEOUT){
					if (Ts == WORK_TS_FINISH){
						InterlockedIncrement(&FinishedClients);
					}
					else if (Ts == WORK_TS_ABORT || Ts == WORK_TS_TIMEOUT){
						InterlockedIncrement(&NotFinishedClients);
					}
					CloseHandle(it->ThreadHandle);
					CloseHandle(it->TimerHandle);
					closesocket(it->Sock);
					it = Contacts.erase(it);
				}

			}
		}
		LeaveCriticalSection(&OurCriticalSection);
		Sleep(1000);
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

	SetConsoleColor(10);
	printf("Finished - %u\n", FinishedClients);
	SetConsoleColor(12);
	printf("Aborted clients - %u\n", NotFinishedClients);
	SetConsoleColor();

	FreeLibrary(OurLib);
	
	system("pause");
	return 0;
}