#include <iostream>
//#include <WinSock2.h>
#include <Windows.h>
//#pragma comment (lib, "ws2_32.lib")
using namespace std;

//�񵿱� -> �������� �а� ������ �ϱ�
//ex) 10MB�� �а� ���� ������ �ݺ� , �ٵ� �񵿱�� ������ ������� X
//���۸� ������ ����� ��ü �д� ����, ���� �д� ����(10% �ڿ� 10% ���̱� = ���� �� offset�� �Դٰ�����)
//����� ���� �д� ���ۿ��� �ʿ��� ��ŭ �ҷ���


void main()
{
    setlocale(LC_ALL, "");//"KOREAN");
    WCHAR* g_buffer = NULL;
    LARGE_INTEGER filesize;
    OVERLAPPED  g_ReadOV = { 0, };
    OVERLAPPED  g_WriteOV = { 0, };
    HANDLE hFileAsync = CreateFile(L"TESTZIP.zip",
        GENERIC_READ | GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL); //���۸�XX

    if (hFileAsync == INVALID_HANDLE_VALUE) { return; }

    HANDLE hFileCopy = CreateFile(L"TESTCOPY.zip",
        GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL); //���۸�XX
    if (hFileCopy == INVALID_HANDLE_VALUE) 
    {
        CloseHandle(hFileAsync);
        return; 
    }

    GetFileSizeEx(hFileAsync, &filesize);

    DWORD dwRead = 0;
    DWORD dwTotalWrite = 0;
    //DWORD dwWritten;
    WCHAR BlockSize = 2048;
    g_buffer = new WCHAR[BlockSize];
    for (int i = 0; ;i++)
    {
        ZeroMemory(g_buffer, BlockSize);

        //�񵿱� �ε�
        g_ReadOV.Offset = i * BlockSize;
        g_ReadOV.OffsetHigh = 0;
        BOOL Ret = ReadFile(hFileAsync, g_buffer, BlockSize, &dwRead, &g_ReadOV);
        BOOL bReturn = GetOverlappedResult(hFileAsync, &g_ReadOV, &dwRead, TRUE);

        //�񵿱� ���
        g_WriteOV.Offset = i * BlockSize;
        g_WriteOV.OffsetHigh = 0;
        DWORD dwWritten;
        Ret = WriteFile(hFileCopy, g_buffer, dwRead, &dwWritten, &g_WriteOV);
        bReturn = GetOverlappedResult(hFileCopy, &g_ReadOV, &dwWritten, TRUE);
        dwTotalWrite += dwWritten;

        if (filesize.LowPart == dwTotalWrite) { break; }
    }
    CloseHandle(hFileAsync);
    CloseHandle(hFileCopy);


}