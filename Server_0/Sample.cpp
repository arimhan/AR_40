#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

////�����޽��� ó��
//void Err_Quit()
//{
//
//}
////�����޽��� ���
//void Err_Display()
//{
//
//}

void main()
{
	//���� �ʱ�ȭ
	WSADATA wsd;
	if (WSAStartup(MAKEWORD(2,2), &wsd != 0))
	{
		return;
	}
	////WSADATA wsa;
	//if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	//{
	//	return;
	//}

	//���� ����

	//bind

	//listen

	//client ���� ����

	//accept ó�� ->
		//Ŭ���̾�Ʈ�� ������ ��� -> Recv ,���� ��� , ���

	//���� ����

	//WSACleanup();
	return;
}


