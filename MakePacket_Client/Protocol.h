#pragma once
#include <windows.h>

using namespace std;
#define PACKET_HEADER_SIZE 4

#pragma pack(push,1) //여기부터 pop까지 모두 1byte로 발송한단 뜻.
typedef struct
{
	WORD			len;
	WORD			type;
}PACKET_HEADER; // 4byte이므로 우선 고정
typedef struct
{
	PACKET_HEADER	ph;
	char			msg[4096];

}UPACKET, *P_UPACKET;
//data는 UPACKET으로 전송 (msg안에 존재)
struct AChatMsg
{
	int				index;
	char			name[20];
	long			damage;
	char			message[256];
	//msg 내 int, float, char...등 다양한 type이 들어갈 수 있기 때문에 구조 정의 필요
};
#pragma pack(pop)

#define PACKET_CHAT_MSG 1000

// 전송 방법 1
// UPACKET sendPacket 으로 전송
// sendPacket.ph.len = strlen(msg) + PACKET_HEADER_SIZE   (UPACKET의 전체 길이 = msg의 길이 + 헤더 사이즈)
// sendPacket.ph.type = PACKET_CHAT_MSG 
// sendPacket.ph.msg = msg
//  UPACKET의 전체 길이 = msg의 길이 + 헤더 사이즈
// char형 msg[arr size]안에 txt가 들어가서 패킷 째로 전송



//전송 방법 2
//AChatMsg msg : name이 포함
//msg.name = "홍길동"
//msg.message = "안녕하세요"
//sendPacket.ph.len = strlen(msg) + PACKET_HEADER_SIZE  
//sendPacket.ph.type = PACKET_CHAT_MSG 
//sendPacket.ph.msg = msg