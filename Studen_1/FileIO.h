#pragma once
#include <iostream>
class AFileIO
{
public:
	// ���� ����, ���� ����, ���� ���, ���� �ε�
	FILE* m_pStream = nullptr;
public:
	bool CreateFile(const char* pFName);
	bool OpenFile(const char* pFName);
	void CloseFile();
	size_t Write(const void* pData, int iSize);
	size_t Read(void* pData, int iSize);

};

