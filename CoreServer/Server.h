#pragma once
#include "NetUser.h"

//#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!9110
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101 "127.0.0.1"

struct XPacket
{
	ANetUser* pUser;
	APacket   packet;
};
class AServer : public AServerObj
{
public:
	list<ANetUser*>		m_UserList;
	SOCKET				m_LSock;
	list<XPacket>		m_packetPool;
	list<ANetUser*>::iterator m_UserIter;

public:
	int SendMsg(SOCKET Csock, UPACKET& packet);
	int SendMsg(ANetUser *pUser, char* msg, int iSize, WORD type);
	int SendMsg(ANetUser* pUser, UPACKET& packet);
	int Broadcast(ANetUser* user);

public:
	virtual bool Init(int iPort);
	virtual bool RunServer();
	virtual bool Release();
public:
	virtual bool AddUser(SOCKET Csock, SOCKADDR_IN CAddr);

};


