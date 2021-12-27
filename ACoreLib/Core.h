#pragma once
#include "Window.h"
class ACore :public AWindow
{
public:
	bool CoreInit();
	//----------------------------------------------------
	//GameRun시 Frame과 Render가 진행될 수 있도록 구조 작성
	bool GameRun(); 
	bool CoreFrame();
	bool CoreRender();
	//----------------------------------------------------
	bool CoreRelease();
};

