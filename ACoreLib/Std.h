#pragma once
#include <winsock2.h>
#include <windows.h>
#include <vector>
#include <list>
#include <d3d11.h>
#include "Collision.h"
#pragma comment (lib, "d3d11.lib")
#ifdef _DEBUG
#pragma comment (lib, "ACoreLib_d.lib")
#else
#pragma comment (lib, "ACoreLib_r.lib")
#endif
#pragma comment (lib, "ws2_32.lib")
using namespace std;

extern RECT g_rtClient;
extern HWND g_hWnd;
//모든곳에서 접근하기 위해 extern 처리한다.
extern float g_fSecPerFrame;
extern float g_fGameTimer;

#define GAME_START int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow){ASample core;
#define GAME_WIN(s,x,y) if (core.SetWinClass(hInstance) == FALSE) return 1; if (core.SetWindow(L#s, x, y) == FALSE) return 1;core.GameRun();return 1;}
#define GAME_RUN(s,x,y) GAME_START; GAME_WIN(s,x,y);
#define SIMPLE_WIN() if (core.SetWinClass(hInstance) == FALSE) return 1; if (core.SetWindow() == FALSE) return 1; core.GameRun(); return 1;}
#define SIMPLE_ARUN() GAME_START; SIMPLE_WIN();

////GAMERUN은 TITLE, 사이즈 지정
////SIMPLERUN은 디폴트값으로 실행
