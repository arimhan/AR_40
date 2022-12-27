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
	//ȭ��(��ũ��)��ǥ��
	GetCursorPos(&m_ptMouse);
	//Ŭ���̾�Ʈ(������)��ǥ��
	ScreenToClient(g_hWnd, &m_ptMouse);
	g_ptMouse = m_ptMouse;

	if(	m_ptMouse.x < 0 || m_ptMouse.x > g_rtClient.right ||
		m_ptMouse.y < 0 || m_ptMouse.y > g_rtClient.bottom) 
	{
		//Ŭ���̾�Ʈ ������ ����� �巡�� �Ұ����ϵ��� ����
		m_bDrag = false;
	}

	// ���콺 ��ư VK_LBUTTON,  VK_RBUTTON, VK_MBUTTON,
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

	//���콺 ���� ��ư�� ������ �ְų�, ������ ���� ��� ó��
	if (m_dwMouseState[0] == KEY_PUSH)	//������ ���� ��� �巡�� ó���ϸ� �̶� ���콺�� ��ġ�� �д´�.
	{
		m_bDrag= true;
		m_ptMouseClick = m_ptMouse;
	}
	if (m_dwMouseState[0] == KEY_UP)
	{
		m_bDrag = false;				//������ ���� ��쿡�� �巡�� ����� ���´�. (true�� ��� Ŭ���ϴ� ���� ��� �巡�� ��)
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