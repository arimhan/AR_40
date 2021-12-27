#pragma once
#include "Device.h"
class ACore :public ADevice
{
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

	virtual bool Init() {
		return true;
	}
	virtual bool Frame() {
		return true;
	}
	virtual bool Render() {
		return true;
	}
	virtual bool Release() {
		return true;
	}
};

