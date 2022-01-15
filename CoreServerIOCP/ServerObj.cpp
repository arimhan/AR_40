#include "ServerObj.h"


AServerObj::AServerObj()
{
	InitializeCriticalSection(&m_cs);
}
AServerObj:: ~AServerObj()
{
	DeleteCriticalSection(&m_cs);
}