#pragma once
//--------------------------Library
#include "Core.h"
#include "World.h"
#include "SoundMgr.h"
#include "GameEngine.h"
//#include "GameState.h"
#include "GameStateMgr.h"

#include "Intro.h"
#include "Mgr.h"

class AMain 
{
public:
	AIntro		m_IntroWorld;
	APlay		m_PlayWorld;

public:
	void Init();
	void Frame();
	void Render();
	void Release();
	AMain() {};
	~AMain() {};
};

