#pragma once
#include "World.h"
#include "PlayerObj2D.h"
#include "ObjectNPC2D.h"
#include "Sound.h"
class AZoneWorld : public AWorld
{
public:
	APlayerObj2D	m_PlayerObj;
	ASound*			m_pBackGroundMusic;
	vector<AObjectNpc2D*> m_NpcList;
public:
	bool			Load(wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

