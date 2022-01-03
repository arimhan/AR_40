#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <WS2tcpip.h>
#include <conio.h> //_kbhit();
#pragma comment (lib, "ws2_32.lib")
using namespace std;

#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101

// Soket_Client
// chat client : string입력 후 엔터 입력 시 string을 서버로 전송

void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET ClientSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT_NUM); // 서버 포트 번호
	sa.sin_addr.s_addr = inet_addr(ADRESS_NUM);
	int iRet = connect(ClientSock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR)
	{
		return;
	}
	cout << "서버 접속 성공!" << endl;

	u_long on = 1; 
	//	u_long nonblockingoff = 0; //0, 1로 사용 가능.
	ioctlsocket(ClientSock, FIONBIO, &on);
	//------------------서버 정상 연결까지 확인 후 string 입력 처리 진행
	char szBuffer[256] = { 0, };	//string 저장 버퍼
	int iECount = 0;				// 버퍼에 저장 전 끝 입력값(커서)를 나타냄.
	while (1)
	{
		if (_kbhit() == 1)
			//_kbhit : 0이 아닌 값을 반환하면 키 입력이 버퍼에서 대기중인 상태, 키 입력 시 처리
		{
			int iValue = _getche(); // 읽은 문자 반환
			if (iValue == '\r' && strlen(szBuffer) == 0) //
			{
				break;
				//continue;
			}
			if (iValue == '\r') // 엔터 입력 시 string 발송
			{
				int iSendByte = send(ClientSock, szBuffer, iECount, 0);

				if (iSendByte == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK) //Soket 에러가 nonblock상태가 아닐 경우 == 진짜 오류일 경우
					{
						cout << "비정상 서버 종료" << endl;
						break;
					}
					//서버 종료 되면서 입력받은 string buffer 초기화 처리
				}
				iECount = 0;
				ZeroMemory(szBuffer, sizeof(char) * 256);
			}
			else // 엔터 안 누르면 string 입력 포인터 끝 부분 증가~~
			{
				szBuffer[iECount++] = iValue;
			}
		}
		else // 키 입력 안 했을 경우 받은 메시지 처리
		{
			char szRecvBuffer[256] = { 0, };
			int iRecvByte = recv(ClientSock, szRecvBuffer, 256, 0);

			if (iRecvByte == 0)
			{
				cout << "서버가 종료되었습니다." << endl; //서버 종료 시 처리
				break;
			}
			if (iRecvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK) //Soket 에러가 nonblock상태가 아닐 경우 == 진짜 오류일 경우
				{
					cout << "비정상 서버 종료" << endl;
					break;
				}
			}
			else //string 출력 처리
			{
				cout << " " <<szRecvBuffer<< endl;
				ZeroMemory(szRecvBuffer, sizeof(char) * 256);
			}
		}
	}
	cout << "line 98" << endl; //while반복문 종료 시 출력
	closesocket(ClientSock);
	WSACleanup();
	_getch();
}