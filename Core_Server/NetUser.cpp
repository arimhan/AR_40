#include "NetUser.h"
#include "Server.h"

int	ANetUser::Recv()
{
	AOV* ov = new AOV(AOV::MODE_RECV);
	m_wsaRecvBuffer.len = sizeof(char)*256;
	m_wsaRecvBuffer.buf = m_szRecv;
	DWORD dwRead;
	DWORD lpFlags = 0;
	BOOL Ret = WSARecv(m_Sock, &m_wsaRecvBuffer, 1, &dwRead, &lpFlags, 
		(WSAOVERLAPPED*)ov, nullptr);

	if (Ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return false;
		}
	}
	return 0;
}
int ANetUser::Dispatch(DWORD dwTrans, AOV* aov)
{
	delete aov;
	if (m_bConnect == false)
	{
		return 0;
	}
	if (aov->type == AOV::MODE_RECV)
	{
		if (!DispatchRecv(m_szRecv, dwTrans)) 
		{}
		Recv();
		return 1;
	}
	if (aov->type == AOV::MODE_SEND)
	{
		if (!DispatchSend(dwTrans)) {}
	}
	//type 1000 -> recv
	// 2000 -> send

	return 1;
}
int	ANetUser::DispatchRecv(char* szRecvBuffer, int iRecvByte)
{
	if (m_iWritePos + iRecvByte >= 2048)
	{
		if (m_iReadPos > 0)
		{
			memmove(&m_szRecvBuffer[0], &m_szRecvBuffer[m_iPacketPos], m_iReadPos);
		}
		m_iPacketPos = 0;
		m_iWritePos = m_iReadPos;
	}
	memcpy(&m_szRecvBuffer[m_iWritePos], szRecvBuffer, iRecvByte);
	m_iWritePos += iRecvByte;	// 버퍼 내 이전에 저장된 위치
	m_iReadPos += iRecvByte;	// 패킷시작 위치로부터 받은 바이트

	if (m_iReadPos >= PACKET_HEADER_SIZE)
	{
		// 패킷 해석 가능
		UPACKET* pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
		//최소 1개 이상의 패킷 도착
		if (pPacket->ph.len <= m_iReadPos)
		{
			do {
				APacket aPacket(pPacket->ph.type);
				memcpy(&aPacket.m_uPacket, &m_szRecvBuffer[m_iPacketPos], pPacket->ph.len);
				m_PacketPool.push_back(aPacket);

				//next packet
				m_iPacketPos += pPacket->ph.len;
				m_iReadPos -= pPacket->ph.len;
				if (m_iReadPos < PACKET_HEADER_SIZE) 
				{
					break; 
				} //패킷 안 오면 중단.
				pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
			} while (pPacket->ph.len<=m_iReadPos);
		}
	}
	return 1;
}
int ANetUser::DispatchSend(DWORD dwTrans)
{
	cout << "DispatchSend";
	return 0;
}
void	ANetUser::Set(SOCKET sock, SOCKADDR_IN addr, AServer* pServer)
{
	m_pServer = pServer;
	m_bConnect = true;
	ZeroMemory(m_szRecvBuffer, sizeof(char) * 2048);
	m_iPacketPos = 0;
	m_iWritePos = 0;
	m_iReadPos = 0;

	m_Sock = sock;
	m_Addr = addr;
	m_csName = inet_ntoa(addr.sin_addr);
	m_iPort = ntohs(addr.sin_port);
}
bool ANetUser::DisConnect()
{
	closesocket(m_Sock);
	return true;
}
ANetUser::ANetUser(){}
ANetUser::~ANetUser(){}
