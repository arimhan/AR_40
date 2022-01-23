#pragma once
#include "NetUser.h"
#include "Accepter.h"
//#define PORT_NUM 9110 // ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!9110
#define ADRESS_NUM "127.0.0.1" // ��ǻ�� IP �ּ� , ���� 48, 192.168.219.101 "127.0.0.1"

struct XPacket
{
	ANetUser*		pUser;
	APacket			packet;
};
class AServer : public AServerObj
{
	AAccepter		m_Accept;
public:
	list<ANetUser*>	m_UserList;
	list<XPacket>	m_packetPool;
	typedef list<ANetUser*>::iterator m_UserIter;
public:
	using CallFunction = function<void(APacket& a, ANetUser* user)>;
	typedef map<int, CallFunction>::iterator FunctionIterator;
	map<int, CallFunction> m_fnExecutePacket;
public:
	virtual void LoginReq(APacket& a, ANetUser* user);
public:
	int SendMsg(SOCKET Csock, UPACKET& packet);
	int SendMsg(ANetUser *pUser, char* msg, int iSize, WORD type);
	int SendMsg(ANetUser* pUser, UPACKET& packet);
	int Broadcast(APacket& a);
	//int Broadcast(ANetUser* user);
	int BroadcastPool(ANetUser* user);
	virtual bool AddUser(SOCKET Csock, SOCKADDR_IN CAddr);
public:
	virtual bool DelUser(SOCKET sock);
	virtual bool DelUser(ANetUser* pUser);
	virtual bool DelUser(m_UserIter& iter);
public:
	virtual bool Init(int iPort);
	virtual bool RunServer();
	virtual bool Release();

};


