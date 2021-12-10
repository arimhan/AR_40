#pragma once
#include <iostream>
#include <string>
using namespace std;
class ASubject
{
private:
	int	m_Kor;
public:
	void Set(int m_Kor);
	int GetKor();
public:
	ASubject();
	~ASubject();
};

