#include "../CommonCode/common_code.h"
#include <iostream>
#include <list>

using namespace std;


int main(int argc, char** argv){

	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 0), &WsaData);



	WSACleanup();

	system("pause");
	return 0;
}