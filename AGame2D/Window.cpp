#include "Window.h"
RECT g_rtClient;
HWND g_hWnd;
AWindow* g_pWindow = nullptr;
//GameEngine���� ������ �����ϱ� ������ ���⼭�� ����� �ʿ����.

/*
LRESULT  CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
    switch (msg)
    {
    case WM_SIZE:
    {
        UINT iWidth = LOWORD(lParam);
        UINT iHeight = HIWORD(lParam);
        g_pWindow->ResizeDevice(iWidth, iHeight);
    }break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);// WM_QUIT
    }break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}*/
void AWindow::ResizeDevice(UINT iWidth, UINT iHeight){}
LRESULT AWindow::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return 0; }
/*
BOOL AWindow::SetWinClass(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    // 1, ������ Ŭ���� ���, �㰡(�ü��)
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"KGCA_Window";
    wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    if (RegisterClass(&wc) == false)
    {
        return FALSE;
    }

    return TRUE;
}*/

BOOL AWindow::SetWindow(const WCHAR* szTitle,
    int iClientWidth,
    int iClientHeight)
{
    RECT rt = { 0,0, iClientWidth , iClientHeight };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
    // 2, ������ ����
    m_hWnd = CreateWindow(
        L"KGCA_Window",
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
    g_rtClient = m_rtClient;

    ShowWindow(m_hWnd, SW_SHOW);
    return TRUE;
}

bool AWindow::WinRun()
{
    MSG msg;
    // �޼���ť�� �޼����� ������ ����
    while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            return false;
        }
        TranslateMessage(&msg);// �޼��� ����
        DispatchMessage(&msg);// ���������ν��� ȣ��
    }
    return true;
}

AWindow::AWindow()
{
    g_pWindow = this;
}
AWindow::~AWindow()
{}