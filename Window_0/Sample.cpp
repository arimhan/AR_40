#include <Windows.h>

//�޽��� ��� ó��
//�ü�� -> �޽��� ���� -> �޽��� ť ���� ->WndProc ȣ��
//������ ���ν��� : �������� ���� �޽��� ó�� �Լ�(��ƾ)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//WinMain �տ� w - �����ڵ� ���
{
    //1. ������ Ŭ���� ���(�ü��)
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW; //���μ��� �ѷ���
    wc.lpfnWndProc = WndProc; //������ �Լ� -> �Լ� �ּ� �Ѱ���
    wc.hInstance = hInstance;
    //wc.hCursor= ;
    //wc.hbrBackground = ;
    wc.lpszClassName = L"Class Name";//������ ��Ʈ�� (lp : ������, sz: ��Ʈ��) , �ü�� ��� => ����
    if (RegisterClass(&wc) == false)
    {
        return 0;
    }
    //2. ������ ����
    HWND hWnd = CreateWindow(
        L"Class Name",
        L"Title Name",
        WS_OVERLAPPEDWINDOW,
        500, 300,//������ �������� X,Y
        800, 500, //������ ũ��
        NULL,
        NULL,
        hInstance,
        NULL);
    if (hWnd == NULL)
    {
        return 0;
    }
    ShowWindow(hWnd, SW_SHOW);

    MSG msg;
    //�⺻ �޽��� ����
    while(1)
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
    //A : ��Ƽ����Ʈ VER
    //W : �����ڵ� VER
        //MessageBox(
        //    NULL,
        //    L"211224_WINDOW_SAMPLE", //���� , STRING L
        //    L"WIN SAMPLE TEST", //TITLE
        //    MB_OK);
    return 1;
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) //�޽������� WndProc ó��
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam); //�Է¹��� �� �״�� ����
}
