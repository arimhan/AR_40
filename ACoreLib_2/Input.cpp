#include "Input.h"


POINT g_ptMouse;

bool AInput::Init()
{
	ZeroMemory(&m_dwKeyState, sizeof(DWORD) * 256 );
	return true;
}
bool AInput::Frame()
{
	POINT ptOffset = g_ptMouse;
	//화면(스크린)좌표계
	GetCursorPos(&m_ptMouse);
	//클라이언트(윈도우)좌표계
	ScreenToClient(g_hWnd, &m_ptMouse);
	g_ptMouse = m_ptMouse;

	// 마우스 버튼 VK_LBUTTON,  VK_RBUTTON, VK_MBUTTON,
	for (int iKey = 0; iKey < 256; iKey++)
	{
		SHORT sKey = GetAsyncKeyState(iKey);
		// 0000 0000 0000 0000
		// 1000 0000 0000 0000
		if (sKey & 0x8000)
		{
			if (m_dwKeyState[iKey] == KEY_FREE)
			{
				m_dwKeyState[iKey] = KEY_PUSH;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_HOLD;
			}
		}
		else
		{
			if (m_dwKeyState[iKey] == KEY_PUSH ||
				m_dwKeyState[iKey] == KEY_HOLD)
			{
				m_dwKeyState[iKey] = KEY_UP;
			}
			else
			{
				m_dwKeyState[iKey] = KEY_FREE;
			}
		}
	}

	m_dwMouseState[0] = m_dwKeyState[VK_LBUTTON];
	m_dwMouseState[1] = m_dwKeyState[VK_RBUTTON];
	m_dwMouseState[2] = m_dwKeyState[VK_MBUTTON];

	//마우스 드래그, 클릭 기능 추가

	
	if (m_dwKeyState[0] == KEY_PUSH)
	{
		m_bDrag= true;
		m_ptMouseClick = m_ptMouse;
	}
	if(m_bDrag)
	{
		m_ptDeltaMouse.x = ptOffset.x - m_ptMouse.x;
		m_ptDeltaMouse.y = ptOffset.y - m_ptMouse.y;
	}

	return true;
}
bool AInput::Render() { return true; }
bool AInput::Release() { return true; }
DWORD AInput::GetKey(DWORD dwKey) { return m_dwKeyState[dwKey]; }
T::TVector2	AInput::GetDelta()
{
	T::TVector2 ret;
	m_fRadianX += (AInput::Get().m_ptDeltaMouse.x / (float)g_rtClient.right) * ABASIS_PI;
	m_fRadianY += (AInput::Get().m_ptDeltaMouse.y / (float)g_rtClient.bottom) * ABASIS_PI;

	return TVector2(m_fRadianX, m_fRadianY);
}
AInput::AInput()
{
	m_ptDeltaMouse.x = 0.0f;
	m_ptDeltaMouse.y = 0.0f;
}
AInput::~AInput(){}