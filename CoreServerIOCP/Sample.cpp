#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LobbyServer.h"
#include "Accepter.h"
//CoreServerSample -> Thread -> IOCP�� �۾�.


void main()
{
	//Loobbyserver ���� , ���ʴ�� accept-detach(�������ڵ�и�)-run(��������)-release(������ �����)
	ALobbyServer server;
	server.Init(9110);
	AAccepter accept(&server);
	accept.Detach();
	server.RunServer();
	server.Release();
}