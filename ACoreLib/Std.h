#pragma once
#include <winsock2.h>
#include <windows.h>
#include <d3d11.h>
#include <dxgidebug.h> //debug
#include <queue>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <iostream>
#include <atlconv.h> //a2w
#include <tchar.h>
#include <string>
#include "Collision.h"
#include <wrl.h>					//ComPtr
using namespace Microsoft::WRL;		//ComPtr

#pragma comment (lib, "d3d11.lib")
#ifdef _DEBUG
#pragma comment (lib, "ACoreLib_d.lib")
#else
#pragma comment (lib, "ACoreLib_r.lib")
#endif
#pragma comment (lib, "ws2_32.lib")
using namespace std;


extern RECT		g_rtClient;
extern HWND		g_hWnd;
//모든곳에서 접근하기 위해 extern 처리한다.
extern float	g_fSecPerFrame;
extern float	g_fGameTimer;
extern POINT	g_ptMouse;

template<class T>
class ASingleton
{
public:
	static T& Get()
	{
		static T theSingle;
		return theSingle;
	}
};

//string <-> wstirng 변환 함수
static wstring to_mw(const string& _src)
{
	USES_CONVERSION;
	return wstring(A2W(_src.c_str()));
}
static string to_mw(const wstring& _src)
{
	USES_CONVERSION;
	return string(W2A(_src.c_str()));
}

static void DisplayText(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	char buf[1024 + 256] = { 0, };
	vsprintf_s(buf, fmt, arg);
	OutputDebugStringA((char*)buf);
	va_end(arg);
}


//멀까
static void MemoryReporting()
{
#if defined(DEBUG) | defined(_DEBUG)
	HMODULE dxgidebugdll = GetModuleHandleW(L"dxgidebug.dll");
	decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast
 <decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgidebugdll, "DXGIGetDebugInterface"));
	IDXGIDebug* debug;
	GetDebugInterface(IID_PPV_ARGS(&debug));
	OutputDebugStringW(L"Starting Live Direct3D Object Dump:\r\n");
	debug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_ALL);
	OutputDebugStringW(L"Completed Live Direct3D Object Dump.\r\n");
	debug->Release();
#endif
}


#define GAME_START int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow){ASample core;
#define GAME_WIN(s,x,y) if (core.SetWinClass(hInstance) == FALSE) return 1; if (core.SetWindow(L#s, x, y) == FALSE) return 1;core.GameRun();return 1;}
#define GAME_RUN(s,x,y) GAME_START; GAME_WIN(s,x,y);
#define SIMPLE_WIN() if (core.SetWinClass(hInstance) == FALSE) return 1; if (core.SetWindow() == FALSE) return 1; core.GameRun(); return 1;}
#define SIMPLE_ARUN() GAME_START; SIMPLE_WIN();
#define BEGIN_START(S) friend class ASingleton<S>

////GAMERUN은 TITLE, 사이즈 지정
////SIMPLERUN은 디폴트값으로 실행