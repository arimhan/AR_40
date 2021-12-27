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
    GetClientRect(m_hWnd, &m_rtClient);
    GetWindowRect(m_hWnd, &m_rtWindow);

    ShowWindow(m_hWnd, SW_SHOW);
    return TRUE;
}
bool AWindow::WinRun()
{
    MSG msg;
    //기본 메시지 루프
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}