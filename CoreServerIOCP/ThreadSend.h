#pragma once
#include "Thread.h"
class   AThreadSend :  public AThread
{
public: 
	bool Run() override;
public:
	AThreadSend();
	AThreadSend(LPVOID value);
};

