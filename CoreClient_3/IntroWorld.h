#pragma once
#include "World.h"
#include "PlayerObj2D.h"
#include "ObjectNpc2D.h"
#include "UIObject.h"
#include "SoundMgr.h"
#include "ShaderMgr.h"
#include "TextureMgr.h"
#include "EffectObj.h"
class AIntroWorld : public AWorld
{
public:
	ASprite				m_SpriteObj;
	AEffectObj			m_ExplosionObj;
	ASound*				m_pBackGroundMusic;
	ATexture*			m_pChangeColorTex[10];
	ATexture*			m_pColorTex;
	AWorld*				m_pNextWorld;
public:
	bool	CreateModelType();
	bool	Load(std::wstring file) override;
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
};

