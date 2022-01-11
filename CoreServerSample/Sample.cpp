//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Server.h"


DWORD WINAPI RecvThread(LPVOID param) // sendthread ó�� �� ��ȯ. 1��ü 1������ ��ȯ����
{
	AServer* pServer = (AServer*)param;
	SOCKET sock = pServer->m_LSock;

	while (1)
	{
		WaitForSingleObject(pServer->g_hMutex, INFINITE);
		//EnterCriticalSection(&g_CS);
		list<ANetUser>::iterator Useriter;
		for (Useriter = pServer->g_UserList.begin(); Useriter != pServer->g_UserList.end();)
		{
			int iRet = pServer->RecvUser(*Useriter);
			if (iRet <= 0) { Useriter = pServer->g_UserList.erase(Useriter); }
			else { Useriter++; }
		}
		//LeaveCriticalSection(&g_CS);
		ReleaseMutex(pServer->g_hMutex);
		Sleep(1);
	}
}
DWORD WINAPI SendThread(LPVOID param) // sendthread ó�� �� ��ȯ. 1��ü 1������ ��ȯ����
{
	AServer* pServer =(AServer*) param;
	SOCKET sock = pServer->m_LSock;
	char szBuffer[256] = { 0, };

	while (1)
	{
		WaitForSingleObject(pServer->g_hMutex, INFINITE);
		//EnterCriticalSection(&g_CS);
		list<ANetUser>::iterator Useriter;
		for (Useriter = pServer->g_UserList.begin(); Useriter != pServer->g_UserList.end();)
		{
			int iRet = pServer->Broadcast(*Useriter);
			if (iRet <= 0) { Useriter = pServer->g_UserList.erase(Useriter); }
			else { Useriter++; }
		}
		//LeaveCriticalSection(&g_CS);
		ReleaseMutex(pServer->g_hMutex);
		Sleep(1);
	}
}

void main()
{
	//AServer ���� , Init�Լ� ȣ��
	AServer server;
	server.Init();

	//������ ����
	DWORD ThreadId;
	HANDLE hThreadRecv = ::CreateThread(0, 0, RecvThread, &server, 0, &ThreadId);

	DWORD ThreadIdSend;
	HANDLE hThreadSend = ::CreateThread(0, 0, SendThread, &server, 0, &ThreadIdSend);


	server.RunServer();

	server.Release();
	CloseHandle(hThreadRecv);
	CloseHandle(hThreadSend);

}