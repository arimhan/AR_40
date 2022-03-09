#pragma once
#include "World.h"
#include "PlayerObj2D.h"
#include "ObjectNPC2D.h"
#include "UIObject.h"
#include "SoundMgr.h"
#include "ShaderMgr.h"
#include "TextureMgr.h"
#include "EffectObj.h"

class AIntroWorld :public AWorld
{
public:

	//int				rt_x = 50, rt_y = 50;
	//ASprite			m_SpriteObj;
	AEffectObj		m_ExplosionObj;
	AWorld*			m_pNextWorld;
	//AButtonObject	m_UIStartBtnD;
public:
	ASound*			m_pBackGroundMusic;
	ATexture*		m_pChangeColorTex[10];
	ATexture*		m_pColorTex;
public:
	bool			CreateModelType();
	bool			Load(wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

