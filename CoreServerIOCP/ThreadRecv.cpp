#include "ThreadRecv.h"
#include "Server.h"

bool AThreadRecv::Run()
{
	AServer* pServer = (AServer*)m_pObject;
	SOCKET sock = pServer->m_LSock;

	while (1)
	{
		//if (WaitForSingleObject(pServer->m_hKillEvent, 1)) { break; }

		WaitForSingleObject(pServer->g_hMutex, INFINITE);
		list<ANetUser>::iterator Useriter;
		for (Useriter = pServer->g_UserList.begin(); Useriter != pServer->g_UserList.end();)
		{
			int iRet = pServer->RecvUser(*Useriter);
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
AThreadRecv::AThreadRecv() {}
AThreadRecv::AThreadRecv(LPVOID value) : AThread(value) {}