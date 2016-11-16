#include "../CommonCode/common_code.h"
#include <iostream>
#include <list>

#define CLIENT_IN_CYCLE
#define	CLIENT_CYCLE_COUNT 100

using namespace std;


int main(int argc, char** argv){

	//char ipstr[50];
	//cout << "Enter IP address of the server you want to connect" << endl;
	//cin >> ipstr;

#ifdef CLIENT_IN_CYCLE
	for (int i = 0; i < CLIENT_CYCLE_COUNT; i++){
#endif

		WSADATA WsaData;
		WSAStartup(MAKEWORD(2, 0), &WsaData);
		CheckNetError();

		SOCKET serverSock;
		serverSock = socket(AF_INET, SOCK_STREAM, NULL);
		CheckNetError();


		//char QueryOutputBuffer[] = "Echo";
		char QueryOutputBuffer[64];
		cin >> QueryOutputBuffer;

		//if (strcmp(QueryOutputBuffer, "Echo") != 0 &&
		//	strcmp(QueryOutputBuffer, "Time") != 0 &&
		//	strcmp(QueryOutputBuffer, "Rand") != 0)
		//{
		//	
		//}
		//else{

		//}
		
		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		//serv.sin_addr.s_addr = inet_addr(ipstr);
		serv.sin_addr.s_addr = inet_addr("127.0.0.1");

		//unsigned long nonblk;
		//int tr = ioctlsocket(serverSock, FIONBIO, &(nonblk = 1));

		if (strcmp(QueryOutputBuffer, "Echo") == 0){

			int NumberOfTimes;
			printf("Enter number of messages: ");
			scanf("%d", &NumberOfTimes);

			char* OutputBuffer = (char*)malloc(MESSAGE_SIZE * sizeof(char));
			printf("Enter message: ");
			scanf("%s", OutputBuffer);

			connect(serverSock, (sockaddr*)&serv, sizeof(serv));

			int QuerySentBytesCount = send(serverSock, QueryOutputBuffer, strlen(QueryOutputBuffer) + 1, 0);
			CheckNetError();

			//Here we receive command that we sent to server
			char* RecBuf = (char*)malloc(MESSAGE_SIZE * sizeof(char));
			int RecBytes = recv(serverSock, RecBuf, MESSAGE_SIZE, 0);
			

			for (int i = 0; i < NumberOfTimes; i++){

				char* OutputDestBuffer = (char*)malloc(MESSAGE_SIZE * sizeof(char));
				sprintf(OutputDestBuffer, "%s - %d", OutputBuffer, i);

				int BytesSent = send(serverSock, OutputDestBuffer, strlen(OutputDestBuffer) + 1, NULL);
				CheckNetError();

				char* InputBuffer = (char*)malloc(MESSAGE_SIZE * sizeof(char));
				int BytesReceived = recv(serverSock, InputBuffer, MESSAGE_SIZE, NULL);
				if (BytesReceived != -1){
					printf("%s\n", InputBuffer);
					if (BytesReceived == 1){
						break;
					}
				}

				free(InputBuffer);
				free(OutputDestBuffer);
			}

			char TerminateStr[] = "";
			int TerminateBytesSent = send(serverSock, TerminateStr, strlen(TerminateStr) + 1, 0);
			if (TerminateBytesSent > 0){
				printf("Terminate message sent succesfully: %d bytes.\n", TerminateBytesSent);
			}

			free(RecBuf);
			free(OutputBuffer);
		}
		else{
			connect(serverSock, (sockaddr*)&serv, sizeof(serv));

			int QuerySentBytesCount = send(serverSock, QueryOutputBuffer, strlen(QueryOutputBuffer) + 1, 0);
			CheckNetError();
			
			//Here we receive command that we sent to server
			char* RecBuf = (char*)malloc(MESSAGE_SIZE * sizeof(char));
			int RecBytes = recv(serverSock, RecBuf, MESSAGE_SIZE, 0);

			char* InputBuffer = (char*)malloc(MESSAGE_SIZE * sizeof(char));
			int BytesReceived = recv(serverSock, InputBuffer, MESSAGE_SIZE, NULL);

			if (BytesReceived != -1){
				cout << InputBuffer << endl;
			}

			free(RecBuf);
			free(InputBuffer);
		}

		WSACleanup();
		CheckNetError();

#ifdef CLIENT_IN_CYCLE
	}
#endif

	system("pause");
	return 0;
}