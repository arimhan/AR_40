#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "ServerObj.h"
#include "Packet.h"


struct TOV
{
	OVERLAPPED ov;
	int type;
};

class ANetUser : public AServerObj
{
public:
	bool			m_bConnect = false;
	SOCKET			m_Sock;
	SOCKADDR_IN		m_Addr;
	string			m_csName;
	short			m_iPort;
public:
	//buffer ฐüทร
	TOV			m_ovRecv;
	TOV			m_ovSend;
	WSABUF		m_wsaRecvBuffer;
	WSABUF		m_wsaSendBuffer;
	char		m_szRecv[256];
	char		m_szSend[256];
	//-------------------------------------------
	char			m_szRecvBuffer[2048];
	int				m_iPacketPos;
	int				m_iWritePos;
	int				m_iReadPos;

	list<APacket>	m_PacketPool;
public:
	int				Recv();
	int				Dispatch(DWORD dwTrans, TOV* tov);
	int				DispatchRecv(char* szRecvBuffer, int iRecvByte);
	int				DispatchSend(DWORD dwTrans);

	void			Set(SOCKET LSock, SOCKADDR_IN LAddr);
	bool			DisConnect();
public:
	ANetUser();
	virtual ~ANetUser();

};

