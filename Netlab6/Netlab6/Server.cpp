#include <Windows.h>
#include "../CommonCode/Common.h"

int main(int argc, char** argv){

	char NamedPipeName[] = "\\\\.\\pipe\\NP_NAME";
	HANDLE ServerHandle = CreateNamedPipeA(
		NamedPipeName,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE| PIPE_WAIT,
		1,
		0,
		0,
		INFINITE,
		0);

	if (ServerHandle != INVALID_HANDLE_VALUE){

		ConnectNamedPipe(ServerHandle, 0);

#if !DO_LAB_IN_LOOP
#if THROUGH_READ_AND_WRITE
#if WITH_SLEEPING
		Sleep(100);
#endif
		void* Contents = VirtualAlloc(0, MESSAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		DWORD BytesRead;
		ReadFile(ServerHandle, (char*)Contents, MESSAGE_SIZE, &BytesRead, 0);
		printf("%s\n", Contents);
		VirtualFree(Contents, 0, MEM_RELEASE);

		char WriteBuffer[] = "Hello from Server!";
		DWORD BytesWritten;
		WriteFile(ServerHandle, WriteBuffer, sizeof(WriteBuffer), &BytesWritten, 0);
#else


		char WriteBuffer[] = "Hello from Server!";
		DWORD BytesWritten;
		WriteFile(ServerHandle, WriteBuffer, sizeof(WriteBuffer), &BytesWritten, 0);

		void* Contents = VirtualAlloc(0, MESSAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		DWORD BytesRead;
		ReadFile(ServerHandle, (char*)Contents, MESSAGE_SIZE, &BytesRead, 0);
		printf("%s\n", Contents);
		VirtualFree(Contents, 0, MEM_RELEASE);

		//char OutputBuffer[] = "Hello from Server!";
		//char* InputBuffer = (char*)calloc(256, sizeof(char));
		//DWORD BytesRead;
		//CallNamedPipeA(NamedPipeName, InputBuffer, 256, OutputBuffer, strlen(OutputBuffer) + 1, &BytesRead, 100);
		//printf("%s\n", InputBuffer);
		//free(InputBuffer);
#endif
#else
		for (int i = 0; i < 100; i++){
#if THROUGH_READ_AND_WRITE
#if WITH_SLEEPING
			Sleep(100);
#endif
			void* Contents = VirtualAlloc(0, MESSAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			DWORD BytesRead;
			ReadFile(ServerHandle, (char*)Contents, MESSAGE_SIZE, &BytesRead, 0);
			printf("%s\n", Contents);
			VirtualFree(Contents, 0, MEM_RELEASE);

			char* DestWriteBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
			sprintf(DestWriteBuffer, "Hello from Server. Message - %d\n", i);
			DWORD BytesWritten;
			WriteFile(ServerHandle, DestWriteBuffer, strlen(DestWriteBuffer) + 1, &BytesWritten, 0);
#else
			char* DestWriteBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
			sprintf(DestWriteBuffer, "Hello from Client. Message - %d.\n", i);
			char* InputBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
			DWORD BytesRead;
			CallNamedPipeA(NamedPipeName, InputBuffer, MESSAGE_SIZE, DestWriteBuffer, strlen(DestWriteBuffer) + 1, &BytesRead, 0);
			printf("%s\n", InputBuffer);
			free(DestWriteBuffer);
			free(InputBuffer);
#endif

		}
#endif

		DisconnectNamedPipe(ServerHandle);
		CloseHandle(ServerHandle);

	}
	else{
		CheckNPError();
	}

	system("pause");
	return 0;
}