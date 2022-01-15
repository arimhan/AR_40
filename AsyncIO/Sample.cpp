#include <iostream>
#include <Windows.h>
using namespace std;

DWORD BytesPerSector;

DWORD SectorsPerCluster;
DWORD NumberOfFreeClusters;
DWORD TotalNumberOfClusters;

//동기 , 비동기 
//파일입출력 => C++
void main()
{
    WCHAR lpRootPathName[] = L"d:\\";
    GetDiskFreeSpace(lpRootPathName, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters);

    setlocale(LC_ALL, "");//"KOREAN");
    
    //"KOREAN"); =>""해당 지역의 언어를 따름. "" <모든 컴퓨터, "언어"
    {
    // --------------비동기 사용XXX-------------------
        //파일 생성 , 전부 유니코드 (W)
        HANDLE hFile = CreateFile(L"test.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != NULL) //파일포인터 오류여부 처리
        {
            //all 2byte
            WCHAR buffer[] = L"test string";
            DWORD dwLength = sizeof(buffer);
            DWORD dwWritten; //return값 (사용한 size)
            //얼만큼 썼는지, 성공여부 반환값이 발생 => BOOL 타입 지정
            BOOL ret = WriteFile(hFile, buffer, dwLength,& dwWritten, NULL);
            // LPCVOID lpBuffer 버퍼 시작 주소 nNumberOfBytesToWrite 이 주소부터 , ~ LPDWORD lpNumberOfBytesWritten 이 주소까지
            // LPOVERLAPPED lpOverlapped 비동기 처리 (null = 사용X)
            if (ret == TRUE)
            {
                //유니코드 -> wcout 사용, 한글 출력X =>상단에  setlocale(LC_ALL, "") 처리를 하면 정상출력된다.
                wcout << "Create Succese" << endl;
                //wcout << "성공!" << endl;;
            }
        }
        CloseHandle(hFile);
        //파일 생성 , 전부 유니코드 (W)
        HANDLE hReadFile = CreateFile(L"test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hReadFile != NULL) //파일포인터 오류여부 처리
        {
            WCHAR buffer[512] = { 0, };
            DWORD dwLength = sizeof(buffer);
            DWORD dwRead; //return값 (사용한 size)
            //얼만큼 썼는지, 성공여부 반환값이 발생 => BOOL 타입 지정
            BOOL ret = ReadFile(hReadFile, buffer, dwLength, &dwRead, NULL);
            if (ret == TRUE)
            {
                wcout << buffer << endl;
            }
        }
        CloseHandle(hReadFile);
    }

    WCHAR* g_buffer = NULL;
    LARGE_INTEGER filesize; //longlong (8byte)
    OVERLAPPED  g_ReadOV = { 0, };
    OVERLAPPED  g_WriteOV = { 0, };
    {
        HANDLE hFileAsync = CreateFile(L"TESTZIP.zip", 
            GENERIC_READ | GENERIC_WRITE, 0, NULL, 
            OPEN_EXISTING, 
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,
            NULL);

        if (hFileAsync != INVALID_HANDLE_VALUE) // handle값 error체크
        {
            GetFileSizeEx(hFileAsync, &filesize);
            //LARGE_INTEGER(longlong)에 의해 확장버전 사용
            DWORD dwSize = 0;
            if (filesize.QuadPart % BytesPerSector != 0)
            {
                dwSize = filesize.QuadPart / BytesPerSector;
                dwSize = (dwSize + 1) * BytesPerSector;
            }
            g_buffer = new WCHAR[filesize.QuadPart];
            DWORD dwRead;
            DWORD dwWritten;
            BOOL Ret = ReadFile(hFileAsync, g_buffer, dwSize, &dwRead, &g_ReadOV);
            BOOL bPanding = FALSE; //대기 여부 판단 (로드, 출력 대기 시에만 TRUE)
            if (Ret == FALSE)
            {
                if (GetLastError() == ERROR_IO_PENDING)
                {
                    wcout << L"로드중 . . ." << endl;
                    bPanding = TRUE;
                }
                else
                {
                    wcout << L"로드 실패!!" << endl;
                    bPanding = FALSE;
                }
            }
            else
            {
                wcout << L"로드완료" << endl;
            }

            // 로드 중일 경우 처리
            DWORD dwTrans = 0;
            BOOL bReturn;
            while (bPanding) //bPanding동안 반복하도록 처리
            {
                bReturn = GetOverlappedResult(hFileAsync, &g_ReadOV, &dwTrans, FALSE);
                if (bReturn == TRUE)
                {
                    wcout << L"로드 완료!";
                    bPanding = FALSE;
                    //로드완
                }
                else
                {
                    if (GetLastError() == ERROR_IO_INCOMPLETE) { wcout << L"."; } //로딩중이니 ... 출력되도록 ~~
                    //실패체크
                    else
                    {
                        wcout << L"로드 실패!" << endl;
                        bPanding = FALSE;
                    }
                }
                Sleep(1000);
            }
        }
        CloseHandle(hFileAsync);
        wcout << L"\n복사 시작";

        HANDLE hFileWriteAsync = CreateFile(L"TESTCOPY.zip", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_WRITE_THROUGH, NULL);
        if (hFileWriteAsync != NULL)
        {
            DWORD dwLenght = filesize.QuadPart;
            DWORD dwWritten;
            BOOL Ret = WriteFile(hFileWriteAsync, g_buffer, dwLenght, &dwWritten, &g_WriteOV);
            BOOL bPanding = FALSE; //대기 여부 판단 (로드, 출력 대기 시에만 TRUE)

            if (Ret == FALSE)
            {
                if (GetLastError() == ERROR_IO_PENDING)
                {
                    wcout << L"\n출력중 . . ." << endl;
                    bPanding = TRUE;
                }
                else
                {
                    wcout << L"출력 실패!!" << endl;
                }
            }
            else
            {
                wcout << L"출력 완료!";
                bPanding = FALSE;
            }
            // 로드 중일 경우 처리
            DWORD dwTrans = 0;
            BOOL bReturn;
            while (bPanding) //bPanding동안 반복하도록 처리
            {
                bReturn = GetOverlappedResult(hFileWriteAsync, &g_WriteOV, &dwTrans, FALSE);
                if (bReturn == TRUE)
                {
                    wcout << L"출력 완료!";
                    bPanding = FALSE;
                    //로드완
                }
                else
                {
                    if (GetLastError() == ERROR_IO_INCOMPLETE) { wcout << L"."; } //로딩중이니 ... 출력되도록 ~~
                    //실패체크
                    else
                    {
                        wcout << L"출력 실패!" << endl;
                        bPanding = FALSE;
                    }
                    Sleep(1000);
                }
            }
        }
        CloseHandle(hFileWriteAsync);
    }
}

    
