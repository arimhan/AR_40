#pragma once
#include "TemLinkedList.cpp"
#include "FileIO.h"
#include "Object.h"
#include <string>

class AStudentManager
{
public:
	AStudentManager(){}
	~AStudentManager() { DeleteAll(); }
	ALinkedList<AStudent>	m_List;
	//AFileIO					m_FileIO;

public:
	bool	m_bRun;
	bool	FileSave(const char* pFileName);

	ANodeBox<AStudent>* const NewNode();
	void	DeleteAll();
	void	Create();
	void	Load(const char* pFileName);
	void	Draw();

	friend ostream& operator << (ostream& os, AStudentManager& manager);
};


