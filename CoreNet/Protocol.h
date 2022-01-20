#pragma once
#include <windows.h>
using namespace std;
//PROTOCOL 수정 후 모든 구조가 변경되어야 함. (기존 소스 작동 불가), 클라랑 맞추기.


#pragma pack(push,1) //여기부터 pop까지 모두 1byte로 발송한단 뜻. 
typedef struct
{
	WORD			ioType;		//패킷 입출력 종류
	WORD			len;		//MSG바이트 크기
	WORD			type;		//패킷 종류
	DWORD			time;		//패킷전송 시간
}PACKET_HEADER; // => 이제 10BYTE!
typedef struct
{
	PACKET_HEADER	ph;
	char			msg[4096];

}UPACKET, * P_UPACKET;
//data는 UPACKET으로 전송 (msg안에 존재)
struct AChatMsg
{
	long			index;
	char			name[20];
	char			message[256];
};
struct ALoginReq
{
	char szID[20];
	char szPS[20];
};
struct ALoginAck
{
	int iRet;
	//1: 승인, -1 ID/PW없음
};
struct ANetResult
{
	int iRet;
	SOCKET sock_id;
};


#pragma pack(pop)
#define PACKET_HEADER_SIZE		10
#define PACKET_ALoginReq_Size	40
#define PACKET_ALoginAck_Size	4
//#define PACKET_CHAT_MSG		1000

enum PACKET_TYPE
{
	PACKET_CHECK_REQ = 1,
	PACKET_CHECK_ACK,

	PACKET_CHAT_NAME_REQ = 100,
	PACKET_CHAT_NAME_ACK,			//USER NAME
	PACKET_CHAT_MSG,				//CHAT MSG
	PACKET_LOGIN_REQ,				//
	PACKET_LOGIN_ACK,				//LOGIN
	PACKET_LOGOUT_REQ,				//
	PACKET_LOGOUT_ACK,				//LOGOUT
	PACKET_LOGOUT_USER,				//"~님이 나가셨습니다" 
};