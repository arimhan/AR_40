#include "Window.h"
#include <Windows.h>


//WinMain 앞에 w - 유니코드 명시
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    AWindow win;
    if (win.WinRegisterClass(hInstance) == FALSE) return 1;
    if (win.SetWindow(L"Set Window_1 Sample") == FALSE) return 1;
        win.WinRun();
    return 1;
}
