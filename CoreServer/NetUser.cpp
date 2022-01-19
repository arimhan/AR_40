#include "NetUser.h"
#include "Server.h"


int	ANetUser::Recv()
{//�񵿱�ε�
	//wsa recv buffer, ovrecvtype����
	//wsarecv
	m_wsaRecvBuffer.len = sizeof(char)*256;
	m_wsaRecvBuffer.buf = m_szRecv;
	m_ovRecv.type = 1000;
	DWORD dwRead;
	DWORD lpFlags = 0;
	BOOL Ret = WSARecv(m_Sock, &m_wsaRecvBuffer, 1, &dwRead, &lpFlags, (WSAOVERLAPPED*)&m_ovRecv, nullptr);

	return 0;
}
int ANetUser::Dispatch(DWORD dwTrans, TOV* tov)
{
	if (m_bConnect == false)
	{
		return 0;
	}
	if (tov->type == 1000)
	{
		if (!DispatchRecv(m_szRecv, dwTrans)) {}Recv();
	}
	if (tov->type == 2000)
	{
		if (!DispatchSend(dwTrans)) {}//Send();
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
	m_iWritePos += iRecvByte;	// ���� �� ������ ����� ��ġ
	m_iReadPos += iRecvByte;	// ��Ŷ���� ��ġ�κ��� ���� ����Ʈ

	if (m_iReadPos >= PACKET_HEADER_SIZE)
	{
		// ��Ŷ �ؼ� ����
		UPACKET* pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];

		//�ּ� 1�� �̻��� ��Ŷ ����
		if (pPacket->ph.len <= m_iReadPos)
		{
			do {
				APacket aPacket(pPacket->ph.type);
				memcpy(&aPacket.m_uPacket, &m_szRecvBuffer[m_iPacketPos], pPacket->ph.len);
				if (pPacket->ph.type == PACKET_CHAT_MSG)
				{
					m_PacketPool.push_back(aPacket);
				}
				else
				{
					XPacket xPacket;
					xPacket.pUser = this;
					xPacket.packet = aPacket;
					m_pServer->m_packetPool.push_back(xPacket);
				}
				//next packet
				m_iPacketPos += pPacket->ph.len;
				m_iReadPos -= pPacket->ph.len;
				if (m_iReadPos < PACKET_HEADER_SIZE) { break; } //��Ŷ �� ���� �ߴ�.
				pPacket = (UPACKET*)&m_szRecvBuffer[m_iPacketPos];
			} while (pPacket->ph.len<=m_iReadPos);
		}
	}
	return 1;
}
int ANetUser::DispatchSend(DWORD dwTrans)
{
	return 0;
}
int ANetUser::SendMsg(char* msg, int iSize, WORD type)
{
	//�񵿱� �ε�
	UPACKET uPacket;
	uPacket.ph.len = iSize + PACKET_HEADER_SIZE;
	uPacket.ph.type = type;
	memcpy(uPacket.msg, msg, iSize);

	m_wsaSendBuffer.len = uPacket.ph.len;
	m_wsaSendBuffer.buf = (char*)&uPacket;
	m_ovSend.type = 2000;

	DWORD dwWrite;
	DWORD lpFlags = 0; 
	BOOL Ret = WSASend(m_Sock, &m_wsaSendBuffer, 1, &dwWrite, 0, (WSAOVERLAPPED*)&m_ovSend, nullptr);

	if (Ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return false;
		}
	}
	return 0;
}
int ANetUser::SendMsg(UPACKET& packet)
{
	//�񵿱� �ε�
	m_wsaSendBuffer.len = packet.ph.len;
	m_wsaSendBuffer.buf = (char*)&packet;
	memcpy(m_wsaSendBuffer.buf,(char*)&packet, packet.ph.len - PACKET_HEADER_SIZE);
	m_ovSend.type = 2000;

	DWORD dwWrite;
	DWORD lpFlags = 0;
	BOOL Ret = WSASend(m_Sock, &m_wsaSendBuffer, 1, &dwWrite, 0, (WSAOVERLAPPED*)&m_ovSend, nullptr);

	if (Ret == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSA_IO_PENDING)
		{
			return false;
		}
	}
	return 0;
}
void	ANetUser::Set(SOCKET sock, SOCKADDR_IN addr)
{
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
