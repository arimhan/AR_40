#pragma once
#include "Thread.h"
class AThreadRecv :   public AThread
{
public:
	bool Run() override;
public:
	AThreadRecv();
	AThreadRecv(LPVOID value);
};

