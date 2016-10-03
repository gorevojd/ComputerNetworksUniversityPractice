#include <iostream>
#include <ctime>
#include <WinSock2.h>
#include <Windows.h>

using namespace std;

void CheckNetError(){
    int errCode = WSAGetLastError();
    switch (errCode){
        case (WSAEINTR):{
            OutputDebugStringA("WSAEINTR Работа функции прервана");
        }break;
        case(WSAEACCES):{
            OutputDebugStringA("WSAEACCES Разрешение отвергнуто");
        }break;
        case(WSAEFAULT):{
            OutputDebugStringA("WSAEFAULT Ошибочный адрес ");
        }break;
        case(WSAEINVAL):{
            OutputDebugStringA("WSAEINVAL Ошибка в аргументе");
        }break;
        case(WSAEMFILE):{
            OutputDebugStringA("WSAEMFILE Слишком много файлов открыто");
        }break;
        case(WSAEWOULDBLOCK):{
            OutputDebugStringA("WSAEWOULDBLOCK Ресурс временно недоступен");
        }break;
        case(WSAEINPROGRESS):{
            OutputDebugStringA("WSAEINPROGRESS Операция в процессе развития");
        }break;
        case(WSAEALREADY):{
            OutputDebugStringA("WSAEALREADY Операция уже выполняется");
        }break;
        case(WSAENOTSOCK):{
            OutputDebugStringA("WSAENOTSOCK Сокет задан неправильно");
        }break;
        case(WSAEDESTADDRREQ):{
            OutputDebugStringA("WSAEDESTADDRREQ Требуется адрес расположения ");
        }break;
        case(WSAEMSGSIZE):{
            OutputDebugStringA("WSAEMSGSIZE Сообщение слишком длинное");
        }break;
        case(WSAEPROTOTYPE):{
            OutputDebugStringA("WSAEPROTOTYPE Неправильный тип протокола для сокета");
        }break;
        case(WSAENOPROTOOPT):{
            OutputDebugStringA("WSAENOPROTOOPT Ошибка в опции протокола");
        }break;
        case(WSAEPROTONOSUPPORT):{
            OutputDebugStringA("WSAEPROTONOSUPPORT Протокол не поддерживается ");
        }break;
        case(WSAESOCKTNOSUPPORT):{
            OutputDebugStringA("WSAESOCKTNOSUPPORT Тип сокета не поддерживается ");
        }break;
        case(WSAEOPNOTSUPP):{
            OutputDebugStringA("WSAEOPNOTSUPP Операция не поддерживается ");
        }break;
        case(WSAEPFNOSUPPORT):{
            OutputDebugStringA("WSAEPFNOSUPPORT Тип протоколов не поддерживается");
        }break;
        case(WSAEAFNOSUPPORT):{
            OutputDebugStringA("WSAEAFNOSUPPORT Тип адресов не поддерживается протоколом");
        }break;
        case(WSAEADDRINUSE):{
            OutputDebugStringA("WSAEADDRINUSE Адрес уже используется");
        }break;
        case(WSAEADDRNOTAVAIL):{
            OutputDebugStringA("WSAEADDRNOTAVAIL Запрошенный адрес не может быть использован");
        }break;
        case(WSAENETDOWN):{
            OutputDebugStringA("WSAENETDOWN Сеть отключена");
        }break;
        case(WSAENETUNREACH):{
            OutputDebugStringA("WSAENETUNREACH Сеть не достижима ");
        }break;
        case(WSAENETRESET):{
            OutputDebugStringA("WSAENETRESET Сеть разорвала соединение");
        }break;
        case(WSAECONNABORTED):{
            OutputDebugStringA("WSAECONNABORTED Программный отказ связи ");
        }break;
        case(WSAECONNRESET):{
            OutputDebugStringA("WSAECONNRESET Связь восстановлена ");
        }break;
        case(WSAENOBUFS):{
            OutputDebugStringA("WSAENOBUFS Не хватает памяти для буферов");
        }break;
        case(WSAEISCONN):{
            OutputDebugStringA("WSAEISCONN Сокет уже подключен");
        }break;
        case(WSAENOTCONN):{
            OutputDebugStringA("WSAENOTCONN Сокет не подключен");
        }break;
        case(WSAESHUTDOWN):{
            OutputDebugStringA("WSAESHUTDOWN Нельзя выполнить send: сокет завершил работу");
        }break;
        case(WSAETIMEDOUT):{
            OutputDebugStringA("WSAETIMEDOUT Закончился отведенный интервал  времени");
        }break;
        case(WSAECONNREFUSED):{
            OutputDebugStringA("WSAECONNREFUSED Соединение отклоненo");
        }break;
        case(WSAEHOSTDOWN):{
            OutputDebugStringA("WSAEHOSTDOWN Хост в неработоспособном состоянии");
        }break;
        case(WSAEHOSTUNREACH):{
            OutputDebugStringA("WSAEHOSTUNREACH Нет маршрута для хоста");
        }break;
        case(WSAEPROCLIM):{
            OutputDebugStringA("WSAEPROCLIM Слишком много процессов ");
        }break;
        case(WSASYSNOTREADY):{
            OutputDebugStringA("WSASYSNOTREADY Сеть не доступна ");
        }break;
        case(WSAVERNOTSUPPORTED):{
            OutputDebugStringA("WSAVERNOTSUPPORTED Данная версия недоступна ");
        }break;
        case(WSANOTINITIALISED):{
            OutputDebugStringA("WSANOTINITIALISED Не выполнена инициализация WS2_32.DLL");
        }break;
        case(WSAEDISCON):{
            OutputDebugStringA("WSAEDISCON Выполняется отключение");
        }break;
        case(WSATYPE_NOT_FOUND):{
            OutputDebugStringA("WSATYPE_NOT_FOUND Класс не найден");
        }break;
        case(WSAHOST_NOT_FOUND):{
            OutputDebugStringA("WSAHOST_NOT_FOUND Хост не найден ");
        }break;
        case(WSATRY_AGAIN):{
            OutputDebugStringA("WSATRY_AGAIN Неавторизированный хост не найден ");
        }break;
        case(WSANO_RECOVERY):{
            OutputDebugStringA("WSANO_RECOVERY Неопределенная  ошибка");
        }break;
        case(WSANO_DATA):{
            OutputDebugStringA("WSANO_DATA Нет записи запрошенного типа");
        }break;
        case(WSA_INVALID_HANDLE):{
            OutputDebugStringA("WSA_INVALID_HANDLE Указанный дескриптор события  с ошибкой");
        }break;
        case(WSA_INVALID_PARAMETER):{
            OutputDebugStringA("WSA_INVALID_PARAMETER Один или более параметров с ошибкой");
        }break;
        case(WSA_IO_INCOMPLETE):{
            OutputDebugStringA("WSA_IO_INCOMPLETE Объект ввода-вывода не в сигнальном состоянии");
        }break;
        case(WSA_IO_PENDING):{
            OutputDebugStringA("WSA_IO_PENDING Операция завершится позже");
        }break;
        case(WSA_NOT_ENOUGH_MEMORY):{
            OutputDebugStringA("WSA_NOT_ENOUGH_MEMORY Не достаточно памяти");
        }break;
        case(WSA_OPERATION_ABORTED):{
            OutputDebugStringA("WSA_OPERATION_ABORTED Операция отвергнута");
        }break;
        case(0):{
            OutputDebugStringA("Everything is seems to be OK\n");
        }break;
    }
}

//SERVER
int main(int argc, char** argv){

	WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);
    CheckNetError();

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, NULL);
    CheckNetError();

    SOCKADDR_IN serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(2000);
    serv.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (LPSOCKADDR)&serv, sizeof(serv));
    CheckNetError();

    listen(serverSock, SOMAXCONN);
    CheckNetError();

	bool b = true;
	
	while (b){
		SOCKET clientSock;
		SOCKADDR_IN clnt = {};
		int sizeClient = sizeof(clnt);
		clientSock = accept(serverSock, (sockaddr*)&clnt, &sizeClient);
		CheckNetError();

		clock_t startTime = clock();
		for(int i = 0; i < 1000; i++){
			char inputBuffer[50];
			char outputBuffer[50] = "Hello from server";
			char outputDestBuffer[50];
			memset(outputDestBuffer, 0, sizeof(outputDestBuffer));
		
			char numberStr[6];
			_itoa_s(i, numberStr, 10);
			int dlen = 0;
			for (int j = 0; j < strlen(outputBuffer); j++, dlen++){
				outputDestBuffer[j] = outputBuffer[j];
			}
			for (int j = 0; j < strlen(numberStr); j++, dlen++){
				outputDestBuffer[strlen(outputBuffer) + j] = numberStr[j];
			}
			outputDestBuffer[dlen] = '\0';

			int receivedBytesCount = 0;
			int sentBytesCount = 0;

			receivedBytesCount = recv(clientSock, inputBuffer, sizeof(inputBuffer), NULL);
			CheckNetError();

			cout << inputBuffer << endl;
			cout << clnt.sin_port << endl;
			cout << inet_ntoa(clnt.sin_addr) << endl;

			sentBytesCount = send(clientSock, outputDestBuffer, strlen(outputDestBuffer), NULL);
			CheckNetError();
		}
		clock_t endTime = clock();
		int elapsedCycles = endTime - startTime;
		float wtfTime = elapsedCycles / CLOCKS_PER_SEC;
		cout << "Connection was " << wtfTime << " second length.\n";

#if 0
		cout << "Do you want to accept one more client? (yes/no)" << endl;
		
		char answ[10];
		cin >> answ;
		if (answ == "yes"){

		}
		else if (answ == "no"){
			b = false;
		}
#endif
	}
    
    closesocket(serverSock);
    CheckNetError();
    
    WSACleanup();
    CheckNetError();
	
	system("pause");
    return 0;
}
