#pragma once
#include "World.h"
#include "PlayerObj2D.h"
#include "ObjectNPC2D.h"
#include "SoundMgr.h"

class AZoneWorld : public AWorld
{
public:
	APlayerObj2D	m_PlayerObj;
	ASound*			m_pBackGroundMusic;


public:
	bool			Load(wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

