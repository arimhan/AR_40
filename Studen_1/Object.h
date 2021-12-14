#pragma once
#include <iostream>
#include <memory.h>
#include <stdlib.h>
using namespace std;

class AObject
{
public:
	// Student를 Type별로 분리
	// 학생들 name
	// buffer , buffersize , 현재위치=?
	// 학생 타입별로 출력, 저장, 로드 함수 다르게 구현

	int m_iType = 0; //type기본값 0 (Student) / 1: MidStudent / 2: HighStudent / 3: ColStudent
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
		//char형 name, buffer 메모리초기화
		memset(m_csName, sizeof(char), 64);
		memset(m_csBuffer, sizeof(char), 1000);
	}
	~AObject()
	{
		m_iType = 0;
	}

};

