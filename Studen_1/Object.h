#pragma once
#include <iostream>
#include <memory.h>
#include <stdlib.h>
using namespace std;

class AObject
{
public:
	// Student�� Type���� �и�
	// �л��� name
	// buffer , buffersize , ������ġ=?
	// �л� Ÿ�Ժ��� ���, ����, �ε� �Լ� �ٸ��� ����

	int m_iType = 0; //type�⺻�� 0 (Student) / 1: MidStudent / 2: HighStudent / 3: ColStudent
	char m_csName[64];
	char m_csBuffer[1000];
	int m_iBufferSize;
	int m_iCurPosition;
	virtual void Show() = 0;
	virtual void Save() = 0;
	virtual void Load() = 0;

	AObject()
	{
		m_iType = 0;
		m_iBufferSize = 0;
		m_iCurPosition = 0;
		//char�� name, buffer �޸��ʱ�ȭ
		memset(m_csName, sizeof(char), 64);
		memset(m_csBuffer, sizeof(char), 1000);
	}
	~AObject()
	{
		m_iType = 0;
	}

};

