#include "Window.h"
RECT g_rtClient;  //외부변수 선언하여 SetWindow시 변수 지정될 수 있도록 세팅
HWND g_hWnd; //채팅 클라이언트에서 사용되는 핸들값
AWindow* g_pWindow = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
    switch (msg) //메시지마다 WndProc 처리
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}
BOOL AWindow::SetWinClass(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Class Name";
    wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);//(GRAY_BRUSH);
    if (RegisterClass(&wc) == false)
    {
        return FALSE;
    }
    return TRUE;
}
BOOL AWindow::SetWindow(const WCHAR* szTitle, int iClientWidth, int iClientHeight)
{
    RECT rt = {0,0 ,iClientWidth, iClientHeight };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
    m_hWnd = CreateWindow(
        L"Class Name",
        szTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0,
        rt.right-rt.left,
        rt.bottom-rt.top,
        NULL,
        NULL,
        m_hInstance,
        NULL);
    if (m_hWnd == NULL)
    {
        return FALSE;
    }
    g_hWnd = m_hWnd;
    GetClientRect(m_hWnd, &m_rtClient);
    GetWindowRect(m_hWnd, &m_rtWindow);
    g_rtClient = m_rtClient; //외부변수 선언 , Client Size 800*600

    ShowWindow(m_hWnd, SW_SHOW);
    return TRUE;
}
bool AWindow::WinRun()
{
    MSG msg;
    //기본 메시지 루프
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT) { return false; }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}
LRESULT AWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return LRESULT();
}
AWindow::AWindow() { g_pWindow = this; }
AWindow::~AWindow(){}
