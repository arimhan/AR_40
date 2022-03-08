#pragma once
#include "World.h"
#include "SoundMgr.h"
#include "TextureMgr.h"
#include "UI.h"
#include "Input.h"
class AIntro :public AWorld
{
public:
	AWorld*		m_pNextWorld;	//Intro -> Zone���� �̵�
	ASound*		m_pBGMusic;		//Intro �� BGM 
	ATexture*	m_pColorTex;
	ATexture*	m_pChangeColorTex[10];

public:
	bool Load(wstring file) override;
	bool CreateModelType();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
};

