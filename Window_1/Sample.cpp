#include "Window.h"
#include <Windows.h>


//WinMain �տ� w - �����ڵ� ���
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    AWindow win;
    if (win.WinRegisterClass(hInstance) == FALSE) return 1;
    if (win.SetWindow(L"Set Window_1 Sample") == FALSE) return 1;
        win.WinRun();
    return 1;
}
