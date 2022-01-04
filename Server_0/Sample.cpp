#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

////에러메시지 처리
//void Err_Quit()
//{
//
//}
////에러메시지 출력
//void Err_Display()
//{
//
//}

void main()
{
	//윈속 초기화
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2,2), &wsd != 0))
	{
		return;
	}
	////WSADATA wsa;
	//if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	//{
	//	return;
	//}

	//소켓 생성

	//bind

	//listen

	//client 변수 선언

	//accept 처리 ->
		//클라이언트와 데이터 통신 -> Recv ,없을 경우 , 출력

	//윈속 종료

	//WSACleanup();
	return;
}


