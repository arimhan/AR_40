#pragma once
#include "Thread.h"
class Accept :public AThread
{
public:
	bool RunServer() ;

	Accept();
	Accept(LPVOID value);

};

