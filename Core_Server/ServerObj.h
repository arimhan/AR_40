#pragma once
#include "ServerStd.h"

class AServerObj
{
public:
	CRITICAL_SECTION	m_cs;
	HANDLE				m_hKillEvent;
public:
	AServerObj();
	virtual ~AServerObj();
};

