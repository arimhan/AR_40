#pragma once
//Device , window, 각종 STD관련 담당
#include <Windows.h>
#include <string>
#include <list>
#include <map>
#include "Timer.h"
#include "Window.h"

#include <iostream>
#include <memory>	//shared_ptr


using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,PSTR szCmdLine, int iCmdShow);
LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

class AGameEngine
{
protected:
	static AGameEngine* m_pGameEngine;
	HINSTANCE			m_hInstance;
	HWND				m_hWindow;
	TCHAR				m_szWindowClass[32];
	TCHAR				m_szTitle[32];
	int					m_iWidth, m_iHeight, m_iFrameDelay;
	BOOL				m_bSleep;
	HCURSOR				m_hcur;

public:
	AGameEngine(HINSTANCE hInstance, LPTSTR szWindowClass, LPTSTR szTitle, int iWidth, int iHeight);

	virtual ~AGameEngine() {};


public:
	static AGameEngine* GetEngine() { return m_pGameEngine; }
	BOOL				Initialize(int iCmdShow);
	LRESULT				HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
	void                ErrorQuit(LPTSTR szErrorMsg);

	HINSTANCE GetInstance() { return m_hInstance; };
	HWND      GetWindow() { return m_hWindow; };
	void      SetWindow(HWND hWindow) 
	{ 
		ATimer at;
		AWindow aw;
		at.m_fSecondPerFrame = 0.0f;
		at.m_fTimer = 0.0f;
		at.m_dwBeforeTime = timeGetTime();

		GetClientRect(aw.m_hWnd, &aw.m_rtClient);
		GetWindowRect(aw.m_hWnd, &aw.m_rtWindow);
		g_rtClient = aw.m_rtClient;

		m_hWindow = hWindow; 
	
	};
	LPTSTR    GetTitle() { return m_szTitle; };
	int       GetWidth() { return m_iWidth; };
	int       GetHeight() { return m_iHeight; };
	int       GetFrameDelay() { return m_iFrameDelay; };
	void      SetFrameRate(int iFrameRate) { m_iFrameDelay = 1000 / iFrameRate; };
	BOOL      GetSleep() { return m_bSleep; };
	void      SetSleep(BOOL bSleep) { m_bSleep = bSleep; };
};

