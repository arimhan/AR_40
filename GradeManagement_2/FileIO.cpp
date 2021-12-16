#include "FileIO.h"

//bool AFileIO::CreateFile(const char* pFileName)
//{
//    if (m_pStream != nullptr) return false;
//    int iError = fopen_s(&m_pStream, pFileName, "wb");
//    if (m_pStream == nullptr) return false;
//    return true;
//}
//bool AFileIO::OpenFile(const char* pFileName)
//{
//    if (m_pStream != nullptr) return false;
//    int iError = fopen_s(&m_pStream, pFileName, "rb");
//    if (m_pStream == nullptr) return false;
//    return true;
//}
//void AFileIO::CloseFile()
//{
//    fclose(m_pStream);
//    m_pStream = nullptr;
//}
//size_t AFileIO::Write(void const* pData, int iSize)
//{
//    if (m_pStream == nullptr) return -1;
//    size_t size = fwrite(pData, iSize, 1, m_pStream);
//    return size;
//}
//size_t AFileIO::Read(void* pData, int iSize)
//{
//    if (m_pStream == nullptr) return -1;
//    size_t size = fread(pData, iSize, 1, m_pStream);
//    return size;
//}
template <class R>
bool AFileIO<R>::SaveFile(const char* pFileName)
{
    return false;
}
template <class R>
bool AFileIO<R>::LoadFile(const char* pFileName)
{
    return false;
}
