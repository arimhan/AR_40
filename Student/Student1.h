#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

//class AUser
//{
//public:
//	int		m_Index;
//	//int		m_Kor;
//	AUser*	pNext;
//
//	AUser()
//	{
//		m_Index = 0;
//		m_Kor = 0;
//		pNext = NULL;
//	}
//	AUser(int i, int Kor)
//	{
//		m_Index = i;
//		m_Kor = Kor;
//		pNext = NULL;
//	}
//	~AUser() {}
//};

class AStudent
{
public:
	AStudent() 
	{
		g_Maxcount = 0;
		g_Start = 0;
		g_End = 0;
	}
	~AStudent() 
	{ 
		DeleteAll(); 
	}


private:
	int		g_Maxcount = 0;
	AUser*	g_Start = 0;
	AUser*	g_End = 0;
public:
	bool	SaveFile();
	//연결리스트 파일 출력 기능

	AUser*	NewNode();
	void	DeleteAll();
	void	Create();
	int		SaveInsert(FILE* fp);
	void	Load();
	void	Draw();
	//void	AddLink(AUser* pUser);
};

