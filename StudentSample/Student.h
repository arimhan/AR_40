#pragma once


class AUser
{
public:
	int		m_iIndex;
	int		m_iKor;
	AUser*  pNext;

	AUser()
	{
		m_iIndex = 0;
		m_iKor = 0;
		pNext = NULL;
	}
	AUser(int i, int Kor)
	{
		m_iIndex = i;
		m_iKor = Kor;
		pNext = NULL;
	}
	~AUser() {}
};
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
	void	AddLink(AUser* pUser);
};


