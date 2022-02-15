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
	//GameRun시 Frame과 Render가 진행될 수 있도록 구조 작성
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

