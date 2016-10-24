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

	if (ClientHandle != INVALID_HANDLE_VALUE){

#if !DO_LAB_IN_LOOP
#if THROUGH_READ_AND_WRITE
		char WriteBuffer[] = "Hello from Client";
		DWORD BytesWritten;
		BOOL WriteResult;
		WriteResult = WriteFile(ClientHandle, WriteBuffer, sizeof(WriteBuffer), &BytesWritten, 0);

#if WITH_SLEEPING
		Sleep(100);
#endif
		void* ReadFileResult = VirtualAlloc(0, MESSAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		DWORD BytesRead;
		ReadFile(ClientHandle, (char*)ReadFileResult, MESSAGE_SIZE, &BytesRead, 0);

		printf("%s\n", (char*)ReadFileResult);
#else

		DWORD HandleStateParams  = PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT;
		SetNamedPipeHandleState(ClientHandle, &HandleStateParams, 0, 0);

		//char* InputBuffer = (char*)calloc(256, sizeof(char));
		//char OutputBuffer[] = "Hello from Client!";
		//DWORD BytesRead;
		//TransactNamedPipe(ClientHandle, InputBuffer, 256, OutputBuffer, strlen(OutputBuffer) + 1, &BytesRead, 0);
		//printf("%s\n", InputBuffer);

		//free(InputBuffer);

		char OutputBuffer[] = "Hello from Server!";
		char* InputBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
		DWORD BytesRead;
		if (CallNamedPipeA(NamedPipeName, InputBuffer, MESSAGE_SIZE, OutputBuffer, strlen(OutputBuffer) + 1, &BytesRead, 0)){
			printf("%s\n", InputBuffer);
		}
		else{
			CheckNPError();
		}
		free(InputBuffer);
#endif
#else
		for (int i = 0; i < 100; i++){
#if THROUGH_READ_AND_WRITE
			char* DestWriteBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
			sprintf(DestWriteBuffer, "Hello from Client. Message - %d.\n", i);
			DWORD BytesWritten;
			BOOL WriteResult;
			WriteResult = WriteFile(ClientHandle, DestWriteBuffer, strlen(DestWriteBuffer) + 1, &BytesWritten, 0);
			free(DestWriteBuffer);
#if WITH_SLEEPING
			Sleep(100);
#endif
			void* ReadFileResult = VirtualAlloc(0, MESSAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			DWORD BytesRead;
			ReadFile(ClientHandle, (char*)ReadFileResult, MESSAGE_SIZE, &BytesRead, 0);

			printf("%s\n", (char*)ReadFileResult);
			VirtualFree(ReadFileResult, 0, MEM_RELEASE);
#else

			char* InputBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
			char* OutputDestBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
			sprintf(OutputDestBuffer, "Hello from Server. Message - %d\n", i);
			DWORD BytesRead;
			TransactNamedPipe(ClientHandle, InputBuffer, MESSAGE_SIZE, ClientHandle, strlen(OutputDestBuffer) + 1, &BytesRead, 0);
			printf("%s\n", InputBuffer);

			free(OutputDestBuffer);
			free(InputBuffer);
#endif
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