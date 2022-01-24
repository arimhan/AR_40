#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
using namespace std;

void main()
{
	//Broadcast사용 가능한 socket추가. -> socketopt
	char flag = true;
	
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag)) < 0)
	{
		//socket error check !
		closesocket(sock);
	}

	//address.sin_addr.s_addr = INADDR_BROADCAST; 로 고정되어 있음.
	//INADDR_BROADCAST -> 해당 주소에 있는 user에게 data가 모두 전송됨. (대상 지정X)
	//여기서 sock은 Broadcast용 sock임. 이 sock을 사용한 해당하는 port번호로 접속한 user들이 대상.
	//그렇기 때문에 userlist로 돌 필요가 없다. -> 여기서 특정한 user에게 data전송하는 기능이 필요하다.

	//즉 sender프로그램 2개 실행 불가..ㅜ

}


