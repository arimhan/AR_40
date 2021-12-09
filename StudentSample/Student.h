#pragma once

//1) 데이터 초기화 및 입력



class AStudent
{
public:
	int			 m_iIndex;
	int			 m_iKor;
	AStudent*	 pNext;
	int			g_iMaxUserCounter = 0;
	AStudent*	g_pHeadUserList = 0;
	AStudent*	g_pEndUser = 0;
public:
	AStudent*	NewNode();
	FILE*		Create();
	int			Insert(FILE* fp);
	void		Load();
	void		Draw(int iCounter);
	void		AllDelete();

private:
};


struct AUser
{
	int m_iIndex;
	int m_iKor;
	AStudent* pNext;
};