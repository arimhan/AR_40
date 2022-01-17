#pragma once
#include "Thread.h"
class AAccepter :public AThread
{
public:
	bool RunServer() override;

	AAccepter();
	AAccepter(LPVOID value);

};

