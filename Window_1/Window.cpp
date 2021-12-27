#include "Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) //메시지마다 WndProc 처리
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam); //입력받은 값 그대로 리턴
        }
    return 0;
}
BOOL AWindow::WinRegisterClass(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    //1. 윈도우 클래스 등록(운영체제)
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW; //가로세로 뿌려라
    wc.lpfnWndProc = WndProc; //포인터 함수 -> 함수 주소 넘겨줘
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Class Name";//포인터 스트링 (lp : 포인터, sz: 스트링) , 운영체제 등록 => 재사용
    if (RegisterClass(&wc) == false)
    {
        return FALSE;
    }
    return TRUE;
}
BOOL AWindow::SetWindow(const WCHAR* szTitle, int iClientWidth, int iClientHeight)
{
    RECT rt = {0,0 ,iClientWidth, iClientHeight }; //시작 좌표 (0,0)
    //2. 윈도우 생성
    HWND hWnd = CreateWindow(
        L"Class Name",
        szTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0,//윈도우 시작지점 X,Y 위에 RECT에서 세팅해둠
        rt.right-rt.left,
        rt.bottom-rt.top, //윈도우 크기 오-왼 = 1024 , 아래-위 = 768 이 나오도록 계산
        NULL,
        NULL,
        m_hInstance,
        NULL);
    if (hWnd == NULL)
    {
        return FALSE;
    }
    GetClientRect(m_hWnd, &m_rtClient);
    GetWindowRect(m_hWnd, &m_rtWindow);

    ShowWindow(hWnd, SW_SHOW);
    return TRUE;
}
bool AWindow::WinRun()
{
    MSG msg;
    //기본 메시지 루프
    while (1)
    {
        //메시지큐에 메시지가 없으면 블록처리
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg); //메시지 번역
            DispatchMessage(&msg); // 윈도우프로시져 호출ㄴ
        }
        else
        {
            //게임로직 호출
            static int count = 0;
            count++;
        }
    }
    return false;
}

//A : 멀티바이트 VER
//W : 유니코드 VER
    //MessageBox(
    //    NULL,
    //    L"211224_WINDOW_SAMPLE", //내용 , STRING L
    //    L"WIN SAMPLE TEST", //TITLE
    //    MB_OK);