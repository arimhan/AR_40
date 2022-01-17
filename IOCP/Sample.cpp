#include <iostream>
#include <Windows.h>
#define MAX_WORKER_THREAD 3 //스레드 트리
#define BlockSize (4096*4096) //16777216
using namespace std;

//IOCP 파일 입출력 => 통신으로 변환
//파일 입출력을 소켓으로 변경하면 통신에서 사용 가능

WCHAR* g_buffer = NULL;

LARGE_INTEGER filesize;
OVERLAPPED  g_ReadOV = { 0, };
OVERLAPPED  g_WriteOV = { 0, };

//비동기 작업 당 어레이는 따로 있어야 함
DWORD g_dwCurrentRead = 0;
DWORD g_dwCurrentWrite = 0;
OVERLAPPED  g_ReadOVArray[100];
OVERLAPPED  g_WriteOVArray[100]; //재활용 시스템 필요. Queue개념으로..

HANDLE g_hFileRead;
HANDLE g_hFileWrite;
HANDLE g_hWorkThread[MAX_WORKER_THREAD];

/***매우 중요!! 완료포트 관리 객체*/
HANDLE g_hIOCP;
LARGE_INTEGER g_LargeRead;
LARGE_INTEGER g_LargeWrite;
HANDLE g_hKillEvent;
//------------------------------------------------------------------

bool DispatchRead(DWORD dwTransfer, OVERLAPPED* pOverlapped)
{
    //읽은 부분 뒤에서부터 읽어~
    g_LargeRead.QuadPart += dwTransfer;
    ++g_dwCurrentWrite; //1번부터 출발
    g_WriteOVArray[g_dwCurrentWrite].Offset = g_LargeWrite.LowPart;
    g_WriteOVArray[g_dwCurrentWrite].OffsetHigh = g_LargeWrite.HighPart;

    DWORD dwWritten;

    BOOL Ret = WriteFile(g_hFileWrite, g_buffer, dwTransfer, &dwWritten, &g_WriteOVArray[g_dwCurrentWrite++]);

    if (Ret == FALSE)
    {
        if (GetLastError() != ERROR_IO_PENDING) //ERROR_IO_PENDING 은 정상
        {
            return false;
        }
        return true;
    }

    return true;
}
bool DispatchWrite(DWORD dwTransfer, OVERLAPPED* pOverlapped)
{
    g_LargeWrite.QuadPart += dwTransfer;

    g_LargeWrite.QuadPart += dwTransfer;
    ++g_dwCurrentRead; //1번부터 출발
    g_ReadOVArray[g_dwCurrentRead].Offset = g_LargeRead.LowPart;
    g_ReadOVArray[g_dwCurrentRead].OffsetHigh = g_LargeRead.HighPart;

    return true;
}

DWORD WINAPI WorkerThread(LPVOID lParam)
{
    DWORD dwTransfer;
    ULONG_PTR KeyValue; //완료시 반환하는 포트값 ex 1000 : Read..
    OVERLAPPED* pOverlapped;


    while(1)
    {
        if (WaitForSingleObject(g_hKillEvent, 1) == WAIT_OBJECT_0)
        {
            break;
        }
        
        //완료 큐에 데이터가 있으면 작업시작
        BOOL bReturn = ::GetQueuedCompletionStatus(g_hIOCP, &dwTransfer, &KeyValue, &pOverlapped,1);

        if (bReturn == TRUE)      //작업
        {
            if (KeyValue == 1000) // Read
            {
                if (!DispatchRead(dwTransfer, pOverlapped))
                {
                    ::SetEvent(g_hKillEvent);
                    break;
                }

            }
            if (KeyValue == 2000) // Write
            {
                if (!DispatchRead(dwTransfer, pOverlapped))
                {
                    ::SetEvent(g_hKillEvent);
                    break;
                }
            }
        }
        else
        {
            if (GetLastError() != WAIT_TIMEOUT)
            {
                ::SetEvent(g_hKillEvent);
                break;
            }
            //오류
        }
    }
    return 1;
}
void main()
{
    setlocale(LC_ALL, "");//"KOREAN");

    g_hFileRead = CreateFile(L"TESTZIP.zip",
        GENERIC_READ | GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL); //버퍼링XX

    if (g_hFileRead == INVALID_HANDLE_VALUE) { return; }

    g_hFileWrite = CreateFile(L"TESTCOPY.zip",
        GENERIC_WRITE, 0, NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
        NULL); //버퍼링XX
    if (g_hFileWrite == INVALID_HANDLE_VALUE)
    {
        CloseHandle(g_hFileRead);
        return;
    }

    GetFileSizeEx(g_hFileRead, &filesize);

    DWORD dwRead = 0;
    DWORD dwTotalWrite = 0;
   // WCHAR BlockSize = (4096*4096);
    g_buffer = new WCHAR[BlockSize];

    for (int iThread = 0; iThread < MAX_WORKER_THREAD; iThread++)
    {
        DWORD id;
        g_hWorkThread[iThread]=::CreateThread(0,0, WorkerThread, nullptr, 0, &id);
    }
    g_LargeRead.QuadPart = 0;
    g_LargeWrite.QuadPart = 0;

    //비동기입출력 작업결과 저장 큐 (1. 비동기 입출력 객체 생성 => Queue생성
    //객체 g_hIOCP에 파일포인터 Read, Write핸들이 연결(저장)된다
    g_hIOCP = ::CreateIoCompletionPort(
            INVALID_HANDLE_VALUE, 0, 0, 0);
    ::CreateIoCompletionPort(g_hFileRead, g_hIOCP, 1000,0); 
    //g_hIOCP이 객체에 파일포인터 g_hFileRead(읽는 핸들)을 등록한다. 완료포트는 1000번으로 넘긴다.
    ::CreateIoCompletionPort(g_hFileWrite, g_hIOCP, 2000, 0);

    //비동기 로드
    g_ReadOV.Offset = 0;
    g_WriteOV.OffsetHigh = 0;
    BOOL Ret = ReadFile(g_hFileRead, g_buffer, BlockSize, &dwRead, &g_ReadOV);
    
    WaitForMultipleObjects(MAX_WORKER_THREAD, g_hWorkThread, TRUE, INFINITE);

    for (int iThread = 0; iThread < MAX_WORKER_THREAD; iThread++)
    {
        CloseHandle(g_hWorkThread[iThread]);
    }
    CloseHandle(g_hIOCP);
}
