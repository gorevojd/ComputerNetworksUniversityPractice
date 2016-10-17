#include <Windows.h>
#include <stdio.h>
#include "../CommonCode/common.h"




int main(int argc, char** argv){

#if 0
	char CompName[256];
	cout << "Enter computer host name: ";
	cin >> CompName;

	char* MailSlotName = (char*)calloc(256, sizeof(char));
	int StrPos = 0;
	for (int i = 0; i < 4; i++){
		MailSlotName[i] = '\\';
	}
	StrPos = 4;

	for (int i = 0; i < strlen(CompName); i++){
		MailSlotName[i + StrPos] = CompName[i];
		StrPos++;
	}

	char EndOfName[] = "\\mailslot\\MS_NAME";
	for (int i = 0; i < strlen(EndOfName); i++){
		MailSlotName[i + StrPos] = EndOfName[i];
	}
	MailSlotName[StrPos] = 0;

#else
	char MailSlotName[] = "\\\\.\\mailslot\\MS_NAME";
#endif

	HANDLE ClientHandle = CreateFileA(
		MailSlotName,
		GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0,
		OPEN_EXISTING,
		0,
		0);


#if !SEND_IN_CYCLE
	char OutputBuffer[] = "Hello from Client!";
	DWORD BytesWritten;
	BOOL WriteFileResult = WriteFile(
		ClientHandle,
		OutputBuffer,
		strlen(OutputBuffer) + 1,
		&BytesWritten,
		0);
#else
	for (int i = 0; i < NUMBER_OF_MESSAGES_TO_SEND; i++){
		char* OutputBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
		sprintf(OutputBuffer, "Hello from Client. Message - %d\n", i);
		DWORD BytesWritten;
		BOOL WriteFileResult = WriteFile(
			ClientHandle,
			OutputBuffer,
			strlen(OutputBuffer) + 1,
			&BytesWritten,
			0);
	}
#endif


	CloseHandle(ClientHandle);

	system("pause");
	return(0);
}