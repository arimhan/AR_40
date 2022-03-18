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
	BOOL SetWindow(const WCHAR* szTitle = L"",
					int iWidth = 600, int iHeight = 400); //���⼭ ������ ���� �����
	bool WinRun();
	virtual LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void	ResizeDevice(UINT iWidth, UINT iHeight); //������ �ҰŴϱ�

	AWindow();
	virtual~AWindow();
};