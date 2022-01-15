#include "ThreadSend.h"
#include "Server.h"

bool AThreadSend::Run()
{
	AServer* pServer = (AServer*)m_pObject;
	SOCKET sock = pServer->m_LSock;

	while (1)
	{
		WaitForSingleObject(pServer->g_hMutex, INFINITE);
		list<ANetUser>::iterator Useriter;
		for (Useriter = pServer->g_UserList.begin(); Useriter != pServer->g_UserList.end();)
		{
			int iRet = pServer->Broadcast(*Useriter);
			if (iRet <= 0)
			{
				Useriter = pServer->g_UserList.erase(Useriter);
			}
			else
			{
				Useriter++;
			}
		}
		ReleaseMutex(pServer->g_hMutex);
		Sleep(1);
	}
	return 1;
}
AThreadSend::AThreadSend() {}
AThreadSend::AThreadSend(LPVOID value) : AThread(value) {}