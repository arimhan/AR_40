#pragma once
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
class ATimer
{
public:
	float m_fSecondPerFrame;
	float m_fTimer;
	DWORD m_dwBeforeTime;

	//float m_fSecPerFrame = 0.0f;
	//float m_fGameTimer = 0.0f;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
};

