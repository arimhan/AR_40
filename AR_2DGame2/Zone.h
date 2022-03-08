#pragma once
#include "World.h"
//#include "Object2D.h"
#include "Object.h"
#include "SoundMgr.h"
#include "Input.h"
class AZone : public AWorld
{
public:
	AObjectPlayer2D	m_PlayerObj;
	ASound*			m_pBGMusic;
public:
	bool Load(wstring file) override;
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

