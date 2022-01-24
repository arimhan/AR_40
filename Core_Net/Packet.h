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
	//데이터 넘길 때 참조로 넘겨야 값이 들어감. 포인터는 제외.

public:
	APacket();
	APacket(WORD Type);
	APacket(const APacket& packet);
	~APacket();
	//virtual 붙이면 class size가 변경됨. network에서는 사용X
};

