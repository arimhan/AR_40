#include "Sample.h"

//GAME_RUN(Window, 1024, 768)
// ;랑  error C2429: 언어 기능 'if/switch의 init-statements'에 컴파일러 플래그 '/std:c++17'이(가) 필요합니다. 등 여러 에러 출력됨

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    Sample core;

    if (core.WinRegisterClass(hInstance) == FALSE) return 1;
    if (core.SetWindow(L"Set Window_1 Sample") == FALSE) return 1;
    core.WinRun();
    return 1;
}
