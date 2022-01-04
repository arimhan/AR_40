#include "Packet.h"

void APacket::PutData(const char* pData, int iSize)
{
	m_uPacket.ph.len += iSize;
	memcpy(m_pOffset, pData, iSize); //msg 에 + 4byte 후 m_pOffset를 iSize 만큼 추가, 값 변경
	m_pOffset += iSize;
}
void APacket::GetData(const char* pData, int iSize)
{
	memcpy(const_cast<char*>(pData), m_pOffset, iSize); 
	// 형변환 후 pData에서 m_pOffset으로 데이타 넘겨줌
	m_pOffset += iSize;
}



//---------------------data 발신(보내기)
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
	PutData((char*)&data, strlen(data)+1);  
	//STL은 null문자를 빼기 때문에 +1을 해준다.
	return *this;
}
APacket& APacket::operator <<(DWORD data)
{
	PutData((char*)&data, sizeof(DWORD));
	return *this;
}
APacket& APacket::operator <<(string data)
{
	int iSize = strlen(m_pOffset+1);
	PutData(const_cast<char*>(data.c_str()), iSize);
	//string은 size함수가 있기 때문에 바로 size함수를 사용.
	//근데 뺄때 문제가 발생하므로 iSize 변수에 값을 넣어 사용한다. 
	//null : 시작 주소로부터 ~ data의 끝을 찾아 출력한다.
	return *this;
}

//---------------------data 수신(받기) , &참조값 
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
	GetData((char*)&data, strlen(data) + 1);
	//STL은 null문자를 빼기 때문에 +1을 해준다.
	return *this;
}
APacket& APacket::operator >>(DWORD& data)
{
	GetData((char*)&data, sizeof(DWORD));
	return *this;
}
APacket& APacket::operator >>(string& data)
{
	int iSize = strlen(m_pOffset + 1);
	GetData(const_cast<char*>(data.c_str()), iSize);
	return *this;
}

//------------------생성자를 통해 값 초기화 진행
APacket::APacket() 
{
	//생성 시 사이즈 초기화 먼저
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
APacket::~APacket(){}
