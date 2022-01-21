#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LobbyServer.h"
#include "Accepter.h"
#include "ObjectPool.h"

void main()
{
	//Loobbyserver 연결 , 차례대로 accept-detach(스레드핸들분리)-run(서버실행)-release(종료전 지우기)
	ALobbyServer server;
	server.Init(9110);
	server.RunServer();
	server.Release();
}  