#include <WinSock2.h>
#include <iostream>

#pragma comment (lib, "ws_32.lib")
using namespace std;
#define PORT_NUM 9190				// ��Ʈ��ȣ, �� ��Ʈ��ȣ�� ���� ���� �� �ִ�. 1024~ ����!
#define ADRESS_NUM "192.168.0.44"	// ��ǻ�� IP �ּ� , ��ȣ 44, 48
// Soket_Client2

void main()
{
	unsigned short iPort = PORT_NUM;
	WSADATA wsa;
	int iRet;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET clSock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(iPort);
	sa.sin_addr.s_addr = htonl(INADDR_ANY);
	//������ �ش� ip�� ����

	iRet = bind(clSock, (SOCKADDR*)&sa, sizeof(sa));
	//(SOCKADDR*)&sa => *name����(&sa) �޾ƾ� �ϴµ� SOCKADDR_IN * ������ �μ��� const sockaddr* ������ �Ű������� ȣȯ�� �ȵ�.
	
	

}