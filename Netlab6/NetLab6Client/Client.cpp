#include <Windows.h>
#include <stdio.h>
#include "../CommonCode/Common.h"

int main(int argc, char** argv){

#if 0
	char CompName[256];
	cout << "Enter computer host name: ";
	cin >> CompName;

	char* NamedPipeName = (char*)calloc(256, sizeof(char));
	int StrPos = 0;
	for (int i = 0; i < 4; i++){
		NamedPipeName[i] = '\\';
	}
	StrPos = 4;

	for (int i = 0; i < strlen(CompName); i++){
		NamedPipeName[i + StrPos] = CompName[i];
		StrPos++;
	}

	char EndOfName[] = "\\pipe\\NP_NAME";
	for (int i = 0; i < strlen(EndOfName); i++){
		NamedPipeName[i + StrPos] = EndOfName[i];
	}
	NamedPipeName[StrPos] = 0;

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

		Sleep(100);
		LARGE_INTEGER FileSize;
		GetFileSizeEx(ClientHandle, &FileSize);
		void* ReadFileResult = VirtualAlloc(0, FileSize.QuadPart, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		//char ReadFileResult[256];
		DWORD BytesRead;
		ReadFile(ClientHandle, (char*)ReadFileResult, FileSize.QuadPart, &BytesRead, 0);

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
		char* InputBuffer = (char*)calloc(256, sizeof(char));
		DWORD BytesRead;
		if (CallNamedPipeA(NamedPipeName, InputBuffer, 256, OutputBuffer, strlen(OutputBuffer) + 1, &BytesRead, 0)){
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
			char* DestWriteBuffer = (char*)calloc(256, sizeof(char));
			sprintf(DestWriteBuffer, "Hello from Client. Message - %d.\n", i);
			DWORD BytesWritten;
			BOOL WriteResult;
			WriteResult = WriteFile(ClientHandle, DestWriteBuffer, strlen(DestWriteBuffer) + 1, &BytesWritten, 0);
			free(DestWriteBuffer);

			Sleep(100);
			LARGE_INTEGER FileSize;
			GetFileSizeEx(ClientHandle, &FileSize);
			void* ReadFileResult = VirtualAlloc(0, FileSize.QuadPart, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			//char ReadFileResult[256];
			DWORD BytesRead;
			ReadFile(ClientHandle, (char*)ReadFileResult, FileSize.QuadPart, &BytesRead, 0);

			printf("%s\n", (char*)ReadFileResult);
			VirtualFree(ReadFileResult, 0, MEM_RELEASE);
#else

			char* InputBuffer = (char*)calloc(256, sizeof(char));
			char* OutputDestBuffer = (char*)calloc(256, sizeof(char));
			sprintf(OutputDestBuffer, "Hello from Server. Message - %d\n", i);
			DWORD BytesRead;
			TransactNamedPipe(ClientHandle, InputBuffer, 256, ClientHandle, strlen(OutputDestBuffer) + 1, &BytesRead, 0);
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