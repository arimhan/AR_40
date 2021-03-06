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
	ASprite			m_SpriteObj;
	AEffectObj		m_ExplosionObj;
	AWorld*			m_pNextWorld;
public:
	ASound*			m_pBackGroundMusic;
	ATexture*		m_pChangeColorTex[10];
	ATexture*		m_pColorTex;
public:
	bool			Load(wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

