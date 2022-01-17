#pragma once
#include "NetUser.h"

//#define PORT_NUM 9110 // ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!9110
#define ADRESS_NUM "127.0.0.1" // ��ǻ�� IP �ּ� , ���� 48, 192.168.219.101 "127.0.0.1"


class AServer : public AServerObj
{
public:
	list<ANetUser*>		m_UserList;
	SOCKET				m_LSock;

public:
	int SendMsg(SOCKET Csock, char* msg, WORD type);
	int SendMsg(SOCKET Csock, UPACKET& packet);
	int Broadcast(ANetUser* user);

public:
	virtual bool Init(int iPort);
	virtual bool RunServer();
	virtual bool Release();
public:
	virtual bool AddUser(SOCKET sock, SOCKADDR_IN CAddr);

};


