#ifndef EXTERN_FUNCTIONS_H

#include "common_code.h"

#define EXPORT extern "C" __declspec(dllexport)

//#define THREAD_FUNC_PROT(name) DWORD WINAPI name(LPVOID Param)
//typedef THREAD_FUNC_PROT(echo_server_prototype);
//typedef THREAD_FUNC_PROT(service_server_prototype);
//typedef THREAD_FUNC_PROT(time_server_prototype);
//THREAD_FUNC_PROT(ThreadFuncStub){
//	return 0;
//}
//static echo_server_prototype* EchoServer_ = ThreadFuncStub;
//static service_server_prototype* ServiceServer_ = ThreadFuncStub;
//static time_server_prototype* TimeServer_ = ThreadFuncStub;
//#define EchoServer EchoServer_
//#define ServiceServer ServiceServer_
//#define TimeServer TimeServer_

#define SSS_PROT(name) HANDLE name(char* Id, LPVOID Param)
typedef SSS_PROT(sss_prototype);
SSS_PROT(SSS_Stub){
	return INVALID_HANDLE_VALUE;
}
static sss_prototype* SSS_ = SSS_Stub;
#define OurSSS SSS_


#define EXTERN_FUNCTIONS_H
#endif