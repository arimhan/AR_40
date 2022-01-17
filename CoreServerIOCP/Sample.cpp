#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "LobbyServer.h"
#include "Accepter.h"
//CoreServerSample -> Thread -> IOCP로 작업.


void main()
{
	//Loobbyserver 연결 , 차례대로 accept-detach(스레드핸들분리)-run(서버실행)-release(종료전 지우기)
	ALobbyServer server;
	server.Init(9110);
	AAccepter accept(&server);
	accept.Detach();
	server.RunServer();
	server.Release();
}