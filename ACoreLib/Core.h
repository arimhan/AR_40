#pragma once
#include "Window.h"
class ACore :public AWindow
{
public:
	bool CoreInit();
	//----------------------------------------------------
	//GameRun�� Frame�� Render�� ����� �� �ֵ��� ���� �ۼ�
	bool GameRun(); 
	bool CoreFrame();
	bool CoreRender();
	//----------------------------------------------------
	bool CoreRelease();
};

