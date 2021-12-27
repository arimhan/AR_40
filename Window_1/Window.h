#pragma once
#include <Windows.h>
class AWindow
{
public:
	//전역변수들
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	UINT		m_iWindowWidth;
	UINT		m_iWindowHeight;

	WORD MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE, int);
	//윈도우 생성
	bool InitWindow();
	bool CreateWindows();
	bool WinRun();
	//윈도우 위치조정

	AWindow() {}
	~AWindow() {}
};