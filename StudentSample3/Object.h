#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory.h>
#include <stdlib.h>
using namespace std;

class AObject
{
public:
	int		m_iType = 0; //0,1,2,3...
	char	m_csName[64];
	char	m_csBuffer[1000];
	int		m_iBufferSize;
	int		m_iCurrentPosition;

	//���������Լ� (�Լ� ��ü ����X, �������̽��� �ڽ� Ŭ�������� �����ϱ� ���� ���)
	virtual void	Show() = 0; 
	virtual void	Save() = 0;
	virtual void	Load() = 0;
	AObject()
	{
		m_iType = -1;
		m_iBufferSize = 0;
		m_iCurrentPosition = 0;
		memset(m_csName, 0, sizeof(char) * 64);
		memset(m_csBuffer, 0, sizeof(char) * 1000);
	}
	~AObject() 
	{
		m_iType = -1;
	}
};
