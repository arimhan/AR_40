#pragma once
#include "Std.h"
class AWindow
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	RECT		m_rtClient;
	RECT		m_rtWindow;
public:
	BOOL SetWinClass(HINSTANCE	hInstance);
	BOOL SetWindow(const WCHAR* szTitle = L"ArimHan 3D Sample",
					int iWidth = 600, int iHeight = 400); //여기서 세팅한 값이 적용됨
	bool WinRun();
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void	ResizeDevice(UINT iWidth, UINT iHeight); //재정의 할거니까

	AWindow();
	virtual~AWindow();
};