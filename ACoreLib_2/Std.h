#pragma once
#include <winsock2.h>
#include <windows.h>
#include <d3d11.h>
#include <dxgidebug.h>
#include <tchar.h>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <atlconv.h> // A2W
#include "Collision.h"
#include <wrl.h> 
//3D
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>
#include "AMath.h"


//#define Tex_Size		6
//#define Plane_Size	6
//#define Frustum_Size	8

class ABoxObj;
using namespace Microsoft::WRL;


#pragma comment	(lib, "d3d11.lib")
#ifdef _DEBUG
#pragma comment	(lib, "ACoreLib_2_d.lib")
#else
#pragma comment	(lib, "ACoreLib_2_r.lib")
#endif
#pragma comment	(lib, "ws2_32.lib")
using namespace std;

//3D
#define ABASIS_EPSILON	((FLOAT) 0.001f)
#define ABASIS_PI		((FLOAT) 3.141592654f)
#define DegreeToRadian(degree)((degree)*(ABASIS_PI/180.0f))
#define RadianToDegree(radian)((radian)*(180.0f/ABASIS_PI))


//랜덤
#define randf(x) (x*rand()/(float)RAND_MAX)
#define randf2(x,off) (off+x*rand()/(float)RAND_MAX)
#define randstep(fMin,fMax) (fMin+((float)fMax-(float)fMin)*rand()/(float)RAND_MAX)
#define clamp(x,MinX,MaxX) if (x>MaxX) x=MaxX; else if (x<MinX) x=MinX;

extern RECT			g_rtClient;
extern HWND			g_hWnd;
extern float		g_fSecPerFrame;
extern float		g_fGameTimer;
extern POINT		g_ptMouse;
extern ABoxObj*		g_pBoxDebug;

static std::wstring to_mw(const std::string& _src)
{
	USES_CONVERSION;
	return std::wstring(A2W(_src.c_str()));
};

static std::string to_wm(const std::wstring& _src)
{
	USES_CONVERSION;
	return std::string(W2A(_src.c_str()));
};

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

static void DisplayText(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	char buf[1024 + 256] = { 0, };
	vsprintf_s(buf, fmt, arg);
	OutputDebugStringA((char*)buf);
	va_end(arg);
}
static void MemoryReporting()
{
#if defined(DEBUG) | defined(_DEBUG)
	HMODULE dxgidebugdll = GetModuleHandleW(L"dxgidebug.dll");
	decltype(&DXGIGetDebugInterface) GetDebugInterface = reinterpret_cast<decltype(&DXGIGetDebugInterface)>(GetProcAddress(dxgidebugdll, "DXGIGetDebugInterface"));
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