#include <iostream>
#include <WinSock2.h>
#include <Windows.h>

using namespace std;

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