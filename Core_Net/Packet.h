#pragma once
#include "Protocol.h"
#include <string>
using namespace std;

class APacket
{
public:
	char*		m_pOffset;
	char*		c_str() { return m_pOffset; }
	UPACKET		m_uPacket;
	void		PutData(const char* pData, int iSize);
	void		GetData(const char* pData, int iSize);
	void		Reset();
public:
	APacket& operator << (int data);
	APacket& operator << (long data);
	APacket& operator << (short data);
	APacket& operator << (float data);
	APacket& operator << (byte data);
	APacket& operator << (char* data);
	APacket& operator << (DWORD data);
	APacket& operator << (string data);

public:
	APacket& operator >> (int& data);
	APacket& operator >> (long& data);
	APacket& operator >> (short& data);
	APacket& operator >> (float& data);
	APacket& operator >> (byte& data);
	APacket& operator >> (char* data);
	APacket& operator >> (DWORD& data);
	APacket& operator >> (string& data);
	//������ �ѱ� �� ������ �Ѱܾ� ���� ��. �����ʹ� ����.

public:
	APacket();
	APacket(WORD Type);
	APacket(const APacket& packet);
	~APacket();
	//virtual ���̸� class size�� �����. network������ ���X
};

