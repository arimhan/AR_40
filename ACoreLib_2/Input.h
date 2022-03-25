#pragma once
#include "Std.h"

enum KeyState
{
	KEY_FREE = 0,
	KEY_UP,
	KEY_PUSH,
	KEY_HOLD,
};
class AInput
{
public:
	float	m_fRadianX = 0.0f;
	float	m_fRadianY = 0.0f;
	
	//마우스 드래그, 클릭기능 추가
	bool	m_bDrag = false;
	POINT	m_ptMouseClick;
	POINT	m_ptDeltaMouse;
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
	DWORD   GetKey(DWORD dwKey);
	T::TVector2	GetDelta();
private:
	AInput();
public:
	virtual ~AInput();
};

