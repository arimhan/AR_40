#include <iostream>
#include <winSock2.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
#define PORT_NUM 10000 //10000 ������ ��Ʈ��ȣ
#define ADRESS_NUM "192.168.0.12" //������ ��ǻ�� IP �ּ�


//<���� ����>
// ������, TCP��������(SOCK_STREAM,IPPROTO_TCP)
// �񿬰���, UDP ��������(SOCK_DGRAM,IPPROTO_UDP)

void main()
{
	unsigned short iPort = PORT_NUM;
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET sock = socket (AF_INET,AF_INET,0);
	//�������� ���� �׷��� �߰� TYPE�� ��õǸ� 0���� �����ص� OK
	//SOCK_STREAM : TCP
	//SOCK_DGRAM : UDP

	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port= htons(9000); // ���� ��Ʈ ��ȣ
	sa.sin_addr.s_addr=inet_addr(ADRESS_NUM);
	//IP ��ũ�η� ������ ���� ����. ������ S_un.S_addr�� ����.
	//inet_addr���ڿ��� 4byte�� �ٲ㼭 ����

	//�����Ѵ�~
	int iRet = connect(sock, (sockaddr*)&sa, sizeof(sa));

	//������~ �޴� ���� ����
	char szBuffer[256] = "�ȳ�"; // [] ����θ� �ش��� �������� ���۵�.
	char szRecvBuffer[256] = { 0, };

	// data ����
	int iSendByte = send(sock, szBuffer, sizeof(szBuffer), 0);

	//������ ���ڽý����� ���� (���ú� ����)
	int iRetByte = recv(sock, szRecvBuffer, 256, 0);
	cout << szRecvBuffer << endl;

	//�ݱ�~
	WSACleanup();
}