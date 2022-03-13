#pragma once
//--------------------------Library
#include "Mgr.h"
#include "GameEngine.h"
#include "GameState.h"
#include "SoundMgr.h"
#include "Core.h"
//--------------------------Stage
//#include "Play.h"

class AIntro : public AGameState 
{
public:
	ASound*		m_pBGMusic;
	HWND		m_hButton;
public:
	void		Init();
	bool		Frame();
	bool		Release();
	void		Update();
	void		Render(HDC hdc);
	GameState	ChangeGameState();
public:
	bool		CreateModelType();
	bool		Load(wstring file);

public:
	AIntro();
	~AIntro();

};



