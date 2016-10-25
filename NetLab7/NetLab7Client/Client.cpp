#include <Windows.h>
#include <stdio.h>
#include "../CommonCode/common.h"
#include <iostream>
#include <time.h>

using namespace std;



int main(int argc, char** argv){

#if 1
	 char CompName[256];
	 cout << "Enter computer host name: ";
	 cin >> CompName;

	 char* MailSlotName = (char*)calloc(256, sizeof(char));

	 sprintf(MailSlotName, "\\\\%s\\mailslot\\MS_NAME", CompName);

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
	DWORD BeginClock = clock();

	for (int i = 0; i < NUMBER_OF_MESSAGES_TO_SEND; i++){
		char* OutputBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
		for (int i = 0; i < MESSAGE_SIZE - 1; i++){
			OutputBuffer[i] = 'a';
		}
		OutputBuffer[MESSAGE_SIZE] = 0;

		DWORD BytesWritten;
		BOOL WriteFileResult = WriteFile(
			ClientHandle,
			OutputBuffer,
			strlen(OutputBuffer) + 1,
			&BytesWritten,
			0);
	}

	DWORD EndClock = clock();
	DWORD CyclesElapsed = EndClock - BeginClock;
	real32 SecondsElapsed = (real32)CyclesElapsed / CLOCKS_PER_SEC;
	printf("%d messages sent in %0.4f seconds.\n", NUMBER_OF_MESSAGES_TO_SEND, SecondsElapsed);

#endif


	CloseHandle(ClientHandle);

	system("pause");
	return(0);
}