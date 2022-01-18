#pragma once
#include <windows.h>
using namespace std;
//PROTOCOL ���� �� ��� ������ ����Ǿ�� ��. (���� �ҽ� �۵� �Ұ�), Ŭ��� ���߱�.

enum PACKET_TYPE
{
	PACKET_CHECK_REQ = 1,
	PACKET_CHECK_ACK,

	PACKET_CHAT_NAME_REQ,		//
	PACKET_CHAT_NAME_REQ,		//USER NAME
	PACKET_CHAT_MSG,			//CHAT MSG
	PACKET_LOGIN_REQ,			//
	PACKET_LOGIN_ACK,			//LOGIN
	PACKET_LOGOUT_REQ,			//
	PACKET_LOGOUT_ACK,			//LOGOUT
	PACKET_LOGOUT_USER,			//"~���� �����̽��ϴ�" 
};


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

}UPACKET, *P_UPACKET;
//data�� UPACKET���� ���� (msg�ȿ� ����)
struct AChatMsg
{
	long			index;
	char			name[20];
	char			message[256]; 
};
#pragma pack(pop)
#define PACKET_HEADER_SIZE	10
#define PACKET_CHAT_MSG		1000

