#pragma once
#include <Windows.h>
class AWindow
{
public:
	//����������
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	UINT		m_iWindowWidth;
	UINT		m_iWindowHeight;

	WORD MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE, int);
	//������ ����
	bool InitWindow();
	bool CreateWindows();
	bool WinRun();
	//������ ��ġ����

	AWindow() {}
	~AWindow() {}
};