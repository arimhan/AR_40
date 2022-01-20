#pragma once
#include <windows.h>
using namespace std;
//PROTOCOL ���� �� ��� ������ ����Ǿ�� ��. (���� �ҽ� �۵� �Ұ�), Ŭ��� ���߱�.


#pragma pack(push,1) //������� pop���� ��� 1byte�� �߼��Ѵ� ��. 
typedef struct
{
	WORD			ioType;		//��Ŷ ����� ����
	WORD			len;		//MSG����Ʈ ũ��
	WORD			type;		//��Ŷ ����
	DWORD			time;		//��Ŷ���� �ð�
}PACKET_HEADER; // => ���� 10BYTE!
typedef struct
{
	PACKET_HEADER	ph;
	char			msg[4096];

}UPACKET, * P_UPACKET;
//data�� UPACKET���� ���� (msg�ȿ� ����)
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
	//1: ����, -1 ID/PW����
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
	PACKET_LOGOUT_USER,				//"~���� �����̽��ϴ�" 
};