#pragma once
#include "World.h"
#include "PlayerObj2D.h"
#include "ObjectNpc2D.h"
#include "SoundMgr.h"
#include "Input.h"

class AZoneWorld :   public AWorld
{
public:
	APlayerObj2D		m_PlayerObj;
	AObject2D			m_TimerObj;
	ASound*				m_pBackGroundMusic;
public:
	bool	Load(std::wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};
