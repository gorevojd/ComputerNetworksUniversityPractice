#include <iostream>
#include "../CommonCode/common_code.h"
using namespace std;

void PrintInfo(sockaddr_in* info){
	printf("SERVER IP: %s. SERVER PORT: %d.\n", inet_ntoa(info->sin_addr), info->sin_port);
}

bool GetServerByName(
	SOCKET Socket,
	char* ServerName,
	char* ServerNick,
	sockaddr* Wtf,
	int WtfLen)
{
	bool Result = false;

	hostent* HostEntity = gethostbyname(ServerName);
	
	((SOCKADDR_IN*)Wtf)->sin_family = AF_INET;
	((SOCKADDR_IN*)Wtf)->sin_addr.s_addr = inet_addr(inet_ntoa(*((in_addr*)HostEntity->h_addr_list[0])));
	((SOCKADDR_IN*)Wtf)->sin_port = htons(2000);

	char OutputBuffer[] = "Hello from Client";

	int BytesSent = sendto(
		Socket,
		OutputBuffer,
		strlen(OutputBuffer) + 1,
		0,
		Wtf,
		WtfLen);

	if (BytesSent > 0){
		Result = true;
	}

	return(Result);
}

int main(int argc, char** argv){

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);

	SOCKET ClientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	CheckNetError();

	char ServerName[50];
	char ServerNick[] = "Hello";
	cout << "Enter server name: ";
	cin >> ServerName;

	SOCKADDR_IN Wtfs = {};
	GetServerByName(
		ClientSocket,
		ServerName,
		ServerNick,
		(sockaddr*)&Wtfs,
		sizeof(Wtfs));

	int WtfsLen = sizeof(WtfsLen);
	char InputBuffer[256];
	int ReceivedBytesCount = recvfrom(
		ClientSocket,
		InputBuffer,
		sizeof(InputBuffer),
		0, (sockaddr*)&Wtfs, &WtfsLen);

	printf("%s\n", InputBuffer);

	WSACleanup();
	CheckNetError();

	system("pause");
	return 0;
}

