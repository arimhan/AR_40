#pragma once
#include "Thread.h"
class AAccepter :public AThread
{
	SOCKET			m_LSock;
public:
	virtual bool	Set(int iPort);
	bool			RunServer() override;

	AAccepter();
	AAccepter(LPVOID value);
	virtual ~AAccepter();
};

