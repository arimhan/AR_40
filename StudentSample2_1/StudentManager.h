#pragma once
#include "LinkedList.h"
#include "FileIO.h"

class AStudentManager
{
public:
	AStudentManager()
	{
	}

	~AStudentManager()
	{
		m_List.DeleteAll();
	}
	ALinkedList<AStudent> m_List;
	AFileIO m_FileIO;

public:
	bool	FileSave(const char* pFileName);
	//연결리스트 출력 기능 구현

	ANodeBox<AStudent>* const NewNode();
	void	Create();
	void	Load(const char* pFileName);
	void	Draw();
	friend ostream& operator << (ostream& os, const AStudentManager& manager);//data); 

};


