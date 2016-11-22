#ifndef COMMON_CODE_H
#define COMMON_CODE_H

#include <WinSock2.h>
#include <Windows.h>
#include <list>

#define MESSAGE_SIZE 64
#define TEST_TIME_TO_SLEEP 10

struct table_entry{
	char Id[20];
	DWORD((WINAPI* Function))(LPVOID);
};

#define BEGIN_TABLESERVICE table_entry TableService[] = {
#define ENTRY_SERVICE(s, t) {s, t}
#define END_TABLESERVICE };
#define TABLESERVICE_ID(i) TableService[i].Id
#define TABLESERVICE_FN(i) TableService[i].Function
#define TableArrayCount (sizeof(TableService) / sizeof(TableService[0]))

enum talkers_command{
	TC_DONOTHING = 0,
	TC_START, /*Allow client connection*/
	TC_STOP, /*Disallow client connection*/
	TC_EXIT, /*Exit server program*/
	TC_STAT, /*Statistics: number of connections,
		  active connections,
		  number of dissmissed connections*/
	TC_WAIT, /**/
	TC_SHUTDOWN,
	TC_GETCOMMAND
};

enum waiting_thread_state{
	WAIT_TS_EMPTY = 0,
	WAIT_TS_ACCEPT,
	WAIT_TS_CONTACT
};
enum working_thread_state{
	WORK_TS_DEFAULT = 0,
	WORK_TS_WORK,
	WORK_TS_ABORT,
	WORK_TS_TIMEOUT,
	WORK_TS_FINISH
};

struct contact{
	DWORD GlobalRunning;

	waiting_thread_state WaitingState;
	working_thread_state WorkingState;

	SOCKET Sock;
	SOCKADDR_IN SockAddr;
	int SockAddrLen;
	HANDLE ThreadHandle;
	HANDLE TimerHandle;

	bool IsTimerEnded;

	HANDLE AccServHandle;
	HANDLE DispServHandle;

	char Message[MESSAGE_SIZE];
	char ServerName[15];
};

typedef std::list<contact> list_contact;

inline contact CreateContact(waiting_thread_state State, const char* ServerName = ""){
	contact Result = {};

	Result.SockAddrLen = sizeof(SOCKADDR_IN);
	Result.WaitingState = State;
	strcpy(Result.ServerName, ServerName);
	Result.Message[0] = '\0';

	return(Result);
}

inline contact CreateEmptyContact(){
	contact Result = {};
	return(Result);
}

void SetWorkingState(contact* Contact, working_thread_state WorkingState, const char* Message = ""){
	Contact->WorkingState = WorkingState;
	strcpy(Contact->Message, Message);
}

/*
The different color codes are

0   BLACK
1   BLUE
2   GREEN
3   CYAN
4   RED
5   MAGENTA
6   BROWN
7   LIGHTGRAY
8   DARKGRAY
9   LIGHTBLUE
10  LIGHTGREEN
11  LIGHTCYAN
12  LIGHTRED
13  LIGHTMAGENTA
14  YELLOW
15  WHITE
*/
void PrintColorText(const char* Text, DWORD Color = 7){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
	printf(Text);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void SetConsoleColor(DWORD Color = 7){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
}

void PrintTime(){
	SYSTEMTIME St;
	GetLocalTime(&St);
	printf(
		"%Time: %u:%u:%u:%u. Date: %u.%u.%u\n",
		St.wHour, St.wMinute, St.wSecond, St.wMilliseconds, 
		St.wDay, St.wMonth, St.wYear);
}

void CheckNetError(){
	int errCode = WSAGetLastError();
	switch (errCode){
		case (WSAEINTR) : {
			OutputDebugStringA("WSAEINTR Работа функции прервана");
		}break;
		case(WSAEACCES) : {
			OutputDebugStringA("WSAEACCES Разрешение отвергнуто");
		}break;
		case(WSAEFAULT) : {
			OutputDebugStringA("WSAEFAULT Ошибочный адрес ");
		}break;
		case(WSAEINVAL) : {
			OutputDebugStringA("WSAEINVAL Ошибка в аргументе");
		}break;
		case(WSAEMFILE) : {
			OutputDebugStringA("WSAEMFILE Слишком много файлов открыто");
		}break;
		case(WSAEWOULDBLOCK) : {
			OutputDebugStringA("WSAEWOULDBLOCK Ресурс временно недоступен");
		}break;
		case(WSAEINPROGRESS) : {
			OutputDebugStringA("WSAEINPROGRESS Операция в процессе развития");
		}break;
		case(WSAEALREADY) : {
			OutputDebugStringA("WSAEALREADY Операция уже выполняется");
		}break;
		case(WSAENOTSOCK) : {
			OutputDebugStringA("WSAENOTSOCK Сокет задан неправильно");
		}break;
		case(WSAEDESTADDRREQ) : {
			OutputDebugStringA("WSAEDESTADDRREQ Требуется адрес расположения ");
		}break;
		case(WSAEMSGSIZE) : {
			OutputDebugStringA("WSAEMSGSIZE Сообщение слишком длинное");
		}break;
		case(WSAEPROTOTYPE) : {
			OutputDebugStringA("WSAEPROTOTYPE Неправильный тип протокола для сокета");
		}break;
		case(WSAENOPROTOOPT) : {
			OutputDebugStringA("WSAENOPROTOOPT Ошибка в опции протокола");
		}break;
		case(WSAEPROTONOSUPPORT) : {
			OutputDebugStringA("WSAEPROTONOSUPPORT Протокол не поддерживается ");
		}break;
		case(WSAESOCKTNOSUPPORT) : {
			OutputDebugStringA("WSAESOCKTNOSUPPORT Тип сокета не поддерживается ");
		}break;
		case(WSAEOPNOTSUPP) : {
			OutputDebugStringA("WSAEOPNOTSUPP Операция не поддерживается ");
		}break;
		case(WSAEPFNOSUPPORT) : {
			OutputDebugStringA("WSAEPFNOSUPPORT Тип протоколов не поддерживается");
		}break;
		case(WSAEAFNOSUPPORT) : {
			OutputDebugStringA("WSAEAFNOSUPPORT Тип адресов не поддерживается протоколом");
		}break;
		case(WSAEADDRINUSE) : {
			OutputDebugStringA("WSAEADDRINUSE Адрес уже используется");
		}break;
		case(WSAEADDRNOTAVAIL) : {
			OutputDebugStringA("WSAEADDRNOTAVAIL Запрошенный адрес не может быть использован");
		}break;
		case(WSAENETDOWN) : {
			OutputDebugStringA("WSAENETDOWN Сеть отключена");
		}break;
		case(WSAENETUNREACH) : {
			OutputDebugStringA("WSAENETUNREACH Сеть не достижима ");
		}break;
		case(WSAENETRESET) : {
			OutputDebugStringA("WSAENETRESET Сеть разорвала соединение");
		}break;
		case(WSAECONNABORTED) : {
			OutputDebugStringA("WSAECONNABORTED Программный отказ связи ");
		}break;
		case(WSAECONNRESET) : {
			OutputDebugStringA("WSAECONNRESET Связь восстановлена ");
		}break;
		case(WSAENOBUFS) : {
			OutputDebugStringA("WSAENOBUFS Не хватает памяти для буферов");
		}break;
		case(WSAEISCONN) : {
			OutputDebugStringA("WSAEISCONN Сокет уже подключен");
		}break;
		case(WSAENOTCONN) : {
			OutputDebugStringA("WSAENOTCONN Сокет не подключен");
		}break;
		case(WSAESHUTDOWN) : {
			OutputDebugStringA("WSAESHUTDOWN Нельзя выполнить send: сокет завершил работу");
		}break;
		case(WSAETIMEDOUT) : {
			OutputDebugStringA("WSAETIMEDOUT Закончился отведенный интервал  времени");
		}break;
		case(WSAECONNREFUSED) : {
			OutputDebugStringA("WSAECONNREFUSED Соединение отклоненo");
		}break;
		case(WSAEHOSTDOWN) : {
			OutputDebugStringA("WSAEHOSTDOWN Хост в неработоспособном состоянии");
		}break;
		case(WSAEHOSTUNREACH) : {
			OutputDebugStringA("WSAEHOSTUNREACH Нет маршрута для хоста");
		}break;
		case(WSAEPROCLIM) : {
			OutputDebugStringA("WSAEPROCLIM Слишком много процессов ");
		}break;
		case(WSASYSNOTREADY) : {
			OutputDebugStringA("WSASYSNOTREADY Сеть не доступна ");
		}break;
		case(WSAVERNOTSUPPORTED) : {
			OutputDebugStringA("WSAVERNOTSUPPORTED Данная версия недоступна ");
		}break;
		case(WSANOTINITIALISED) : {
			OutputDebugStringA("WSANOTINITIALISED Не выполнена инициализация WS2_32.DLL");
		}break;
		case(WSAEDISCON) : {
			OutputDebugStringA("WSAEDISCON Выполняется отключение");
		}break;
		case(WSATYPE_NOT_FOUND) : {
			OutputDebugStringA("WSATYPE_NOT_FOUND Класс не найден");
		}break;
		case(WSAHOST_NOT_FOUND) : {
			OutputDebugStringA("WSAHOST_NOT_FOUND Хост не найден ");
		}break;
		case(WSATRY_AGAIN) : {
			OutputDebugStringA("WSATRY_AGAIN Неавторизированный хост не найден ");
		}break;
		case(WSANO_RECOVERY) : {
			OutputDebugStringA("WSANO_RECOVERY Неопределенная  ошибка");
		}break;
		case(WSANO_DATA) : {
			OutputDebugStringA("WSANO_DATA Нет записи запрошенного типа");
		}break;
		/*case(WSA_INVALID_HANDLE) : {
			OutputDebugStringA("WSA_INVALID_HANDLE Указанный дескриптор события  с ошибкой");
		}break;
		case(WSA_INVALID_PARAMETER) : {
			OutputDebugStringA("WSA_INVALID_PARAMETER Один или более параметров с ошибкой");
		}break;
		case(WSA_IO_INCOMPLETE) : {
			OutputDebugStringA("WSA_IO_INCOMPLETE Объект ввода-вывода не в сигнальном состоянии");
		}break;
		case(WSA_IO_PENDING) : {
			OutputDebugStringA("WSA_IO_PENDING Операция завершится позже");
		}break;
		case(WSA_NOT_ENOUGH_MEMORY) : {
			OutputDebugStringA("WSA_NOT_ENOUGH_MEMORY Не достаточно памяти");
		}break;
		case(WSA_OPERATION_ABORTED) : {
			OutputDebugStringA("WSA_OPERATION_ABORTED Операция отвергнута");
		}break;*/
		case(0) : {
			OutputDebugStringA("Everything is seems to be OK\n");
		}break;
	}
	OutputDebugStringA("\n");
}

#endif