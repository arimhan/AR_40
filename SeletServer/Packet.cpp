#include "Packet.h"

void APacket::PutData(const char* pData, int iSize)
{
	m_uPacket.ph.len += iSize;
	memcpy(m_pOffset, pData, iSize); //msg �� + 4byte �� m_pOffset�� iSize ��ŭ �߰�, �� ����
	m_pOffset += iSize;
}
void APacket::GetData(const char* pData, int iSize)
{
	memcpy(const_cast<char*>(pData), m_pOffset, iSize); 
	// ����ȯ �� pData���� m_pOffset���� ����Ÿ �Ѱ���
	m_pOffset += iSize;
}



//---------------------data �߽�(������)
APacket& APacket::operator <<(int data)
{
	PutData((char*)&data, sizeof(int));
	return *this;
}
APacket& APacket::operator <<(long data)
{
	PutData((char*)&data, sizeof(long));
	return *this;
}
APacket& APacket::operator <<(short data)
{
	PutData((char*)&data, sizeof(short));
	return *this;
}
APacket& APacket::operator <<(float data)
{
	PutData((char*)&data, sizeof(float));
	return *this;
}
APacket& APacket::operator <<(byte data)
{
	PutData((char*)&data, sizeof(byte));
	return *this;
}
APacket& APacket::operator <<(char* data)
{
	PutData(data, strlen(data)+1);
	return *this;
}
APacket& APacket::operator <<(DWORD data)
{
	PutData((char*)&data, sizeof(DWORD));
	return *this;
}
APacket& APacket::operator <<(string data)
{
	PutData(data.c_str(), data.size()+1);
	return *this;
}

//---------------------data ����(�ޱ�) , &������ 
APacket& APacket::operator >>(int& data)
{
	GetData((char*)&data, sizeof(int));
	return *this;
}
APacket& APacket::operator >>(long& data)
{
	GetData((char*)&data, sizeof(long));
	return *this;
}
APacket& APacket::operator >>(short& data)
{
	GetData((char*)&data, sizeof(short));
	return *this;
}
APacket& APacket::operator >>(float& data)
{
	GetData((char*)&data, sizeof(float));
	return *this;
}
APacket& APacket::operator >>(byte& data)
{
	GetData((char*)&data, sizeof(byte));
	return *this;
}
APacket& APacket::operator >>(char* data)
{
	int iSize = strlen(m_pOffset) + 1;
	GetData(data, iSize);
	return *this;
}
APacket& APacket::operator >>(DWORD& data)
{
	GetData((char*)&data, sizeof(DWORD));
	return *this;
}
APacket& APacket::operator >>(string& data)
{
	int iSize = strlen(m_pOffset+1);
	GetData(data.c_str(), iSize);
	return *this;
}

//------------------�����ڸ� ���� �� �ʱ�ȭ ����
APacket::APacket() 
{
	//���� �� ������ �ʱ�ȭ ����
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.len = PACKET_HEADER_SIZE;
	m_pOffset = m_uPacket.msg;
}
APacket::APacket(WORD Type)
{
	//type
	ZeroMemory(&m_uPacket, sizeof(UPACKET));
	m_uPacket.ph.len = PACKET_HEADER_SIZE;
	m_uPacket.ph.type = Type;
	m_pOffset = m_uPacket.msg;
}
APacket::APacket(const APacket& packet)
{
	//const APacket
	m_uPacket.ph = packet.m_uPacket.ph;
	memcpy(m_uPacket.msg, packet.m_uPacket.msg, sizeof(char) * 4096);
	//memcpy�� msg�� �ִ���̸� ���ؼ� ����ó��
	m_pOffset = m_uPacket.msg;
}
APacket::~APacket(){}
