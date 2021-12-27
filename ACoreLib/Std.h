#pragma once
#include <windows.h>
#include <vector>
#include <list>
#include <d3d11.h>
#pragma comment (lib, "ACoreLib")
#pragma comment (lib, "d3d11.lib")
using namespace std;

//#define GAME_START int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) { Sample core;
//#define GAME_WIN(s,x,y) if (core.WinRegisterClass(hInstance) == FALSE) return 1; if (core.SetWindow(core.SetWindow(L#s, x, y) == FALSE) return 1; core.GameRun(); return 1;}
//#define SIMPLE_WIN() if (core.WinRegisterClass(hInstance) == FALSE) return 1; if (core.SetWindow() == FALSE) return 1; core.GameRun(); return 1;}
//#define GAME_RUN(s,x,y) GAME_START; GAME_WIN(s,x,y);
//#define SIMPLE_RUN() GAME_START; SIMPLE_WIN();
////GAMERUN은 TITLE, 사이즈 지정
////SIMPLERUN은 디폴트값으로 실행
