#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory.h>
#include <stdlib.h>

using namespace std;

class AObject
{
public:
	char	m_csBuffer[1000];
	int		m_iBufferSize;
	int		m_iCurrentPosition;
	virtual void	Show() = 0; //순수가상함수
	virtual void	Save() = 0;
	virtual void	Load() = 0;
	AObject()
	{
		m_iBufferSize = 0;
		m_iCurrentPosition = 0;
		memset(m_csBuffer, 0, sizeof(char) * 1000);
	}
	~AObject() 
	{
	}
};
