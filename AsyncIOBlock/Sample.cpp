#include <iostream>
//#include <WinSock2.h>
#include <Windows.h>
//#pragma comment (lib, "ws2_32.lib")
using namespace std;

//비동기 -> 블럭단위로 읽고 쓰도록 하기
//ex) 10MB씩 읽고 쓰고를 끝까지 반복 , 근데 비동기라 순서가 보장되지 X
//버퍼를 여러개 만들어 전체 읽는 버퍼, 나눠 읽는 버퍼(10% 뒤에 10% 붙이기 = 버퍼 내 offset가 왔다갔다함)
//쓰기는 나눠 읽는 버퍼에서 필요한 만큼 불러옴


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
        NULL); //버퍼링XX

    if (hFileAsync == INVALID_HANDLE_VALUE) { return; }

    HANDLE hFileCopy = CreateFile(L"TESTCOPY.zip",
        GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL); //버퍼링XX
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

        //비동기 로드
        g_ReadOV.Offset = i * BlockSize;
        g_ReadOV.OffsetHigh = 0;
        BOOL Ret = ReadFile(hFileAsync, g_buffer, BlockSize, &dwRead, &g_ReadOV);
        BOOL bReturn = GetOverlappedResult(hFileAsync, &g_ReadOV, &dwRead, TRUE);

        //비동기 출력
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