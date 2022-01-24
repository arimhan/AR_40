#pragma once
#include "Std.h"
class AWindow
{
public:
	//전역변수들
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	RECT		m_rtClient;
	RECT		m_rtWindow;
public:
	BOOL SetWinClass(HINSTANCE	hInstance);
	BOOL SetWindow(const WCHAR* szTitle = L"Sample", int iWidth = 600, int iHeight = 400); //여기서 세팅한 값이 적용됨
	bool WinRun();
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	AWindow();
	virtual~AWindow();
};