#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winSock2.h>
#include <conio.h> //_kbhit();
#include <list>
#include "Packet.h"
#pragma comment (lib, "ws2_32.lib")
//using namespace std;
// chat server : client���� ���� ���� -> n�� ī��Ʈ , client string ���� �� ���ó��

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
	// 1. ��Ŷ ����
	//��Ģ�� ���ؼ� �����ϰ� ó���ؾ���.
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg)); //txt �޸� ī�� ó��
	char* pMsg = (char*)&packet;
	//packet�� ����ü -> ���ڿ��� ĳ�����Ͽ� �����Ѵ�.
	int iSendSize = 0;
	//int iTotalSize = packet.ph.len - iSendSize; //strlen(msg) + PACKET_HEADER_SIZE;
	do {
		// 2. ��Ŷ ���� : �ü���� sendbuffer(short byte), recvbuffer �� ũ�Ⱑ ������ ����.
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
	// ������ packet ����
		//packet�� ����ü -> ���ڿ��� ĳ�����Ͽ� �����Ѵ�.
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
	//Server ����, �ּ� ����
	SOCKET Lsock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN LAddr;
	ZeroMemory(&LAddr, sizeof(LAddr));
	LAddr.sin_family = AF_INET;
	LAddr.sin_port = htons(9110); 
	LAddr.sin_addr.s_addr = htonl(INADDR_ANY); //��� IP ���� ���
	int iRet = bind(Lsock, (sockaddr*)&LAddr, sizeof(LAddr));
	if (iRet == SOCKET_ERROR) return;
	iRet = listen(Lsock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return;

	//Client �ּ� ����
	SOCKADDR_IN CAddr;
	int iLen = sizeof(CAddr);
	cout << "���� ������ ... " << endl;

	//����ŷ ����
	u_long on = 1;
	ioctlsocket(Lsock, FIONBIO, &on);

	list<AUser> UserList;

	while (1)
	{
		SOCKET Csock = accept(Lsock, (sockaddr*)&CAddr, &iLen);

		if (Csock == SOCKET_ERROR) //Client�� ��ȿ�� ������ �ƴ� ���
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK) //������ �ƴ� ��� ó��
			{
				cout << "ErrorCode: " <<iError << endl;
				break;
			}
		}
		else //���� �۵� -> usercount, ip , port ���� ���
		{
			AUser user;
			user.Set(Csock, CAddr);
			UserList.push_back(user);

			cout << "IP: " << inet_ntoa(CAddr.sin_addr) << ",  Port: " << ntohs(CAddr.sin_port) << " " << endl; //ip, port ���

			//����ŷ ������ ��ӵǱ� ������ ǥ�� �� �ص� ���������, ��������� ǥ���ϴ°��� ����.
			u_long on = 1;
			ioctlsocket(Csock, FIONBIO, &on);
			cout << UserList.size() << "�� ������.." << endl;
		}
		if (UserList.size() > 0) //User ���� �� ó��
		{
			list<AUser>::iterator iter;
			for (iter = UserList.begin(); iter != UserList.end();) //iter ++ ��ġ Ȯ��
			{
				AUser user = *iter;
				char szRecvBuffer[256] = { 0, };

				//��Ŷ ��� �ޱ�
				UPACKET recvPacket;
				ZeroMemory(&recvPacket, sizeof(recvPacket));
				int iRecvSize = 0;
				do {
					int iRecvByte = recv(user.m_Sock, szRecvBuffer, PACKET_HEADER_SIZE, 0);
					iRecvSize += iRecvByte;
					if (iRecvByte == 0) 
					{ //���� Byte�� �ϳ��� ���� ��� ���������߱� ������ ���� ó�� �� UserList���� �����.
						closesocket(user.m_Sock);
						iter = UserList.erase(iter); // user �α׾ƿ� �� ���� ��. 
						cout << user.m_csName << " ��������" << endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK) //Soket ������ nonblock���°� �ƴ� ��� == ��¥ ������ ���
						{
							//cout << "ErrorCode2: " << iError << endl;
							iter = UserList.erase(iter); //������ ���߿� ƨ��� �������ᰡ �ƴ϶� �����߻� -> ���������� ��.
							cout << user.m_csName << " ������ ��������" << endl;
							break;
						}
						else { break; }
					}
				} while (iRecvSize < PACKET_HEADER_SIZE); //��Ŷ ����� ���� ���� do while������ �ݺ��Ѵ�.
				if (iRecvSize == SOCKET_ERROR)
				{
					if (iter != UserList.end())
					{
						//UserList�� �� �������̸� continue
						iter++;
					}
					continue;
				}

				memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);
				// ������ �ޱ�
				iRecvSize = 0;
				do {
					int iRecvByte = recv(user.m_Sock, recvPacket.msg, recvPacket.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
					iRecvSize += iRecvByte;

					if (iRecvByte == 0)
					{
						closesocket(user.m_Sock);
						iter = UserList.erase(iter); // user �α׾ƿ� �� ���� ��. 
						cout << user.m_csName << " ��������" << endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK) 
						{
							iter = UserList.erase(iter);
							cout << user.m_csName << " ������ ��������" << endl;
						}
						else { iter++; }
					}
				} while (iRecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);
				// ������ ��Ŷ ���� - ��Ŷ ����� �����ϴ� ���� do while������ �ݺ� ó�� (���� �޽��� ����)

				APacket data;
				data.m_uPacket = recvPacket;
				AChatMsg recvdata;
				ZeroMemory(&recvdata, sizeof(recvdata));
				//���޹��� ��Ŷ������ ����ϴ� �׸�. [�̸�] ������ ������ ��µȴ�.
				data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
				//cout << recvdata.index << " ," << recvdata.name << "  ," << recvdata.damage << "  ," << recvdata.message << endl;;
				cout << "\n" << "[ " << recvdata.name << " ]" << recvdata.message;

				// ��Ŷ �ϼ�
				list<AUser>::iterator iterSend;
				for (iterSend = UserList.begin(); iterSend != UserList.end();)
				{
					AUser user = *iterSend;
					int iSendMsgSize = SendMsg(user.m_Sock, recvPacket);
					if (iSendMsgSize < 0)
					{
						closesocket(user.m_Sock);
						iterSend = UserList.erase(iterSend);
						cout << user.m_csName << " ������ ��������" << endl;
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