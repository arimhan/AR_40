#pragma once
#include "Device.h"
#include "DxObject.h"
#include "Input.h"
#include "Timer.h"
#include "WriteFont.h"
#include "Camera.h"

class ACore : public ADevice
{
public:
	ACamera*	m_pMainCamera = nullptr;
	ACamera		m_DefaultCamera;
	ATimer		m_GameTimer;
	AWriteFont  m_dxWrite;
	bool		m_bWireFrame = false;
private:
//외부에서 접근 불가능한 Core기능. Init부터 Render/ Release기능
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
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
public:
	ACore();
	virtual ~ACore();
};

