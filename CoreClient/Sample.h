#pragma once
#include "Core.h"
#include "AsyncSelect.h"
#include "PlayerObj2D.h"
#include "ObjectNpc2D.h"
#include "Sound.h"

class ASample : public ACore
{
public:
	APlayerObj2D			m_PlayerObj;
	ASoundMgr				m_SoundMgr;
public:
	vector<AObjectNpc2D*>	m_NpcList;
	AAsyncSelect			m_Net;
	HWND					m_hEdit;
	HWND					m_hButton;
	HWND					m_hListBox;
	int						m_iChatCnt;

	virtual bool	Init() override;
	virtual bool	Frame() override;
	virtual bool	Render() override;
	virtual bool	Release() override;
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	ASample();
	~ASample();
};