#pragma once
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
class ATimer
{
public:
	int		m_iFPS;
	float	m_fSecondPerFrame;
	float	m_fTimer;
	DWORD	m_dwBeforeTime;

	float	m_fFPSTimer = 0.0f;
	int		m_iFPSCounter = 0;
	//float m_fSecPerFrame = 0.0f;
	//float m_fGameTimer = 0.0f;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
};

