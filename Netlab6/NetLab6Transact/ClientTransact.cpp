#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "../CommonCode/Common.h"

using namespace std;

int main(int argc, char** argv){

#if 1
	char CompName[256];
	cout << "Enter computer host name: ";
	cin >> CompName;

	char* NamedPipeName = (char*)calloc(256, sizeof(char));

	sprintf(NamedPipeName, "\\\\%s\\pipe\\NP_NAME", CompName);

#else
	char NamedPipeName[] = "\\\\.\\pipe\\NP_NAME";
#endif

	HANDLE ClientHandle = CreateFileA(
		NamedPipeName,
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		0,
		0);

	DWORD Mode = PIPE_READMODE_MESSAGE;
	SetNamedPipeHandleState(ClientHandle, &Mode, 0, 0);

	if (ClientHandle != INVALID_HANDLE_VALUE){

#if !DO_LAB_IN_LOOP
		char OutputBuffer[] = "Hello from Client!";
		char* InputBuffer = (char*)calloc(256, sizeof(char));
		DWORD BytesRead;
		TransactNamedPipe(ClientHandle, OutputBuffer, strlen(OutputBuffer) + 1, InputBuffer, MESSAGE_SIZE, &BytesRead, 0);
		printf("%s\n", InputBuffer);
		free(InputBuffer);
#else
		for (int i = 0; i < 100; i++){
			char OutputBuffer[] = "Hello from Client!";
			char* InputBuffer = (char*)calloc(256, sizeof(char));
			DWORD BytesRead;
			TransactNamedPipe(ClientHandle, InputBuffer, 256, OutputBuffer, strlen(OutputBuffer) + 1, &BytesRead, 0);
			printf("%s\n", InputBuffer);
			free(InputBuffer);
		}
#endif

		CloseHandle(ClientHandle);
	}
	else{
		CheckNPError();
	}



	system("pause");
	return 0;
}