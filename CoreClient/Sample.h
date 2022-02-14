#pragma once
#include "Core.h"
#include "AsyncSelect.h"
#include "PlayerObj2D.h"
#include "ObjectNpc2D.h"
#define PORT_NUM 9110 //9110
#define ADRESS_NUM "127.0.0.1" //"127.0.0.1"
class ASample : public ACore
{
public:
	APlayerObj2D	m_PlayerObj;
public:
	vector<AObjectNpc2D>	m_NpcList;
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