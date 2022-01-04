#pragma once
#include <windows.h>
#define PACKET_HEADER_SIZE 4

#pragma pack(push,1) //������� pop���� ��� 1byte�� �߼��Ѵ� ��.
typedef struct
{
	WORD			len;
	WORD			type;
}PACKET_HEADER; // 4byte�̹Ƿ� �켱 ����
typedef struct
{
	PACKET_HEADER	ph;
	char			msg[4096];

}UPACKET, *P_UPACKET;
//data�� UPACKET���� ���� (msg�ȿ� ����)
struct AChatMsg
{
	int				index;
	char			name[20];
	long			damage;
	char			message[256]; 
	//msg �� int, float, char...�� �پ��� type�� �� �� �ֱ� ������ ���� ���� �ʿ�
	//���� ����ü�� �������� ���� ��� ���� ����. ä�ö����� ��¿ �� ���� �����. -> �� �������� ū �迭�� �ѱ��.
	//memcpy�ؼ� �Ѱܵ� ��������� �ʹ� ���� �޸𸮸� �Ҹ��ϱ� ������ ������ ����. -> �׽�Ʈ�� ��� �߰��ϰԵǸ� �� ����� ����ǹǷ� ������X
	//����ü �� �ʿ��� �����͸� �ѱ� �� �ִ� ����ȭ ����� �ʿ��ϴ�.
};
#pragma pack(pop)

#define PACKET_CHAT_MSG 1000

// ���� ��� 1
// UPACKET sendPacket ���� ����
// sendPacket.ph.len = strlen(msg) + PACKET_HEADER_SIZE   (UPACKET�� ��ü ���� = msg�� ���� + ��� ������)
// sendPacket.ph.type = PACKET_CHAT_MSG 
// sendPacket.ph.msg = msg
//  UPACKET�� ��ü ���� = msg�� ���� + ��� ������
// char�� msg[arr size]�ȿ� txt�� ���� ��Ŷ °�� ����



//���� ��� 2
//AChatMsg msg : name�� ����
//msg.name = "ȫ�浿"
//msg.message = "�ȳ��ϼ���"
//sendPacket.ph.len = strlen(msg) + PACKET_HEADER_SIZE  
//sendPacket.ph.type = PACKET_CHAT_MSG 
//sendPacket.ph.msg = msg