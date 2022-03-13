#pragma once
//------------------------GameState, Stage
#include "Intro.h"
#include "Play.h"

class AGameStateManager
{
private:
	HWND			m_hWnd;
	HDC				m_hMemDC;
	HBITMAP			m_hBit;
	HBITMAP			m_hOldBit;
	RECT			m_rClient;

	AGameState* GS;

	AGameStateManager() { GS = NULL; };
	~AGameStateManager() {};
public:
	void ChangeGameState(GameState _GS)
	{
		if (_GS == GS_WAIT) return;

		if (GS)
		{
			delete GS;
			GS = NULL;
		}
		switch (_GS)
		{
		case GS_INTRO:
			GS = new AIntro();
			break;
		case GS_PLAY:
			GS = new APlay();
			break;
		};
		GS->Init();
	}
	void GameEnd()
	{
		if (GS) delete GS;
	}
	AGameState* GetGameState()
	{
		return GS;
	}
	void Render()
	{
		m_hWnd = AGameEngine::GetEngine()->GetWindow();
		HDC hDC;
		HDC	hMemDC;
		GetClientRect(m_hWnd, &m_rClient);
		hDC = GetDC(m_hWnd);
		m_hBit = CreateCompatibleBitmap(hDC, m_rClient.right, m_rClient.bottom);
		m_hMemDC = CreateCompatibleDC(hDC);
		m_hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBit);
		ReleaseDC(m_hWnd, hDC);
		hDC = GetDC(m_hWnd);
		hMemDC = CreateCompatibleDC(hDC);

		GS->Render(m_hMemDC);

		DeleteDC(hMemDC);
		ReleaseDC(m_hWnd, hDC);
		hDC = GetDC(m_hWnd);
		BitBlt(hDC, 0, 0, m_rClient.right, m_rClient.bottom, m_hMemDC, 0, 0, SRCCOPY);

		SelectObject(m_hMemDC, m_hOldBit);
		DeleteObject(m_hBit);
		DeleteDC(m_hMemDC);
		ReleaseDC(m_hWnd, hDC);
		InvalidateRect(m_hWnd, NULL, FALSE);

	}
	static AGameStateManager* Instance()
	{
		static AGameStateManager _Instance;
		return &_Instance;
	}
};




