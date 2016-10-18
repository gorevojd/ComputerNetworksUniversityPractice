#include <Windows.h>
#include <stdio.h>
#include "../CommonCode/common.h"
#include <time.h>

int main(int argc, char** argv){

	char MailSlotName[] = "\\\\.\\mailslot\\MS_NAME";

	DWORD MaxMessageSize = MESSAGE_SIZE;

	HANDLE MailslotHandle = CreateMailslotA(
		MailSlotName,
		MaxMessageSize,
		MAILSLOT_WAIT_FOREVER,
		NULL);
#if !SEND_IN_CYCLE
	DWORD BytesRead;
	char* InputBuffer = (char*)VirtualAlloc(0, MaxMessageSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	BOOL BoolReadResult = ReadFile(
		MailslotHandle,
		InputBuffer,
		MaxMessageSize,
		&BytesRead,
		0);

	printf("%s\n", InputBuffer);

	VirtualFree(InputBuffer, 0, MEM_RELEASE);
#else
	int NumberOfMessagesToSend = NUMBER_OF_MESSAGES_TO_SEND;
	for (int i = 0; i < NumberOfMessagesToSend; i++){
		DWORD BytesRead;
		char* InputBuffer = (char*)VirtualAlloc(0, MaxMessageSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		BOOL BoolReadResult = ReadFile(
			MailslotHandle,
			InputBuffer,
			MaxMessageSize,
			&BytesRead,
			0);

		printf("Read %d bytes from message.\n", BytesRead);
		printf("%i Message read.\n", i);


		VirtualFree(InputBuffer, 0, MEM_RELEASE);
	}


#endif

	CloseHandle(MailslotHandle);

	system("pause");
	return(0);
}