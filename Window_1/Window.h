#pragma once
#include <Windows.h>
class AWindow
{
public:
	//����������
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	UINT m_iWindowWidth;
	UINT m_iWindowHeight;

	//������ ����
	bool InitWindow();
	//������ ��ġ����

	AWindow() {}
	~AWindow() {}
};