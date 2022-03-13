#pragma once
#include "GameState.h"

class APlay :public AGameState
{
private:
	GameState	flag;


public:
	void	Init();
	void	GameInit();
	void	Update();
	void	Render(HDC hdc);
	GameState ChangeGameState();
	void	CheckCollision();
	void	CheckCollision_Enemy();
	void	DrawMap(HDC hdc);
	void	LoadMap();

public:
	APlay();
	~APlay();
};

