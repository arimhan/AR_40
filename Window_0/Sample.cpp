#include <Windows.h>

//메시지 기반 처리
//운영체제 -> 메시지 전달 -> 메시지 큐 저장 ->WndProc 호출
//윈도우 프로시져 : 윈도우의 각종 메시지 처리 함수(루틴)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
//WinMain 앞에 w - 유니코드 명시
{
    //1. 윈도우 클래스 등록(운영체제)
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW; //가로세로 뿌려라
    wc.lpfnWndProc = WndProc; //포인터 함수 -> 함수 주소 넘겨줘
    wc.hInstance = hInstance;
    //wc.hCursor= ;
    //wc.hbrBackground = ;
    wc.lpszClassName = L"Class Name";//포인터 스트링 (lp : 포인터, sz: 스트링) , 운영체제 등록 => 재사용
    if (RegisterClass(&wc) == false)
    {
        return 0;
    }
    //2. 윈도우 생성
    HWND hWnd = CreateWindow(
        L"Class Name",
        L"Title Name",
        WS_OVERLAPPEDWINDOW,
        500, 300,//윈도우 시작지점 X,Y
        800, 500, //윈도우 크기
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
    //기본 메시지 루프
    while(1)
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
    //A : 멀티바이트 VER
    //W : 유니코드 VER
        //MessageBox(
        //    NULL,
        //    L"211224_WINDOW_SAMPLE", //내용 , STRING L
        //    L"WIN SAMPLE TEST", //TITLE
        //    MB_OK);
    return 1;
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) //메시지마다 WndProc 처리
    {
        case WM_DESTROY:
        {
            PostQuitMessage(0);
        }break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam); //입력받은 값 그대로 리턴
}
