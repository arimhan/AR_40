#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "ServerObj.h"
#include "Packet.h"
#include "ObjectPool.h"

class AServer;
struct AOV	:	public AObjectPool<AOV>
{
	enum { MODE_RECV =1, MODE_SEND=2, MODE_EXIT };
	OVERLAPPED ov;
	int type;

	//malloc�� ����ϸ� ������ ȣ��X new�� ������ �ؼ� ������ ȣ�� �� �ʱ�ȭ �ǵ��� ó��
	AOV(int packetType)
	{
		ZeroMemory(&ov, sizeof(OVERLAPPED));
		type = packetType;
	}
	AOV()
	{
		ZeroMemory(&ov, sizeof(OVERLAPPED));
		type = MODE_RECV;
	}
};
class ANetUser : public AServerObj
{
	AServer* m_pServer = nullptr;
public:
	bool			m_bConnect = false;
	SOCKET			m_Sock;
	SOCKADDR_IN		m_Addr;
	string			m_csName;
	short			m_iPort;
public:
	//buffer ����
	AOV			m_ovRecv;
	AOV			m_ovSend;
	WSABUF		m_wsaRecvBuffer;
	WSABUF		m_wsaSendBuffer;
	char		m_szRecv[256];
	char		m_szSend[256];
	//-------------------------------------------
	char		m_szRecvBuffer[2048];
	int			m_iPacketPos; //��Ŷ ���� �ּ�
	int			m_iWritePos;  //���� ���� ��ġ(Ŀ��)
	int			m_iReadPos;   //���� ���� ��ġ

	list<APacket>	m_PacketPool;
public:
	int				Recv();
	int				Dispatch(DWORD dwTrans, AOV* aov);
	int				DispatchRecv(char* szRecvBuffer, int iRecvByte);
	int				DispatchSend(DWORD dwTrans);
	void			Set(SOCKET Sock, SOCKADDR_IN Addr, AServer* pServer);
	bool			DisConnect();
public:
	ANetUser();
	virtual ~ANetUser();
};
