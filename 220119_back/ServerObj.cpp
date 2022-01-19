#include "ServerObj.h"

AServerObj::AServerObj()
{
	InitializeCriticalSection(&m_cs);
	m_hKillEvent = ::CreateEvent(0, TRUE, FALSE, 0);
}
AServerObj:: ~AServerObj()
{
	DeleteCriticalSection(&m_cs);
	CloseHandle(m_hKillEvent);
}