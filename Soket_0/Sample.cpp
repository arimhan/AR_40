#include <iostream>
#include <winSock2.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
#define PORT_NUM 10000 //10000 선생님 포트번호
#define ADRESS_NUM "192.168.0.12" //선생님 컴퓨터 IP 주소


//<소켓 생성>
// 연결형, TCP프로토콜(SOCK_STREAM,IPPROTO_TCP)
// 비연결형, UDP 프로토콜(SOCK_DGRAM,IPPROTO_UDP)

void main()
{
	unsigned short iPort = PORT_NUM;
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET sock = socket (AF_INET,AF_INET,0);
	//프로토콜 지정 그런데 중간 TYPE값 명시되면 0으로 설정해도 OK
	//SOCK_STREAM : TCP
	//SOCK_DGRAM : UDP

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port= htons(9000); // 서버 포트 번호
	sa.sin_addr.s_addr=inet_addr(ADRESS_NUM);
	//IP 매크로로 지정한 곳에 넣음. 원래는 S_un.S_addr에 넣음.
	//inet_addr문자열을 4byte로 바꿔서 저장

	//연결한다~
	int iRet = connect(sock, (sockaddr*)&sa, sizeof(sa));

	//보내는~ 받는 버퍼 생성
	char szBuffer[256] = "안녕"; // [] 비워두면 해당한 사이즈대로 전송됨.
	char szRecvBuffer[256] = { 0, };

	// data 전송
	int iSendByte = send(sock, szBuffer, sizeof(szBuffer), 0);

	//서버는 에코시스템이 있음 (리시브 가능)
	int iRetByte = recv(sock, szRecvBuffer, 256, 0);
	cout << szRecvBuffer << endl;

	//닫기~
	WSACleanup();
}