#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
using namespace std;

void main()
{
	//Broadcast��� ������ socket�߰�. -> socketopt
	char flag = true;
	
	if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag)) < 0)
	{
		//socket error check !
		closesocket(sock);
	}

	//address.sin_addr.s_addr = INADDR_BROADCAST; �� �����Ǿ� ����.
	//INADDR_BROADCAST -> �ش� �ּҿ� �ִ� user���� data�� ��� ���۵�. (��� ����X)
	//���⼭ sock�� Broadcast�� sock��. �� sock�� ����� �ش��ϴ� port��ȣ�� ������ user���� ���.
	//�׷��� ������ userlist�� �� �ʿ䰡 ����. -> ���⼭ Ư���� user���� data�����ϴ� ����� �ʿ��ϴ�.

	//�� sender���α׷� 2�� ���� �Ұ�..��

}


