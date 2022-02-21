#pragma once
#include "World.h"
#include "PlayerObj2D.h"
#include "ObjectNPC2D.h"
#include "Sound.h"
class AIntroWorld :public AWorld
{
public:
	AObject2D		m_PlayerObj; //APlayerObj2D -> AObject2D로 변경 (플레이어가 아니므로)
	ASound*			m_pBackGroundMusic;
public:
	bool			Load(wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

