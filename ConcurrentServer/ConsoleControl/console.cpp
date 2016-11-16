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
		void* ReadFileResult = malloc(MESSAGE_SIZE * sizeof(char));
		DWORD BytesRead;
		ReadFile(((console_thread_context*)param)->ClientHandle, (char*)ReadFileResult, MESSAGE_SIZE, &BytesRead, 0);
		printf("%s\n", (char*)ReadFileResult);
		free(ReadFileResult);
	}

	ExitThread(Result);
	return Result;
}

int main(int argc, char** argv){

	char ComputerHostName[MESSAGE_SIZE];
	printf("Enter server host name (CMD: hostname or \'.\' if on this computer)\n");
	scanf("%s", ComputerHostName);

	char* NamedPipeName = (char*)calloc(MESSAGE_SIZE, sizeof(char));
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
			char* UserCommand = (char*)malloc(MESSAGE_SIZE * sizeof(char));
			printf("Enter command: ");
			scanf("%s", UserCommand);
			for (int i = 0; i < strlen(UserCommand); i++){
				UserCommand[i] = (char)toupper(UserCommand[i]);
			}


			DWORD BytesWritten;
			BOOL WriteResult = WriteFile(ClientHandle, UserCommand, strlen(UserCommand) + 1, &BytesWritten, 0);

			char* Str = (char*)malloc(MESSAGE_SIZE * sizeof(char));
			DWORD BytesRead;
			BOOL ReadResult = ReadFile(ClientHandle, Str, MESSAGE_SIZE, &BytesRead, 0);

			if (strcmp(Str, "Stat mazafaka") != 0){

			}
			else{
				char* StatStr = (char*)malloc(MESSAGE_SIZE * sizeof(char));
				printf("STATISTICS: ");
				DWORD StatBytesRead;
				BOOL StatReadResult = ReadFile(ClientHandle, StatStr, MESSAGE_SIZE, &StatBytesRead, 0);
				printf(StatStr);
				printf("\n");
				free(StatStr);
			}
			
			if (strcmp(UserCommand, "EXIT") == 0){
				ContinueAsking = false;
				break;
			}

			free(Str);

			free(UserCommand);
		}
	}

	free(NamedPipeName);

	system("pause");
	return 0;
}