#pragma once
#include "ServerObj.h"
#include <process.h>

class AThread : public AServerObj
{
public:
	uintptr_t	 m_hThread;
	unsigned int m_iID;
	bool		 m_bStarted;
	LPVOID		 m_pObject;
					 
public:			 
	void  Create();
	void  Create(LPVOID pValue);
	void  Join();
	void  Detach();
	virtual bool RunServer();
	static unsigned int WINAPI	Runner(LPVOID param);

public:
	AThread();
	AThread(LPVOID pValue);
	virtual ~AThread(); //상속할거니까
};

