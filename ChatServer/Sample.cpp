#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winSock2.h>
#include <list>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

#define PORT_NUM 9110 
#define ADRESS_NUM "127.0.0.1" 
// chat server : client에서 서버 접속 -> n명 카운트 , client string 받은 뒤 출력처리

struct AUser
{
	SOCKET			m_Sock;
	SOCKADDR_IN		m_Addr;
	string			m_csName;
	short			m_iPort;

	void Set(SOCKET sock, SOCKADDR_IN addr)
	{
		m_Sock = sock;
		m_Addr = addr;
		m_csName = inet_ntoa(addr.sin_addr);
		m_iPort = ntohs(addr.sin_port);
	}
}


void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	//Server 소켓
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(9110); // 서버 포트 번호, 내 포트번호에 접속하는 애들 다 접속 가능하도록 설정
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //모든 IP 접속 허용
	int iRet = bind(ListenSock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return;
	iRet = listen(ListenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return;

	SOCKADDR_IN ClientAddr;
	int iLen = sizeof(ClientAddr);
	cout << "서버 가동중 ... " << endl;

	//---------------------논블로킹 적용
	u_long on = 1;
	ioctlsocket(ListenSock, FIONBIO, &on);
	list<AUser> UserList;

	while (1)
	{
		//SOCKET이 존재할 동안

		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &iLen);

		if (ClientSock == SOCKET_ERROR) //Client가 유효한 소켓이 아닐 경우
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK) //에러가 아닐 경우 처리
			{
				cout << "ErrorCode: " << iError << endl;
				break;
			}
		}
		else //정상 작동 -> usercount, ip , port 정보 출력
		{
			AUser user;
			user.Set();
			
			UserList.push_back(ClientSock);
			cout << "IP: " << inet_ntoa(ClientAddr.sin_addr) << ", Port: " << ntohs(ClientAddr.sin_port) << " " << endl; //ip, port 출력
			u_long on = 1;
			ioctlsocket(ClientSock, FIONBIO, &on);
			cout << UserList.size() << " 명 접속중.." << endl;
		}
		if (UserList.size() > 0) //User 접속 시 처리
		{
			list<SOCKET>::iterator iter;
			for (iter = UserList.begin(); iter != UserList.end();) //iter ++ 위치 확인
			{
				SOCKET iterSock = *iter;
				char szRecvBuffer[256] = { 0, };
				int iRecvByte = recv(iterSock, szRecvBuffer, 256, 0);
				if (iRecvByte == 0)
				{
					closesocket(iterSock);
					iter = UserList.erase(iter); // user 로그아웃 시 지울 것. 
					cout << "접속종료"<<endl;
					continue;
				}
				if (iRecvByte == SOCKET_ERROR)
				{
					int iError = WSAGetLastError();
					if (iError != WSAEWOULDBLOCK) //Soket 에러가 nonblock상태가 아닐 경우 == 진짜 오류일 경우
					{
						//cout << "ErrorCode2: " << iError << endl;
						iter = UserList.erase(iter);
					}
					else
					{
						iter++;
					}
				}
				else
				{
					list<SOCKET>::iterator iterSend;
					for (iterSend = UserList.begin(); iterSend != UserList.end(););
					{
						SOCKET iterSendSock = *iterSend;
						cout << "<= 받음 : " << szRecvBuffer << " " << endl;
						int iSendByte = send(iterSendSock, szRecvBuffer, iRecvByte, 0);
						cout << iterSendSock <<"  => :" << "보냄 : " << iSendByte << " [byte]" << endl;

						if (iSendByte == SOCKET_ERROR)
						{
							int iError = WSAGetLastError();
							if (iError != WSAEWOULDBLOCK) //Soket 에러가 nonblock상태가 아닐 경우 == 진짜 오류일 경우
							{
								//cout << "ErrorCode2: " << iError << endl;
								closesocket(iterSendSock);
								iter = UserList.erase(iterSend);
							}
							else
							{
								iterSend++;
							}
						}
						iter++;
					}
				}
			}
		}
	}
	closesocket(ListenSock);
	WSACleanup();
}