#pragma once
#include "Device.h"
#include "DxObject.h"
#include "Input.h"
#include "Timer.h"
#include "WriteFont.h"

class ACore : public ADevice
{
public:
	ATimer		m_GameTimer;
	AWriteFont  m_dxWrite;
	
//private:
	bool	CoreInit();	
		bool	CoreFrame();
		bool	CoreRender();
	bool	CoreRelease();
public:
	bool	GameRun();
public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) {};
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) {};
	void			ResizeDevice(UINT iWidth, UINT iHeight);
	virtual bool	Init() { return true; };
	virtual bool	Frame() { return true; };
	virtual bool	Render() { return true; };
	virtual bool	Release() { return true; };

public:
	ACore();
	virtual ~ACore();
};

