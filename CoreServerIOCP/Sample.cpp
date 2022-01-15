#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"
#include "ThreadRecv.h"
#include "ThreadSend.h"
//CoreServerSample -> Thread -> IOCP로 작업.


void main()
{
	//AServer 연결 , Init함수 호출
	AServer server;
	server.Init(9110);

	AThreadRecv tRecv(&server);
	AThreadSend tSend(&server);
	tRecv.Detach();
	tSend.Detach();

	server.RunServer();
	server.Release();

}