#pragma once
#include "Device.h"
#include "DxObject.h"
#include "ObjectMgr.h" //I_ObjectMgr 
#include "Input.h"
#include "Timer.h"
class ACore :public ADevice
{
public:
	ATimer		m_GameTimer;
private:
	bool CoreInit();
	//----------------------------------------------------
	//GameRun�� Frame�� Render�� ����� �� �ֵ��� ���� �ۼ�
	    bool CoreFrame();
	    bool CoreRender();
	//----------------------------------------------------
	bool CoreRelease();
public:
    bool GameRun();
public:

	virtual bool Init() {return true;}
	virtual bool Frame() { return true; }
	virtual bool Render() { return true; }
	virtual bool Release() { return true; }

	ACore();
	virtual ~ACore();
};

