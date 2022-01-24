#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
using namespace std;


void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN sa;
	ZeroMemory(&sa, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(9110); // ���� ��Ʈ ��ȣ, �� ��Ʈ��ȣ�� �����ϴ� �ֵ� �� ���� �����ϵ��� ����
	sa.sin_addr.s_addr = htonl(INADDR_ANY); //��� IP ���� ���

	int iRet = bind(sock, (sockaddr*)&sa, sizeof(sa));
	if (iRet == SOCKET_ERROR) return;

	SOCKADDR_IN ClientAddr;
	int iLen = sizeof(ClientAddr);
	char buf[256] = {};
	while (1)
	{
		recvfrom(sock, buf, 256, 0, (SOCKADDR*)&ClientAddr, &iLen);





		SOCKET ClientSock = accept(ListenSock, (sockaddr*)&ClientAddr, &iLen);
		//accept�Ǹ� ListenSock�� ��ȯ�ȴ�. ���� �����ߴ���(&ClientAddr), ��ȯ���� Ȯ�� ����.
		//�� ������ &iLen���� ���� �ƴ� �ּҸ� ���ϱ� ������ sizeof�Լ��� ����ϸ� �ȵ�. �׷��� ������ �޾Ƽ� �ּҸ� �Ѱܾ� ��.

		if (ClientSock == SOCKET_ERROR) //Client�� ��ȿ�� ������ �ƴ� ���
		{
			int iError = WSAGetLastError();
			cout << "ErrorCode: " << iError << endl;
			if (iError != WSAEWOULDBLOCK) //������ �ƴ� ��� ó��
			{
				break;
			}
			continue;
		}
		cout << "IP: " << inet_ntoa(ClientAddr.sin_addr) << ", Port: " << ntohs(ClientAddr.sin_port) << endl; //ip, port ���
	}

	WSACleanup();
}