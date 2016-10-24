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
		void* Contents = VirtualAlloc(0, MESSAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		DWORD BytesRead;
		ReadFile(ServerHandle, (char*)Contents, MESSAGE_SIZE, &BytesRead, 0);
		printf("%s\n", (char*)Contents);
		VirtualFree(Contents, 0, MEM_RELEASE);

		char WriteBuffer[] = "Hello from Server!";
		DWORD BytesWritten;
		WriteFile(ServerHandle, WriteBuffer, sizeof(WriteBuffer), &BytesWritten, 0);
#else
		for (int i = 0; i < 100; i++){
			void* Contents = VirtualAlloc(0, MESSAGE_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
			DWORD BytesRead;
			ReadFile(ServerHandle, (char*)Contents, MESSAGE_SIZE, &BytesRead, 0);
			printf("%s\n", Contents);
			VirtualFree(Contents, 0, MEM_RELEASE);

			char* DestWriteBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
			sprintf(DestWriteBuffer, "Hello from Server. Message - %d\n", i);
			DWORD BytesWritten;
			WriteFile(ServerHandle, DestWriteBuffer, strlen(DestWriteBuffer) + 1, &BytesWritten, 0);
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