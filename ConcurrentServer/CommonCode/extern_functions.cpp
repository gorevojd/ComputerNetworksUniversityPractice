#include "extern_functions.h"
#include "../ConcurrentServer/server.cpp"

BEGIN_TABLESERVICE
ENTRY_SERVICE("EchoServer", EchoServer),
END_TABLESERVICE

EXPORT SSS_PROT(SSS){
	HANDLE Res = INVALID_HANDLE_VALUE;
	int i = 0;

	while (i < TableArrayCount && strcmp(TABLESERVICE_ID(i), Id) != 0){
		i++;
	}
	//Needed function found
	if (i < TableArrayCount){
		Res = CreateThread(0, 0, TABLESERVICE_FN(i), Param, 0, 0);
	}
	if (i == TableArrayCount){
		printf("ERROR: Not found requested function....");
		closesocket(((contact*)Param)->Sock);
	}
	
	return(Res);
}


BOOL APIENTRY DllMain(HANDLE hinst, DWORD  rcall, LPVOID wres)
{
	return TRUE;
}
