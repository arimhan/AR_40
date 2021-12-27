#include "Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) //�޽������� WndProc ó��
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam); //�Է¹��� �� �״�� ����
        }
    return 0;
}
BOOL AWindow::WinRegisterClass(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    //1. ������ Ŭ���� ���(�ü��)
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW; //���μ��� �ѷ���
    wc.lpfnWndProc = WndProc; //������ �Լ� -> �Լ� �ּ� �Ѱ���
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Class Name";//������ ��Ʈ�� (lp : ������, sz: ��Ʈ��) , �ü�� ��� => ����
    if (RegisterClass(&wc) == false)
    {
        return FALSE;
    }
    return TRUE;
}
BOOL AWindow::SetWindow(const WCHAR* szTitle, int iClientWidth, int iClientHeight)
{
    RECT rt = {0,0 ,iClientWidth, iClientHeight }; //���� ��ǥ (0,0)
    //2. ������ ����
    HWND hWnd = CreateWindow(
        L"Class Name",
        szTitle,
        WS_OVERLAPPEDWINDOW,
        0, 0,//������ �������� X,Y ���� RECT���� �����ص�
        rt.right-rt.left,
        rt.bottom-rt.top, //������ ũ�� ��-�� = 1024 , �Ʒ�-�� = 768 �� �������� ���
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
    //�⺻ �޽��� ����
    while (1)
    {
        //�޽���ť�� �޽����� ������ ���ó��
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&msg); //�޽��� ����
            DispatchMessage(&msg); // ���������ν��� ȣ�⤤
        }
        else
        {
            //���ӷ��� ȣ��
            static int count = 0;
            count++;
        }
    }
    return false;
}

//A : ��Ƽ����Ʈ VER
//W : �����ڵ� VER
    //MessageBox(
    //    NULL,
    //    L"211224_WINDOW_SAMPLE", //���� , STRING L
    //    L"WIN SAMPLE TEST", //TITLE
    //    MB_OK);