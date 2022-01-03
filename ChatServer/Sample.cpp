#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winSock2.h>
#include <list>
#pragma comment (lib, "ws2_32.lib")
using namespace std;

#define PORT_NUM 9110 
#define ADRESS_NUM "127.0.0.1" 
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
void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET ListenSock = socket(AF_INET, SOCK_STREAM, 0);
	//Server ����
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(PORT_NUM); // ���� ��Ʈ ��ȣ, �� ��Ʈ��ȣ�� �����ϴ� �ֵ� �� ���� �����ϵ��� ����
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //��� IP ���� ���
	int iRet = bind(ListenSock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return;
	iRet = listen(ListenSock, SOMAXCONN);
	if (iRet == SOCKET_ERROR) return;

	SOCKADDR_IN ClientAddr;
	int iLen = sizeof(ClientAddr);
	cout << "���� ������ ... " << endl;

	//---------------------����ŷ ����
	u_long on = 1;
	ioctlsocket(ListenSock, FIONBIO, &on);

	list<AUser> UserList;

	while (1)
	{
		//SOCKET�� ������ ����
		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &iLen);

		if (ClientSock == SOCKET_ERROR) //Client�� ��ȿ�� ������ �ƴ� ���
		{
			int iError = WSAGetLastError();
			if (iError != WSAEWOULDBLOCK) //������ �ƴ� ��� ó��
			{
				cout << "ErrorCode: " << iError << endl;
				break;
			}
		}
		else //���� �۵� -> usercount, ip , port ���� ���
		{
			AUser user;
			user.Set(ClientSock, ClientAddr);
			UserList.push_back(user);

			cout << "IP: " << inet_ntoa(ClientAddr.sin_addr) << ", Port: " << ntohs(ClientAddr.sin_port) << " " << endl; //ip, port ���
			u_long on = 1;
			ioctlsocket(ClientSock, FIONBIO, &on);
			cout << UserList.size() << " �� ������.." << endl;
		}
		if (UserList.size() > 0) //User ���� �� ó��
		{
			list<AUser>::iterator iter;
			for (iter = UserList.begin(); iter != UserList.end();) //iter ++ ��ġ Ȯ��
			{
				AUser user = *iter;
				char szRecvBuffer[256] = { 0, };
				int iRecvByte = recv(user.m_Sock, szRecvBuffer, 256, 0);
				if (iRecvByte == 0)
				{
					closesocket(user.m_Sock);
					iter = UserList.erase(iter); // user �α׾ƿ� �� ���� ��. 
					cout << user.m_csName<<" ��������"<<endl;
					continue;
				}
				if (iRecvByte == SOCKET_ERROR)
				{
					int iError = WSAGetLastError();
					if (iError != WSAEWOULDBLOCK) //Soket ������ nonblock���°� �ƴ� ��� == ��¥ ������ ���
					{
						//cout << "ErrorCode2: " << iError << endl;
						iter = UserList.erase(iter);
						cout << user.m_csName << " ������ ��������" << endl;
					}
					else
					{
						iter++;
					}
				}
				else //Client ���� string�� 1���� �ԷµǸ�, �� �� for���� ��� ���鼭 ������� �Ǵ� ���� �߻�
				{
					list<AUser>::iterator iterSend;
					for (iterSend = UserList.begin(); iterSend != UserList.end();)
					{
						AUser user = *iterSend;
						cout << "=>  " << szRecvBuffer << endl;
						int iSendByte = send(user.m_Sock, szRecvBuffer, iRecvByte, 0);
						cout << "User:" << user.m_Sock << ", " << iSendByte << "[byte]  <=" << endl;

						if (iSendByte == SOCKET_ERROR)
						{
							int iError = WSAGetLastError();
							if (iError != WSAEWOULDBLOCK) //Soket ������ nonblock���°� �ƴ� ��� == ��¥ ������ ���
							{
								//cout << "ErrorCode2: " << iError << endl;
								closesocket(user.m_Sock);
								iterSend = UserList.erase(iterSend);
								cout << user.m_csName << " ������ ��������" << endl;
							}
						}
						else
						{
							iterSend++;
						}
					}
					if (iter != UserList.end())
					{
						iter++;
					}
				}
			}
		}
	}
	closesocket(ListenSock);
	WSACleanup();
}