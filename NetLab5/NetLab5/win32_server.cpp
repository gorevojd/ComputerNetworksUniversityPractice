
#include <iostream>
using namespace std;

#include <WinSock2.h>
#include <Windows.h>

void CheckNetError(){
	int errCode = WSAGetLastError();
	switch (errCode){
		case (WSAEINTR) : {
			OutputDebugStringA("WSAEINTR ������ ������� ��������");
		}break;
		case(WSAEACCES) : {
			OutputDebugStringA("WSAEACCES ���������� ����������");
		}break;
		case(WSAEFAULT) : {
			OutputDebugStringA("WSAEFAULT ��������� ����� ");
		}break;
		case(WSAEINVAL) : {
			OutputDebugStringA("WSAEINVAL ������ � ���������");
		}break;
		case(WSAEMFILE) : {
			OutputDebugStringA("WSAEMFILE ������� ����� ������ �������");
		}break;
		case(WSAEWOULDBLOCK) : {
			OutputDebugStringA("WSAEWOULDBLOCK ������ �������� ����������");
		}break;
		case(WSAEINPROGRESS) : {
			OutputDebugStringA("WSAEINPROGRESS �������� � �������� ��������");
		}break;
		case(WSAEALREADY) : {
			OutputDebugStringA("WSAEALREADY �������� ��� �����������");
		}break;
		case(WSAENOTSOCK) : {
			OutputDebugStringA("WSAENOTSOCK ����� ����� �����������");
		}break;
		case(WSAEDESTADDRREQ) : {
			OutputDebugStringA("WSAEDESTADDRREQ ��������� ����� ������������ ");
		}break;
		case(WSAEMSGSIZE) : {
			OutputDebugStringA("WSAEMSGSIZE ��������� ������� �������");
		}break;
		case(WSAEPROTOTYPE) : {
			OutputDebugStringA("WSAEPROTOTYPE ������������ ��� ��������� ��� ������");
		}break;
		case(WSAENOPROTOOPT) : {
			OutputDebugStringA("WSAENOPROTOOPT ������ � ����� ���������");
		}break;
		case(WSAEPROTONOSUPPORT) : {
			OutputDebugStringA("WSAEPROTONOSUPPORT �������� �� �������������� ");
		}break;
		case(WSAESOCKTNOSUPPORT) : {
			OutputDebugStringA("WSAESOCKTNOSUPPORT ��� ������ �� �������������� ");
		}break;
		case(WSAEOPNOTSUPP) : {
			OutputDebugStringA("WSAEOPNOTSUPP �������� �� �������������� ");
		}break;
		case(WSAEPFNOSUPPORT) : {
			OutputDebugStringA("WSAEPFNOSUPPORT ��� ���������� �� ��������������");
		}break;
		case(WSAEAFNOSUPPORT) : {
			OutputDebugStringA("WSAEAFNOSUPPORT ��� ������� �� �������������� ����������");
		}break;
		case(WSAEADDRINUSE) : {
			OutputDebugStringA("WSAEADDRINUSE ����� ��� ������������");
		}break;
		case(WSAEADDRNOTAVAIL) : {
			OutputDebugStringA("WSAEADDRNOTAVAIL ����������� ����� �� ����� ���� �����������");
		}break;
		case(WSAENETDOWN) : {
			OutputDebugStringA("WSAENETDOWN ���� ���������");
		}break;
		case(WSAENETUNREACH) : {
			OutputDebugStringA("WSAENETUNREACH ���� �� ��������� ");
		}break;
		case(WSAENETRESET) : {
			OutputDebugStringA("WSAENETRESET ���� ��������� ����������");
		}break;
		case(WSAECONNABORTED) : {
			OutputDebugStringA("WSAECONNABORTED ����������� ����� ����� ");
		}break;
		case(WSAECONNRESET) : {
			OutputDebugStringA("WSAECONNRESET ����� ������������� ");
		}break;
		case(WSAENOBUFS) : {
			OutputDebugStringA("WSAENOBUFS �� ������� ������ ��� �������");
		}break;
		case(WSAEISCONN) : {
			OutputDebugStringA("WSAEISCONN ����� ��� ���������");
		}break;
		case(WSAENOTCONN) : {
			OutputDebugStringA("WSAENOTCONN ����� �� ���������");
		}break;
		case(WSAESHUTDOWN) : {
			OutputDebugStringA("WSAESHUTDOWN ������ ��������� send: ����� �������� ������");
		}break;
		case(WSAETIMEDOUT) : {
			OutputDebugStringA("WSAETIMEDOUT ���������� ���������� ��������  �������");
		}break;
		case(WSAECONNREFUSED) : {
			OutputDebugStringA("WSAECONNREFUSED ���������� ��������o");
		}break;
		case(WSAEHOSTDOWN) : {
			OutputDebugStringA("WSAEHOSTDOWN ���� � ����������������� ���������");
		}break;
		case(WSAEHOSTUNREACH) : {
			OutputDebugStringA("WSAEHOSTUNREACH ��� �������� ��� �����");
		}break;
		case(WSAEPROCLIM) : {
			OutputDebugStringA("WSAEPROCLIM ������� ����� ��������� ");
		}break;
		case(WSASYSNOTREADY) : {
			OutputDebugStringA("WSASYSNOTREADY ���� �� �������� ");
		}break;
		case(WSAVERNOTSUPPORTED) : {
			OutputDebugStringA("WSAVERNOTSUPPORTED ������ ������ ���������� ");
		}break;
		case(WSANOTINITIALISED) : {
			OutputDebugStringA("WSANOTINITIALISED �� ��������� ������������� WS2_32.DLL");
		}break;
		case(WSAEDISCON) : {
			OutputDebugStringA("WSAEDISCON ����������� ����������");
		}break;
		case(WSATYPE_NOT_FOUND) : {
			OutputDebugStringA("WSATYPE_NOT_FOUND ����� �� ������");
		}break;
		case(WSAHOST_NOT_FOUND) : {
			OutputDebugStringA("WSAHOST_NOT_FOUND ���� �� ������ ");
		}break;
		case(WSATRY_AGAIN) : {
			OutputDebugStringA("WSATRY_AGAIN ������������������ ���� �� ������ ");
		}break;
		case(WSANO_RECOVERY) : {
			OutputDebugStringA("WSANO_RECOVERY ��������������  ������");
		}break;
		case(WSANO_DATA) : {
			OutputDebugStringA("WSANO_DATA ��� ������ ������������ ����");
		}break;
		case(WSA_INVALID_HANDLE) : {
			OutputDebugStringA("WSA_INVALID_HANDLE ��������� ���������� �������  � �������");
		}break;
		case(WSA_INVALID_PARAMETER) : {
			OutputDebugStringA("WSA_INVALID_PARAMETER ���� ��� ����� ���������� � �������");
		}break;
		case(WSA_IO_INCOMPLETE) : {
			OutputDebugStringA("WSA_IO_INCOMPLETE ������ �����-������ �� � ���������� ���������");
		}break;
		case(WSA_IO_PENDING) : {
			OutputDebugStringA("WSA_IO_PENDING �������� ���������� �����");
		}break;
		case(WSA_NOT_ENOUGH_MEMORY) : {
			OutputDebugStringA("WSA_NOT_ENOUGH_MEMORY �� ���������� ������");
		}break;
		case(WSA_OPERATION_ABORTED) : {
			OutputDebugStringA("WSA_OPERATION_ABORTED �������� ����������");
		}break;
		case(0) : {
			OutputDebugStringA("Everything is seems to be OK\n");
		}break;
	}
	OutputDebugStringA("\n");
}

void PrintInfo(sockaddr_in* info){
	printf("IP: %s. PORT: %d.\n", inet_ntoa(info->sin_addr), info->sin_port);
}
#if 0
bool GetRequestFromClient(
	SOCKET ServerSocket,
	char* ServerName,
	unsigned short port,
	sockaddr* Clnt,
	int* ClntLen)
{
	bool Result = false;

	SOCKADDR_IN* Serv = {};
	((SOCKADDR_IN*)Serv)->sin_family = AF_INET;
	((SOCKADDR_IN*)Serv)->sin_port = htons(port);
	((SOCKADDR_IN*)Serv)->sin_addr.s_addr = INADDR_ANY;

	if (bind(ServerSocket, (LPSOCKADDR)Serv, sizeof(Serv)) >= 0){

		int receivedByteCount = recvfrom(
			ServerSocket,
			ServerName,
			strlen(ServerName) + 1,
			0,
			Clnt,
			ClntLen);

		if (receivedByteCount > 0){
			Result = true;
		}
		else{
			CheckNetError();
		}
	}
	else{
		CheckNetError();
	}

	return(Result);
}

bool SendAnswerToClient(
	SOCKET ServerSocket,
	char* ServerName,
	int ServerNameLen,
	sockaddr* TargetClient,
	int TargetClientLen)
{
	bool Result = false;

	int SentBytesCount = sendto(
		ServerSocket,
		ServerName,
		ServerNameLen,
		0,
		TargetClient,
		TargetClientLen);

	return(Result);
}

#endif


bool CheckForAnotherServerWithName(char* ServerName){
	bool Result = false;

	SOCKET AnotherSocket = socket(AF_INET, SOCK_DGRAM, NULL);
	CheckNetError();

	int optval = 1;
	int TimeOut = 1000;
	setsockopt(AnotherSocket, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int));
	setsockopt(AnotherSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&TimeOut, sizeof(TimeOut));
	CheckNetError();

	SOCKADDR_IN All = {};
	All.sin_family = AF_INET;
	All.sin_port = htons(2000);
	All.sin_addr.s_addr = INADDR_BROADCAST;

	int BytesSent = sendto(
		AnotherSocket,
		ServerName,
		strlen(ServerName) + 1,
		0,
		(sockaddr*)&All,
		sizeof(All));

	if (BytesSent > 0){

		char RequestedServerName[50];

		int AllLen = sizeof(All);

		int receivedByteCount = recvfrom(
			AnotherSocket,
			RequestedServerName,
			sizeof(RequestedServerName),
			0,
			(sockaddr*)&All,
			&AllLen);
		if (receivedByteCount > 0){
			int StringsAreEqual = strcmp(ServerName, RequestedServerName);

			if (StringsAreEqual == 0){
				cout << "Computer with this name alredy exists!!!!!!!!!!!!!!!!!!\n";
				Result = true;
			}
			else{
				CheckNetError();
			}
		}
		else{
			cout << "No servers in network.\n";
			CheckNetError();
		}
	}

	closesocket(AnotherSocket);
	CheckNetError();

	return Result;
}

bool GetRequestFromClient(
	SOCKET ServerSocket,
	char* ServerName,
	unsigned short port,
	sockaddr* Clnt,
	int* ClntLen)
{
	bool Result = false;

	SOCKADDR_IN Serv = {};
	((SOCKADDR_IN*)&Serv)->sin_family = AF_INET;
	((SOCKADDR_IN*)&Serv)->sin_port = htons(port);
	((SOCKADDR_IN*)&Serv)->sin_addr.s_addr = INADDR_ANY;

	if (bind(ServerSocket, (LPSOCKADDR)&Serv, sizeof(Serv)) >= 0){

		int receivedByteCount = recvfrom(
			ServerSocket,
			ServerName,
			strlen(ServerName) + 1,
			0,
			Clnt,
			ClntLen);

		if (receivedByteCount > 0){
			Result = true;
		}
		else{
			CheckNetError();
		}
	}
	else{
		CheckNetError();
	}

	return(Result);
}

bool SendAnswerToClient(
	SOCKET ServerSocket,
	char* ServerName,
	int ServerNameLen,
	sockaddr* TargetClient,
	int TargetClientLen)
{
	bool Result = false;

	int SentBytesCount = sendto(
		ServerSocket,
		ServerName,
		ServerNameLen,
		0,
		TargetClient,
		TargetClientLen);

	return(Result);
}




int main(int argc, char** argv){

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	CheckNetError();

	char ServerName[] = "Hello";
	CheckForAnotherServerWithName(ServerName);

	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, NULL);
	CheckNetError();

	bool Receiving = true;
	while (Receiving == true){
		char RequestStr[50];
		SOCKADDR_IN Clnt = {};
		int ClientLen = sizeof(Clnt);

		char QueryName[50];
		GetRequestFromClient(ServerSocket, QueryName, sizeof(QueryName), (sockaddr*)&Clnt, &ClientLen);
		if (strcmp(ServerName, QueryName) == 0){
			SendAnswerToClient(
				ServerSocket,
				ServerName,
				strlen(ServerName) + 1,
				(sockaddr*)&Clnt,
				ClientLen);

			PrintInfo(&Clnt);
	

		}
	}

	closesocket(ServerSocket);
	CheckNetError();

	WSACleanup();
	CheckNetError();


	system("pause");
	return(0);
}


