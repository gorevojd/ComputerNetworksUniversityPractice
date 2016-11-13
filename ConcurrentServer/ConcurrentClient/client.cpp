#include "../CommonCode/common_code.h"
#include <iostream>
#include <list>

#define CLIENT_IN_CYCLE
#define	CLIENT_CYCLE_COUNT 100

using namespace std;


int main(int argc, char** argv){

#ifdef CLIENT_IN_CYCLE
	for (int i = 0; i < CLIENT_CYCLE_COUNT; i++){
#endif

		WSADATA WsaData;
		WSAStartup(MAKEWORD(2, 0), &WsaData);
		CheckNetError();

		SOCKET serverSock;
		serverSock = socket(AF_INET, SOCK_STREAM, NULL);
		CheckNetError();

		//char ipstr[50];
		//cout << "Enter IP address of the server you want to connect" << endl;
		//cin >> ipstr;
		
		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		//serv.sin_addr.s_addr = inet_addr(ipstr);
		serv.sin_addr.s_addr = inet_addr("127.0.0.1");
		CheckNetError();

		connect(serverSock, (sockaddr*)&serv, sizeof(serv));
		CheckNetError();

		char QueryOutputBuffer[] = "EchoServer";
		int QuerySentBytesCount = send(serverSock, QueryOutputBuffer, strlen(QueryOutputBuffer) + 1, 0);
		CheckNetError();

		char OutputBuffer[] = "Wtf Client";
		int BytesSent = send(serverSock, OutputBuffer, strlen(OutputBuffer) + 1, NULL);
		CheckNetError();

		char* InputBuffer = (char*)malloc(MESSAGE_SIZE * sizeof(char));
		int BytesReceived = recv(serverSock, InputBuffer, MESSAGE_SIZE, NULL);
		CheckNetError();

		cout << InputBuffer << endl;

		WSACleanup();
		CheckNetError();

#ifdef CLIENT_IN_CYCLE
	}
#endif

	system("pause");
	return 0;
}