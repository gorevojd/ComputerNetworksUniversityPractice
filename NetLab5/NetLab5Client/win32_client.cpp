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
	printf("SERVER IP: %s. SERVER PORT: %d.\n", inet_ntoa(info->sin_addr), info->sin_port);
}

void DetectComputerHostName(void){
	char Name[256];
	if (gethostname(Name, sizeof(Name)) >= 0){
		printf("This computer (NetBIOS / DNS) name: %s\n", Name);
	}
	else{
		CheckNetError();
	}
}

bool SendBroadCastMessageToFindServer(
	SOCKET Socket,
	char* ServerName,
	short Port,
	sockaddr* All,
	int AllLen)
{
	bool Result = false;


	((SOCKADDR_IN*)All)->sin_family = AF_INET;
	((SOCKADDR_IN*)All)->sin_port = htons(Port);
	((SOCKADDR_IN*)All)->sin_addr.s_addr = INADDR_BROADCAST;

	int BytesSent = sendto(
		Socket,
		ServerName,
		strlen(ServerName) + 1,
		0,
		All,
		AllLen);

	if (BytesSent > 0){
		Result = true;
	}

	return(Result);
}

void GetServerBySymbolicName(
	SOCKET Socket,
	char* SymbolicName,
	char* Name,
	sockaddr* All,
	int AllLen)
{
	hostent* HostEntity = gethostbyname(SymbolicName);
	for (int i = 0; HostEntity->h_addr_list[i] != 0; i++){
		printf("Host ip: %s\n", HostEntity->h_addr_list[i]);
	}

	unsigned short WantedPort = 2000;
	SendBroadCastMessageToFindServer(
		Socket,
		Name,
		WantedPort,
		All,
		sizeof(*All));

	int AllLen2 = sizeof(*All);
	char InputBuffer[256];
	int ReceivedBytesCount = recvfrom(
		Socket,
		InputBuffer,
		sizeof(InputBuffer),
		0,
		All,
		&AllLen2);
}


int main(int argc, char** argv){

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	CheckNetError();

	SOCKET clientSock = socket(AF_INET, SOCK_DGRAM, 0);
	CheckNetError();

	int optval = 1;
	setsockopt(clientSock, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int));
	CheckNetError();

	char* WantedServerName = "Hello";
	unsigned short WantedPort = 2000;


	printf("Enter computer symbolyc name...\n");
	char HostName[50];
	cin >> HostName;

	DetectComputerHostName();

	SOCKADDR_IN All = {};
	GetServerBySymbolicName(
		clientSock,
		HostName,
		WantedServerName,
		(sockaddr*)&All,
		sizeof(All));
	


	WSACleanup();
	CheckNetError();


	system("pause");
	return(0);
}


