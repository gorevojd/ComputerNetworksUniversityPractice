#include <iostream>
#include <WinSock2.h>
#include <Windows.h>

using namespace std;

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
	case(WSA_INVALID_HANDLE) : {
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
	}break;
	case(0) : {
		OutputDebugStringA("Everything is seems to be OK\n");
	}break;
	}
}


//CLIENT
int main(int argc, char** argv){

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	CheckNetError();

	SOCKET clientSock = socket(AF_INET, SOCK_DGRAM, NULL);
	CheckNetError();

	char ipstr[50];
	cout << "Enter IP: \n";
	cin >> ipstr;


	SOCKADDR_IN serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(2000);
	serv.sin_addr.s_addr = inet_addr(ipstr);

	int messagesSent = 0;
	for (int i = 0; i < 1000; i++, messagesSent++){

		char outputBuffer[] = "Hello from client";
		char* outputDestBuffer = (char*)calloc(50, sizeof(char));
		int sentByteCount = 0;

		char numStr[10];
		_itoa_s(i, numStr, 10);
		int numStrLen = strlen(numStr);

		//for (int j = 0; j < strlen(outputBuffer); j++){
		//	outputDestBuffer[j] = outputBuffer[j];
		//}
		strcpy(outputDestBuffer, outputBuffer);
		for (int j = 0; j < numStrLen; j++){
			outputDestBuffer[strlen(outputBuffer) + j] = numStr[j];
		}

		sentByteCount = sendto(
			clientSock,
			outputDestBuffer,
			strlen(outputDestBuffer) + 1,
			0,
			(sockaddr*)&serv,
			sizeof(serv));

		free(outputDestBuffer);
	}

	printf("Total messages sent: %d\n", messagesSent);

	closesocket(clientSock);
	CheckNetError();

	WSACleanup();
	CheckNetError();

	system("pause");
	return 0;
}