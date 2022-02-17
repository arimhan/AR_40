#pragma once
#include "Device.h"
#include "DxObject.h"
#include "Input.h"
#include "Timer.h"
#include "WriteFont.h"
class ACore :public ADevice
{
public:
	ATimer		m_GameTimer;
	AWriteFont	m_dxWrite;
	ID3D11SamplerState*		m_pSamplerState = nullptr;
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

