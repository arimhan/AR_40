#pragma once
#include "Device.h"
class ACore :public ADevice
{
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
