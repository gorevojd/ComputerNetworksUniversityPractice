#include <ctime>
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

	SOCKET serverSock;
	serverSock = socket(AF_INET, SOCK_STREAM, NULL);
	CheckNetError();

	char ipstr[50];
	cout << "Enter IP address of the server you want to connect" << endl;
	cin >> ipstr;

	SOCKADDR_IN serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(2000);
	serv.sin_addr.s_addr = inet_addr(ipstr);
	CheckNetError();

	connect(serverSock, (sockaddr*)&serv, sizeof(serv));
	CheckNetError();
	
	clock_t startTime = clock();
	for (int i = 0; i < 1000; i++){

		char inputBuffer[50];
		char numberStr[6];
		_itoa_s(i, numberStr, 10);
		char outputBuffer[50] = "Hello from Client";
		char* outputDestBuffer = (char*)calloc(strlen(outputBuffer) + strlen(numberStr) + 1, 1);
		memset(outputDestBuffer, 0, sizeof(outputDestBuffer));
		int dlen = 0;
		for (int j = 0; j < strlen(outputBuffer); j++, dlen++){
			outputDestBuffer[j] = outputBuffer[j];
		}
		for (int j = 0; j < strlen(numberStr); j++, dlen++){
			outputDestBuffer[strlen(outputBuffer) + j] = numberStr[j];
		}
		outputDestBuffer[dlen] = 0;
		cout << strlen(numberStr) << endl;
		int receivedBytesCount = 0;
		int sentBytesCount = 0;

		sentBytesCount = send(serverSock, outputDestBuffer, strlen(outputDestBuffer), NULL);
		CheckNetError();

		receivedBytesCount = recv(serverSock, inputBuffer, sizeof(inputBuffer), NULL);
		CheckNetError();

		free(outputDestBuffer);
		cout << inputBuffer << endl;
		
	}
	clock_t endTime = clock();
	int cyclesElapsed = endTime - startTime;
	float wtfTime = cyclesElapsed / CLOCKS_PER_SEC;
	cout << "Connection was " << wtfTime << " seconds length.\n";
	printf("Connection was %f seconds lenght.\n", wtfTime);

	WSACleanup();
	CheckNetError();

	system("pause");
	return 0;
}