#pragma once
#include <iostream>
class AFileIO
{
public:
	FILE* m_pStream = nullptr;
	// ���� ���� => ���̳ʸ�
	// ���� ����
	// ���� ��� 
	// ���� �ε�
	bool CreateFile(const char* pFileName);
	bool OpenFile(const char* pFileName);
	void CloseFile();
	size_t Write(void const* pData, int iSize);
	size_t Read(void* pData, int iSize);
};

