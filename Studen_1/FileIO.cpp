#include "FileIO.h"
//���� ����, �ҷ����� ����ó�� �ʿ�

bool AFileIO::CreateFile(const char* pFName) 
{
	fopen_s(&m_pStream, pFName, "wb");
}
bool AFileIO::OpenFile(const char* pFName) 
{
	fopen_s(&m_pStream, pFName, "rb");
}
void AFileIO::CloseFile()
{
	fclose(m_pStream);
	m_pStream = nullptr;
}
size_t AFileIO::Write(const void* pData, int iSize) 
{
	size_t size = fwrite(pData, iSize, 1, m_pStream);
}
size_t AFileIO::Read(void* pData, int iSize) 
{
	size_t size = fread(pData, iSize, 1, m_pStream);
}