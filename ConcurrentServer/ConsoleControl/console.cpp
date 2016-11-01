#include <iostream>
#include "../CommonCode/common_code.h"

using namespace std;

static bool ContinueReceiving = true;
static bool ContinueAsking = true;

struct console_thread_context{
	HANDLE ClientHandle;
};

DWORD WINAPI GetDiagnosticMessagesFromServer(LPVOID param){
	DWORD Result = 0;

	while (ContinueReceiving == true){
		void* ReadFileResult = malloc(256 * sizeof(char));
		DWORD BytesRead;
		ReadFile(((console_thread_context*)param)->ClientHandle, (char*)ReadFileResult, MESSAGE_SIZE, &BytesRead, 0);
		printf("%s\n", (char*)ReadFileResult);
		free(ReadFileResult);
	}

	ExitThread(Result);
	return Result;
}

int main(int argc, char** argv){

	char ComputerHostName[256];
	printf("Enter server host name (CMD: hostname or \'.\' if on this computer)\n");
	scanf("%s", ComputerHostName);

	char* NamedPipeName = (char*)calloc(256, sizeof(char));
	sprintf(NamedPipeName, "\\\\%s\\pipe\\NP_NAME", ComputerHostName);

	HANDLE ClientHandle = CreateFileA(
		NamedPipeName,
		GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		0,
		0);

	if (ClientHandle != INVALID_HANDLE_VALUE){
		while (ContinueAsking == true){
			char* UserCommand = (char*)malloc(256 * sizeof(char));
			printf("Enter command: ");
			scanf("%s", UserCommand);

			DWORD BytesWritten;
			BOOL WriteResult = WriteFile(ClientHandle, UserCommand, strlen(UserCommand) + 1, &BytesWritten, 0);

			free(UserCommand);
		}
	}

	free(NamedPipeName);

	system("pause");
	return 0;
}