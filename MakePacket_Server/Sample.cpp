#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <conio.h> //_kbhit();
#include <list>
#include "Packet.h"
#pragma comment (lib, "ws2_32.lib")
//using namespace std;
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
};
int SendMsg(SOCKET sock, char* msg, WORD type)
{
	// 1. 패킷 생성
	//규칙을 정해서 동일하게 처리해야함.
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg)); //txt 메모리 카피 처리
	char* pMsg = (char*)&packet;
	//packet은 구조체 -> 문자열로 캐스팅하여 전송한다.
	int iSendSize = 0;
	//int iTotalSize = packet.ph.len - iSendSize; //strlen(msg) + PACKET_HEADER_SIZE;
	do {
		// 2. 패킷 전송 : 운영체제는 sendbuffer(short byte), recvbuffer 내 크기가 정해져 있음.
		int iSendByte = send(sock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if(WSAGetLastError() != WSAEWOULDBLOCK)
			{
				//cout << "Error_sock "<< WSAGetLastError << endl;
				return -1;
			}
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int SendMsg(SOCKET sock, UPACKET&packet)
{
	// 생성된 packet 전송
		//packet은 구조체 -> 문자열로 캐스팅하여 전송한다.
	char* pMsg = (char*)&packet;
	int iSendSize = 0;

	do { 
		int iSendByte = send(sock, &pMsg[iSendSize], packet.ph.len - iSendSize, 0);
		if (iSendByte ==SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) return -1;
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { return; }
	//Server 소켓, 주소 세팅
	SOCKET Lsock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN LAddr;
	ZeroMemory(&LAddr, sizeof(LAddr));
	LAddr.sin_family = AF_INET;
	LAddr.sin_port = htons(9110); 
	LAddr.sin_addr.s_addr = htonl(INADDR_ANY); //모든 IP 접속 허용
	int iRet = bind(Lsock, (sockaddr*)&LAddr, sizeof(LAddr));
	if (iRet == SOCKET_ERROR) return;
	iRet = listen(Lsock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return;

	//Client 주소 세팅
	SOCKADDR_IN CAddr;
	int iLen = sizeof(CAddr);
	cout << "서버 가동중 ... " << endl;

	//논블로킹 적용
	u_long on = 1;
	ioctlsocket(Lsock, FIONBIO, &on);

	list<AUser> UserList;

	while (1)
	{
		SOCKET Csock = accept(Lsock, (sockaddr*)&CAddr, &iLen);

		if (Csock == SOCKET_ERROR) //Client가 유효한 소켓이 아닐 경우
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK) //에러가 아닐 경우 처리
			{
				cout << "ErrorCode: " <<iError << endl;
				break;
			}
		}
		else //정상 작동 -> usercount, ip , port 정보 출력
		{
			AUser user;
			user.Set(Csock, CAddr);
			UserList.push_back(user);

			cout << "IP: " << inet_ntoa(CAddr.sin_addr) << ",  Port: " << ntohs(CAddr.sin_port) << " " << endl; //ip, port 출력

			//논블로킹 성질은 상속되기 때문에 표기 안 해도 상관없으나, 명시적으로 표기하는것이 좋다.
			u_long on = 1;
			ioctlsocket(Csock, FIONBIO, &on);
			cout << UserList.size() << "명 접속중.." << endl;
		}
		if (UserList.size() > 0) //User 접속 시 처리
		{
			list<AUser>::iterator iter;
			for (iter = UserList.begin(); iter != UserList.end();) //iter ++ 위치 확인
			{
				AUser user = *iter;
				char szRecvBuffer[256] = { 0, };

				//패킷 헤더 받기
				UPACKET recvPacket;
				ZeroMemory(&recvPacket, sizeof(recvPacket));
				int iRecvSize = 0;
				do {
					int iRecvByte = recv(user.m_Sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
					iRecvSize += iRecvByte;
					if (iRecvByte == 0) 
					{ //받은 Byte가 하나도 없을 경우 접속종료했기 때문에 종료 처리 후 UserList에서 지우기.
						closesocket(user.m_Sock);
						iter = UserList.erase(iter); // user 로그아웃 시 지울 것. 
						cout << user.m_csName << " 접속종료" << endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK) //Soket 에러가 nonblock상태가 아닐 경우 == 진짜 오류일 경우
						{
							//cout << "ErrorCode2: " << iError << endl;
							iter = UserList.erase(iter); //유저가 도중에 튕기면 정상종료가 아니라서 오류발생 -> 접속종료라고 뜸.
							cout << user.m_csName << " 비정상 접속종료" << endl;
							break;
						}
						else { break; }
					}
				} while (iRecvSize < PACKET_HEADER_SIZE); //패킷 헤더를 받을 동안 do while문으로 반복한다.
				if (iRecvSize == SOCKET_ERROR)
				{
					if (iter != UserList.end())
					{
						//UserList의 맨 마지막이면 continue
						iter++;
					}
					continue;
				}

				memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);
				// 데이터 받기
				iRecvSize = 0;
				do {
					int iRecvByte = recv(user.m_Sock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
					iRecvSize += iRecvByte;

					if (iRecvByte == 0)
					{
						closesocket(user.m_Sock);
						iter = UserList.erase(iter); // user 로그아웃 시 지울 것. 
						cout << user.m_csName << " 접속종료" << endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK) 
						{
							iter = UserList.erase(iter);
							cout << user.m_csName << " 비정상 접속종료" << endl;
						}
						else { iter++; }
					}
				} while (iRecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);
				// 보내는 패킷 길이 - 패킷 헤더가 존재하는 동안 do while문으로 반복 처리 (실제 메시지 길이)

				APacket data;
				data.m_uPacket = recvPacket;
				AChatMsg recvdata;
				ZeroMemory(&recvdata, sizeof(recvdata));
				//전달받은 패킷정보를 출력하는 항목. [이름] 데이터 순으로 출력된다.
				data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
				//cout << recvdata.index << " ," << recvdata.name << "  ," << recvdata.damage << "  ," << recvdata.message << endl;;
				cout << "\n" << "[ " << recvdata.name << " ]" << recvdata.message;

				// 패킷 완성
				list<AUser>::iterator iterSend;
				for (iterSend = UserList.begin(); iterSend != UserList.end();)
				{
					AUser user = *iterSend;
					int iSendMsgSize = SendMsg(user.m_Sock, recvPacket);
					if (iSendMsgSize < 0)
					{
						closesocket(user.m_Sock);
						iterSend = UserList.erase(iterSend);
						cout << user.m_csName << " 비정상 접속종료" << endl;
					}
					else { iterSend++; }
				}
				if (iter != UserList.end()) { iter++; }
			}
		}
	}
	closesocket(Lsock);
	WSACleanup();
}