#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LobbyServer.h"
#include "Accept.h"
//CoreServerSample -> Thread -> IOCP�� �۾�.


void main()
{
	//AServer ���� , Init�Լ� ȣ��
	ALobbyServer server;
	server.Init(9110);
	Accept accept(&server);
	accept.Detach();
	server.RunServer();
	server.Release();


}