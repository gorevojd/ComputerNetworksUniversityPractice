#ifndef COMMON_CODE_H

#define DO_LAB_IN_LOOP 1
#define THROUGH_READ_AND_WRITE 1

#include <Windows.h>
#include <stdio.h>

inline void CheckNPError(){
	switch (GetLastError())
	{
		case ERROR_IO_PENDING:{
			OutputDebugStringA("ERROR_IO_PENDING.\n");
		}break;
		case ERROR_PIPE_CONNECTED:{
			OutputDebugStringA("ERROR_PIPE_CONNECTED.\n");
		}break;
		default:
		{
			char* Buffer = (char*)calloc(256, sizeof(char));
			sprintf(Buffer, "ConnectNamedPipe failed with %d.\n", GetLastError());
			OutputDebugStringA(Buffer);
			printf("%s\n", Buffer);
		}
	}
}

struct debug_read_file_result{
	int Size;
	void* Memory;
};

inline debug_read_file_result DEBUGReadFile(char* FileName){
	
	debug_read_file_result Result;

	HANDLE FileHandle = CreateFileA(FileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
	if (FileHandle != INVALID_HANDLE_VALUE){
		LARGE_INTEGER FileSize;
		GetFileSizeEx(FileHandle, &FileSize);
		Result.Size = FileSize.QuadPart;
		Result.Memory = VirtualAlloc(0, FileSize.QuadPart, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (FileSize.QuadPart != 0){
			DWORD BytesRead;
			ReadFile(FileHandle, Result.Memory, FileSize.QuadPart, &BytesRead, 0);
			CloseHandle(FileHandle);
		}
	}
	else{

	}

	return(Result);
}

inline void DEBUGWriteFile(char* FileName, void* Memory, int Size){
	HANDLE FileHandle = CreateFileA(
		FileName,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		0,
		CREATE_ALWAYS,
		0, 0);
	if (FileHandle != INVALID_HANDLE_VALUE){
		DWORD BytesWritten;
		WriteFile(FileHandle, Memory, Size, &BytesWritten, 0);
		CloseHandle(FileHandle);
	}
	else{

	}
}

inline void DEBUGFreeMemory(void* Memory){
	if (!Memory){
		VirtualFree(Memory, 0, MEM_RELEASE);
	}
}

#define COMMON_CODE_H
#endif