#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"
#include "ThreadRecv.h"
#include "ThreadSend.h"
//CoreServerSample -> Thread -> IOCP�� �۾�.


void main()
{
	//AServer ���� , Init�Լ� ȣ��
	AServer server;
	server.Init(9110);

	AThreadRecv tRecv(&server);
	AThreadSend tSend(&server);
	tRecv.Detach();
	tSend.Detach();

	server.RunServer();
	server.Release();

}