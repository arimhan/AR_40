#pragma once
#include "Student.h"

template <class R>
class AFileIO
{
public:

	ALinkedList<AStudent> m_List;

	bool SaveFile(const char* pFileName);
	bool LoadFile(const char* pFileName);

	/*
	FILE* m_pStream = nullptr;
	// ���� ���� => ���̳ʸ�
	// ���� ����
	// ���� ���
	// ���� �ε�
	bool CreateFile(const char* pFileName);
	bool OpenFile(const char* pFileName);
	void CloseFile();
	size_t Write(void const* pData, int iSize);
	size_t Read(void* pData, int iSize);*/
};

