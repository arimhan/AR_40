#pragma once
#include "Core.h"
#include "AsyncSelect.h"
//#include "World.h"
#include "Intro.h"
#include "Zone.h"
//#include <string>
#define PORT_NUM 9110 //9110
#define ADRESS_NUM "127.0.0.1" //"127.0.0.1"


class AMain : public ACore
{
public:
	AIntro		m_Intro;
	AZone		m_Zone;
public:
	AAsyncSelect			m_Net;
	HWND					m_hEdit;
	HWND					m_hButton;
	HWND					m_hListBox;
	int						m_iChatCnt;
public:
	//4가지 기능 재정의 및 가상함수 처리
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
	virtual LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	AMain() {};
	~AMain() {};
};