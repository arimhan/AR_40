#include "Sample.h"

//GAME_RUN(Window, 1024, 768)
// ;��  error C2429: ��� ��� 'if/switch�� init-statements'�� �����Ϸ� �÷��� '/std:c++17'��(��) �ʿ��մϴ�. �� ���� ���� ��µ�

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample core;

    if (core.WinRegisterClass(hInstance) == FALSE) return 1;
    if (core.SetWindow(L"Set Window_1 Sample") == FALSE) return 1;
    core.WinRun();
    return 1;
}
