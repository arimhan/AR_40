#pragma once
#include <windows.h>
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
	//보통 구조체에 가변적인 길이 사용 하지 않음. 채팅때문에 어쩔 수 없이 사용중. -> 맨 마지막에 큰 배열로 넘기기.
	//memcpy해서 넘겨도 상관없지만 너무 많은 메모리를 소모하기 때문에 권하지 않음. -> 테스트로 멤버 추가하게되면 그 멤버도 적용되므로 사용권장X
	//구조체 내 필요한 데이터만 넘길 수 있는 직렬화 기능이 필요하다.
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