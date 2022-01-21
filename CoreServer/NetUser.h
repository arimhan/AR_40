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

	//malloc만 사용하면 생성자 호출X new를 재정의 해서 생성자 호출 시 초기화 되도록 처리
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
class ANetUser : public AServerObj, public AObjectPool<ANetUser>
{
public:
	AServer*		m_pServer = nullptr;
	bool			m_bConnect = false;
	SOCKET			m_Sock;
	SOCKADDR_IN		m_Addr;
	string			m_csName;
	short			m_iPort;
public:
	//buffer 관련
	//TOV			m_ovRecv;
	//TOV			m_ovSend;
	WSABUF		m_wsaRecvBuffer;
	WSABUF		m_wsaSendBuffer;
	char		m_szRecv[256];
	char		m_szSend[256];
	//-------------------------------------------
	char		m_szRecvBuffer[2048];
	int			m_iPacketPos; //패킷 시작 주소
	int			m_iWritePos;  //현재 저장 위치(커서)
	int			m_iReadPos;   //현재 읽은 위치

	list<APacket>	m_PacketPool;
public:
	int				Recv();
	//int				Send();
	int				Dispatch(DWORD dwTrans, AOV* aov);
	int				DispatchRecv(char* szRecvBuffer, int iRecvByte);
	int				DispatchSend(DWORD dwTrans);
	int				SendMsg(char* msg, int iSize, WORD type);
	int				SendMsg(UPACKET& packet);
	void			Set(SOCKET LSock, SOCKADDR_IN LAddr, AServer* pServer);
	bool			DisConnect();
public:
	ANetUser();
	virtual ~ANetUser();
};

