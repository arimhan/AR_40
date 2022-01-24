#pragma once
#include "NetUser.h"
#include "Accepter.h"
//#define PORT_NUM 9110 // 포트번호, 내 포트번호는 내가 정할 수 있다. 1024~ 부터!9110
#define ADRESS_NUM "127.0.0.1" // 컴퓨터 IP 주소 , 나는 48, 192.168.219.101 "127.0.0.1"

class AServer : public AServerObj
{
	AAccepter		m_Accept;
public:
	list<ANetUser*>	m_UserList;
	list<APacket>	m_packetPool;
	typedef list<ANetUser*>::iterator m_UserIter;

public:
	int SendMsg(SOCKET Csock, UPACKET& packet);
	int SendMsg(SOCKET Csock, char* msg, WORD type);
	int Broadcast(ANetUser* user);
	//int Broadcast(APacket& a);
	//int BroadcastPool(ANetUser* user);
	virtual bool AddUser(SOCKET Csock, SOCKADDR_IN CAddr);
public:
	virtual bool Init(int iPort);
	virtual bool RunServer();
	virtual bool Release();

};


