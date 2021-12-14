#pragma once
#include <iostream>
class AFileIO
{
public:
	// 파일 생성, 파일 삭제, 파일 출력, 파일 로드
	FILE* m_pStream = nullptr;
public:
	bool CreateFile(const char* pFName);
	bool OpenFile(const char* pFName);
	void CloseFile();
	size_t Write(const void* pData, int iSize);
	size_t Read(void* pData, int iSize);

};

