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

	if(	m_ptMouse.x < 0 || m_ptMouse.x > g_rtClient.right ||
		m_ptMouse.y < 0 || m_ptMouse.y > g_rtClient.bottom) 
	{
		//클라이언트 영역을 벗어나면 드래그 불가능하도록 설정
		m_bDrag = false;
	}

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

	//마우스 왼쪽 버튼을 누르고 있거나, 눌렀다 뗐을 경우 처리
	if (m_dwMouseState[0] == KEY_PUSH)	//누르고 있을 경우 드래그 처리하며 이때 마우스의 위치를 읽는다.
	{
		m_bDrag= true;
		m_ptMouseClick = m_ptMouse;
	}
	if (m_dwMouseState[0] == KEY_UP)
	{
		m_bDrag = false;				//눌렀다 뗐을 경우에는 드래그 기능을 막는다. (true일 경우 클릭하는 순간 계속 드래그 됨)
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
A::AVector2	AInput::GetDelta()
{
	A::AVector2 ret;
	m_fRadianY = (AInput::Get().m_ptDeltaMouse.x / (float)g_rtClient.right) * ABASIS_PI;
	m_fRadianX = (AInput::Get().m_ptDeltaMouse.y / (float)g_rtClient.bottom) * ABASIS_PI;

	return A::AVector2(m_fRadianX, m_fRadianY);
}
AInput::AInput()
{
	m_ptDeltaMouse.x = 0.0f;
	m_ptDeltaMouse.y = 0.0f;
}
AInput::~AInput(){}