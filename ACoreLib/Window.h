#pragma once
#include "Std.h"
class AWindow
{
public:
	//����������
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	RECT		m_rtClient;
	RECT		m_rtWindow;
public:
	BOOL SetWinClass(HINSTANCE	hInstance);
	BOOL SetWindow(const WCHAR* szTitle = L"Sample", int iWidth = 800, int iHeight = 600); //���⼭ ������ ���� �����
	bool WinRun();
};