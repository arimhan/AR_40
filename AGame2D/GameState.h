#pragma once
#include <Windows.h>


typedef enum {GS_INTRO, GS_PLAY, GS_GAMEOVER, GS_WAIT}GameState;

class AGameState
{
public:
	GameState flag;
public:
	virtual void Init() {};
	virtual void Update() {};
	virtual void Render(HDC hdc) {};
	virtual GameState ChangeGameState() { return GS_WAIT; }
public:
	AGameState() {};
	~AGameState() {};
};
