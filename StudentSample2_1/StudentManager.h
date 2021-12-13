#pragma once
#include "NodeBox.h"

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
	int		  g_iMaxUserCounter;
	ANodeBox* g_pHeadUserList;
	ANodeBox* g_pEndUser;

public:
	bool	FileSave(const char* pFileName);
	//연결리스트 출력 기능 구현

	ANodeBox* const NewNode();
	void	DeleteAll();
	void	Create();
	int		Insert(FILE* fp);
	void	Load(const char* pFileName);
	void	Draw();
	void	AddLink(ANodeBox* const pUser);

	friend ostream& operator << (ostream& os, const AStudentManager& data);

};


