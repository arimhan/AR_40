#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LobbyServer.h"
#include "Accepter.h"
#include "ObjectPool.h"

void main()
{
	//Loobbyserver ���� , ���ʴ�� accept-detach(�������ڵ�и�)-run(��������)-release(������ �����)
	ALobbyServer server;
	server.Init(9110);
	server.RunServer();
	server.Release();
}  