#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LobbyServer.h"
#include "Accept.h"
//CoreServerSample -> Thread -> IOCP로 작업.


void main()
{
	//AServer 연결 , Init함수 호출
	ALobbyServer server;
	server.Init(9110);
	Accept accept(&server);
	accept.Detach();
	server.RunServer();
	server.Release();


}