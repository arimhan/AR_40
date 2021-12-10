#pragma once
#include "Student.h"

class AStudentManager
{
public:
	AStudentManager()
	{
		g_Maxcount = 0;
		g_Start = 0;
		g_End = 0;
	}
	~AStudentManager()
	{
		DeleteAll();
	}

private:
	int			g_Maxcount = 0;
	AStudent*	g_Start = 0;
	AStudent*	g_End = 0;
public:
	bool	SaveFile();
	//연결리스트 파일 출력 기능

	AStudent* const NewNode();
	void	DeleteAll();
	void	Create();
	int		SaveInsert(FILE* fp);
	void	Load();
	void	Draw();
	void	AddLink(AStudent* const pUser);

	friend ostream& operator << (ostream& os, const AStudentManager& manager);
};
