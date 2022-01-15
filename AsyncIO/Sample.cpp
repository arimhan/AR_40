#include <iostream>
#include <Windows.h>
using namespace std;

DWORD BytesPerSector;

DWORD SectorsPerCluster;
DWORD NumberOfFreeClusters;
DWORD TotalNumberOfClusters;

//���� , �񵿱� 
//��������� => C++
void main()
{
    WCHAR lpRootPathName[] = L"d:\\";
    GetDiskFreeSpace(lpRootPathName, &SectorsPerCluster, &BytesPerSector, &NumberOfFreeClusters, &TotalNumberOfClusters);

    setlocale(LC_ALL, "");//"KOREAN");
    
    //"KOREAN"); =>""�ش� ������ �� ����. "" <��� ��ǻ��, "���"
    {
    // --------------�񵿱� ���XXX-------------------
        //���� ���� , ���� �����ڵ� (W)
        HANDLE hFile = CreateFile(L"test.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile != NULL) //���������� �������� ó��
        {
            //all 2byte
            WCHAR buffer[] = L"test string";
            DWORD dwLength = sizeof(buffer);
            DWORD dwWritten; //return�� (����� size)
            //��ŭ �����, �������� ��ȯ���� �߻� => BOOL Ÿ�� ����
            BOOL ret = WriteFile(hFile, buffer, dwLength,& dwWritten, NULL);
            // LPCVOID lpBuffer ���� ���� �ּ� nNumberOfBytesToWrite �� �ּҺ��� , ~ LPDWORD lpNumberOfBytesWritten �� �ּұ���
            // LPOVERLAPPED lpOverlapped �񵿱� ó�� (null = ���X)
            if (ret == TRUE)
            {
                //�����ڵ� -> wcout ���, �ѱ� ���X =>��ܿ�  setlocale(LC_ALL, "") ó���� �ϸ� ������µȴ�.
                wcout << "Create Succese" << endl;
                //wcout << "����!" << endl;;
            }
        }
        CloseHandle(hFile);
        //���� ���� , ���� �����ڵ� (W)
        HANDLE hReadFile = CreateFile(L"test.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hReadFile != NULL) //���������� �������� ó��
        {
            WCHAR buffer[512] = { 0, };
            DWORD dwLength = sizeof(buffer);
            DWORD dwRead; //return�� (����� size)
            //��ŭ �����, �������� ��ȯ���� �߻� => BOOL Ÿ�� ����
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

        if (hFileAsync != INVALID_HANDLE_VALUE) // handle�� errorüũ
        {
            GetFileSizeEx(hFileAsync, &filesize);
            //LARGE_INTEGER(longlong)�� ���� Ȯ����� ���
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
            BOOL bPanding = FALSE; //��� ���� �Ǵ� (�ε�, ��� ��� �ÿ��� TRUE)
            if (Ret == FALSE)
            {
                if (GetLastError() == ERROR_IO_PENDING)
                {
                    wcout << L"�ε��� . . ." << endl;
                    bPanding = TRUE;
                }
                else
                {
                    wcout << L"�ε� ����!!" << endl;
                    bPanding = FALSE;
                }
            }
            else
            {
                wcout << L"�ε�Ϸ�" << endl;
            }

            // �ε� ���� ��� ó��
            DWORD dwTrans = 0;
            BOOL bReturn;
            while (bPanding) //bPanding���� �ݺ��ϵ��� ó��
            {
                bReturn = GetOverlappedResult(hFileAsync, &g_ReadOV, &dwTrans, FALSE);
                if (bReturn == TRUE)
                {
                    wcout << L"�ε� �Ϸ�!";
                    bPanding = FALSE;
                    //�ε��
                }
                else
                {
                    if (GetLastError() == ERROR_IO_INCOMPLETE) { wcout << L"."; } //�ε����̴� ... ��µǵ��� ~~
                    //����üũ
                    else
                    {
                        wcout << L"�ε� ����!" << endl;
                        bPanding = FALSE;
                    }
                }
                Sleep(1000);
            }
        }
        CloseHandle(hFileAsync);
        wcout << L"\n���� ����";

        HANDLE hFileWriteAsync = CreateFile(L"TESTCOPY.zip", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED | FILE_FLAG_WRITE_THROUGH, NULL);
        if (hFileWriteAsync != NULL)
        {
            DWORD dwLenght = filesize.QuadPart;
            DWORD dwWritten;
            BOOL Ret = WriteFile(hFileWriteAsync, g_buffer, dwLenght, &dwWritten, &g_WriteOV);
            BOOL bPanding = FALSE; //��� ���� �Ǵ� (�ε�, ��� ��� �ÿ��� TRUE)

            if (Ret == FALSE)
            {
                if (GetLastError() == ERROR_IO_PENDING)
                {
                    wcout << L"\n����� . . ." << endl;
                    bPanding = TRUE;
                }
                else
                {
                    wcout << L"��� ����!!" << endl;
                }
            }
            else
            {
                wcout << L"��� �Ϸ�!";
                bPanding = FALSE;
            }
            // �ε� ���� ��� ó��
            DWORD dwTrans = 0;
            BOOL bReturn;
            while (bPanding) //bPanding���� �ݺ��ϵ��� ó��
            {
                bReturn = GetOverlappedResult(hFileWriteAsync, &g_WriteOV, &dwTrans, FALSE);
                if (bReturn == TRUE)
                {
                    wcout << L"��� �Ϸ�!";
                    bPanding = FALSE;
                    //�ε��
                }
                else
                {
                    if (GetLastError() == ERROR_IO_INCOMPLETE) { wcout << L"."; } //�ε����̴� ... ��µǵ��� ~~
                    //����üũ
                    else
                    {
                        wcout << L"��� ����!" << endl;
                        bPanding = FALSE;
                    }
                    Sleep(1000);
                }
            }
        }
        CloseHandle(hFileWriteAsync);
    }
}

    
