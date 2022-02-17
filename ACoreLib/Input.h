#pragma once
#include "Std.h"

enum KeyState { KEY_FREE = 0, KEY_UP, KEY_PUSH, KEY_HOLD, };

class AInput
{
public:
	DWORD m_dwKeyState[256];
	POINT m_ptMouse;
	DWORD m_dwMouseState[3];
	static AInput& Get()
	{
		static AInput theSingle;
		return theSingle;
	}
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	DWORD	GetKey(DWORD dwKey);
private:
	AInput();
public:
	virtual ~AInput();
};

