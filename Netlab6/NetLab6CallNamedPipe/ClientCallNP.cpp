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

#if !DO_LAB_IN_LOOP
	char OutputBuffer[] = "Hello from Client!";
	char* InputBuffer = (char*)calloc(256, sizeof(char));
	DWORD BytesRead;
	CallNamedPipeA(NamedPipeName, OutputBuffer, strlen(OutputBuffer) + 1, InputBuffer, MESSAGE_SIZE, &BytesRead, NMPWAIT_WAIT_FOREVER);
	printf("%s\n", InputBuffer);
	free(InputBuffer);
#else
	for(int i = 0; i < 100; i++){
		char* DestWriteBuffer = (char*)calloc(MESSAGE_SIZE, sizeof(char));
		sprintf(DestWriteBuffer, "Hello from Client. Message - %d.\n", i);

		char* InputBuffer = (char*)calloc(256, sizeof(char));
		DWORD BytesRead;
#if 1
		CallNamedPipeA(NamedPipeName, DestWriteBuffer, strlen(DestWriteBuffer) + 1, InputBuffer, MESSAGE_SIZE, &BytesRead, NMPWAIT_WAIT_FOREVER);
#else
		CallNamedPipeA(NamedPipeName, InputBuffer, MESSAGE_SIZE, DestWriteBuffer, strlen(DestWriteBuffer) + 1, &BytesRead, NMPWAIT_WAIT_FOREVER);
#endif
		printf("%s\n", InputBuffer);
		free(InputBuffer);
		free(DestWriteBuffer);
	}
#endif

	system("pause");
	return 0;
}