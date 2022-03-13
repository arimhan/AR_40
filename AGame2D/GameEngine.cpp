#include "GameEngine.h"

AGameEngine* AGameEngine::m_pGameEngine = NULL;

LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return AGameEngine::GetEngine()->HandleEvent(hWindow, msg, wParam, lParam);
}

BOOL AGameEngine::Initialize(int iCmdShow)
{
    WNDCLASSEX    wndclass;

    // WINDOWÃ¢ »ý¼º
    ZeroMemory(&wndclass, sizeof(WNDCLASSEX));
    wndclass.cbSize = sizeof(wndclass);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    //wndclass.cbClsExtra = 0;
    //wndclass.cbWndExtra = 0;
    wndclass.hInstance = m_hInstance;
    //wndclass.hIcon = LoadIcon(m_hInstance, 0);
    //wndclass.hIconSm = LoadIcon(m_hInstance, 0);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);//(COLOR_WINDOW + 1);
    //wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = m_szWindowClass;

    if (!RegisterClassEx(&wndclass))
        return FALSE;

    int iWindowWidth = m_iWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
        iWindowHeight = m_iHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 +
        GetSystemMetrics(SM_CYCAPTION);
    if (wndclass.lpszMenuName != NULL)
        iWindowHeight += GetSystemMetrics(SM_CYMENU);
    int iXWindowPos = (GetSystemMetrics(SM_CXSCREEN) - iWindowWidth) / 2,
        iYWindowPos = (GetSystemMetrics(SM_CYSCREEN) - iWindowHeight) / 2;

    m_hWindow = CreateWindow(m_szWindowClass, m_szTitle, WS_POPUPWINDOW |
        WS_CAPTION | WS_MINIMIZEBOX, iXWindowPos, iYWindowPos, iWindowWidth,
        iWindowHeight, NULL, NULL, m_hInstance, NULL);

    if (!m_hWindow)
        return FALSE;
    ShowWindow(m_hWindow, iCmdShow);
    UpdateWindow(m_hWindow);

    return TRUE;
}

LRESULT AGameEngine::HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
        SetWindow(hWindow);
        timeGetTime();
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWindow, msg, wParam, lParam);
}

void AGameEngine::ErrorQuit(LPTSTR szErrorMsg)
{
    MessageBox(GetWindow(), szErrorMsg, TEXT("Error"), MB_OK | MB_ICONERROR);
    PostQuitMessage(0);
}

AGameEngine::AGameEngine(HINSTANCE hInstance, LPTSTR szWindowClass, LPTSTR szTitle, int iWidth, int iHeight)
{
    m_pGameEngine = this;
    m_hInstance = hInstance;
    m_hWindow = NULL;
    if (lstrlen(szWindowClass) > 0) lstrcpy(m_szWindowClass, szWindowClass);
    if (lstrlen(szTitle) > 0) lstrcpy(m_szTitle, szTitle);
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_iFrameDelay = 50;
    m_bSleep = TRUE;
}