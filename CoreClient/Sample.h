#pragma once
#include "Core.h"
#include "AsyncSelect.h"
#include "IntroWorld.h"
//#include "LoginWorld.h"
#include "ZoneWorld.h"

class ASample : public ACore
{
public:
	AIntroWorld				m_IntroWorld;
	AZoneWorld				m_ZoneWorld;
	//APlayerObj2D			m_PlayerObj;
	//ASoundMgr				m_SoundMgr;
public:
	//vector<AObjectNpc2D*>	m_NpcList;
	AAsyncSelect			m_Net;
	HWND					m_hEdit;
	HWND					m_hButton;
	HWND					m_hListBox;
	int						m_iChatCnt;
public:
	virtual bool	Init() override;
	virtual bool	Frame() override;
	virtual bool	Render() override;
	virtual bool	Release() override;
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	virtual void	CreateResizeDevice(UINT iWidth, UINT iHeight) override;
	virtual void	DeleteResizeDevice(UINT iWidth, UINT iHeight) override;

	ASample();
	~ASample();
};