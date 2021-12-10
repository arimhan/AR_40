#pragma once
#include "Student.h"

class AStudentManager
{
public:
	AStudentManager()
	{
		g_iMaxUserCounter = 0;
		g_pHeadUserList = 0;
		g_pEndUser = 0;
	}

	~AStudentManager()
	{
		DeleteAll();
	}

private:
	int			g_iMaxUserCounter;
	AStudent* g_pHeadUserList;
	AStudent* g_pEndUser;

public:
	bool	FileSave();
	//연결리스트 출력 기능 구현

	AStudent* const NewNode();
	void	DeleteAll();
	void	Create();
	int		Insert(FILE* fp);
	void	Load();
	void	Draw();
	void	AddLink(AStudent* const pUser);

	friend ostream& operator << (ostream& os, const AStudentManager& data);

};


