
#include <iostream>
#include "../CommonCode/common_code.h"

using namespace std;


char* GetThisComputerHostHame(){
	char* Result = (char*)calloc(256, sizeof(char));
	gethostname(Result, 256);
	cout << "This computer host name: " << Result << endl;
	return(Result);
}

char* GetConnectedClientsName(sockaddr* Wtf){
	char* AddrStr = inet_ntoa(((SOCKADDR_IN*)Wtf)->sin_addr);
	//hostent* HostEntity = gethostbyaddr(AddrStr, strlen(AddrStr), AF_INET);
	in_addr ipv4addr;
	inet_pton(AF_INET, AddrStr, &ipv4addr);
	hostent* HostEntity = gethostbyaddr((char*)&ipv4addr, sizeof(ipv4addr), AF_INET);
	char* Result = (char*)malloc(sizeof(char) * (strlen(HostEntity->h_name) + 1));
	strcpy(Result, HostEntity->h_name);
	cout << "Connected client host name: " << Result << endl;
	return(Result);
}

bool CheckForAnotherServerWithNick(char* ServerNick){
	bool Result = false;

	SOCKET AnotherSocket = socket(AF_INET, SOCK_DGRAM, 0);
	CheckNetError();

	int OptionalValue = 1;
	int TimeOut = 1000;
	setsockopt(AnotherSocket, SOL_SOCKET, SO_BROADCAST, (char*)&OptionalValue, sizeof(int));
	setsockopt(AnotherSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&TimeOut, sizeof(TimeOut));
	CheckNetError();

	
	SOCKADDR_IN Wtfs = {};
	Wtfs.sin_family = AF_INET;
	Wtfs.sin_port = htons(2000);
	Wtfs.sin_addr.s_addr = INADDR_BROADCAST;
	
	int BytesSent = sendto(
		AnotherSocket,
		ServerNick,
		strlen(ServerNick) + 1,
		0,
		(sockaddr*)&Wtfs,
		sizeof(Wtfs));

	if (BytesSent > 0){
		char RequestedServerName[50];
		int AllLen = sizeof(Wtfs);

		int ReceivedBytesCount = recvfrom(
			AnotherSocket,
			RequestedServerName,
			sizeof(RequestedServerName),
			0,
			(sockaddr*)&Wtfs,
			&AllLen);

		if (ReceivedBytesCount > 0){
			int StringsAreEqual = strcmp(ServerNick, RequestedServerName);
			if (StringsAreEqual == 0){
				cout << "Computer with this name alredy exists!!!!!!!!!!!!!!!!\n";
				Result = true;
			}
			else{
				CheckNetError();
			}
		}
		else{
			cout << "No serveers in network.\n";
			CheckNetError();
		}
	}

	closesocket(AnotherSocket);
	CheckNetError();

	return(Result);
}

bool GetRequestFromClient(
	SOCKET ServerSocket,
	char* ServerName,
	int ServerNameLen,
	sockaddr* Clnt,
	int* ClntLen)
{
	bool Result = false;

	int ReceivedByteCount = recvfrom(
		ServerSocket,
		ServerName,
		ServerNameLen,
		0,
		Clnt,
		ClntLen);
	if (ReceivedByteCount > 0){
		Result = true;
	}
	else{
		CheckNetError();
	}

	return(Result);
}

bool SendRequestToClient(
	SOCKET ServerSocket,
	char* ServerName,
	sockaddr* TargetClient,
	int TargetClientLen)
{
	bool Result = false;
	int SentBytesCount = sendto(
		ServerSocket,
		ServerName,
		strlen(ServerName) + 1,
		0,
		TargetClient,
		TargetClientLen);
	
	if (SentBytesCount > 0){
		Result = true;
	}

	return(Result);
}

int main(int argc, char** argv){

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 0), &wsaData);
	CheckNetError();

	char ServerNick[] = "Hello";

	CheckForAnotherServerWithNick(ServerNick);
	GetThisComputerHostHame();

	SOCKET ServerSocket = socket(AF_INET, SOCK_DGRAM, 0);
	CheckNetError();

	SOCKADDR_IN Serv;
	Serv.sin_family = AF_INET;
	Serv.sin_port = htons(2000);
	Serv.sin_addr.s_addr = INADDR_ANY;
	if (bind(ServerSocket, (LPSOCKADDR)&Serv, sizeof(Serv)) >= 0){
		bool Receiving = true;
		while (Receiving == true){
			char ClientMessage[256];
			SOCKADDR_IN Clnt = {};
			int ClientLen = sizeof(Clnt);

			if (GetRequestFromClient(
				ServerSocket,
				ClientMessage,
				sizeof(ClientMessage),
				(sockaddr*)&Clnt,
				&ClientLen))
			{
				int StringsAreEqual = strcmp(ServerNick, ClientMessage);
				if (StringsAreEqual == 0)
				{
					SendRequestToClient(
						ServerSocket,
						ServerNick,
						(sockaddr*)&Clnt,
						ClientLen);
					continue;
				}
			
				char OutputBuffer[] = "Hello from Server.\n";
				SendRequestToClient(
					ServerSocket,
					OutputBuffer,
					(sockaddr*)&Clnt,
					ClientLen);
			
				GetConnectedClientsName((sockaddr*)&Clnt);
			}
			else{

			}
		}
	}
	else{
		CheckNetError();
	}

	closesocket(ServerSocket);
	CheckNetError();

	WSACleanup();
	CheckNetError();

	system("pause");
	return 0;
}