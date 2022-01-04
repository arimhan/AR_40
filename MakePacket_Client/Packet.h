#pragma once
#include <string>
#include <Windows.h>
#include "Protocol.h"

//struct AChatMsg
//{
//  int				index;
//	char			name[20];
//	long			damage;
//	char			message[2048];
//};

class APacket
{
public:
	char*		m_pOffset;
	UPACKET		m_uPacket;
	void		PutData(const char* pData, int iSize);
	void		GetData(const char* pData, int iSize);
public:
	APacket& operator <<(int data);
	APacket& operator <<(long data);
	APacket& operator <<(short data);
	APacket& operator <<(float data);
	APacket& operator <<(byte data);
	APacket& operator <<(char* data);
	APacket& operator <<(DWORD data);
	APacket& operator <<(string data);

public:
	APacket& operator >>(int& data);
	APacket& operator >>(long& data);
	APacket& operator >>(short& data);
	APacket& operator >>(float& data);
	APacket& operator >>(byte& data);
	APacket& operator >>(char* data);
	APacket& operator >>(DWORD& data);
	APacket& operator >>(string& data);
	//데이터 넘길 때 참조로 넘겨야 값이 들어감. 포인터는 제외.

public:
	APacket();
	APacket(WORD Type);
	~APacket();
	//virtual 붙이면 class size가 변경됨. network에서는 사용X
};

