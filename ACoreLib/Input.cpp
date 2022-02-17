#include "Input.h"
POINT g_ptMouse;

bool AInput::Init()
{
    ZeroMemory(&m_dwKeyState, sizeof(DWORD)*256);
    return true;
}
bool AInput::Frame()
{
    for (int iKey = 0; iKey < 256; iKey++)
    {
        //화면(스크린)좌표계
        GetCursorPos(&m_ptMouse);
        //클라이언트(윈도우)좌표계
        ScreenToClient(g_hWnd, &m_ptMouse);
        g_ptMouse = m_ptMouse;

        for (int iKey = 0; iKey < 256; iKey++)
        {
            SHORT sKey = GetAsyncKeyState(iKey);
            //GetAsyncKeyState함수 반환값 SHORT형, KEY 누르면 0000 16비트  최상위 비트가 1로 변함.

            //GetAsyncKeyState 함수로 현재 key의 눌림 상태를 체크한다. 0x8000일 경우 (눌리지 않을 경우 상태 체크)
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
            else // 눌려있거나 한번이라도 눌렀을 경우의 상태 체크
            {
                if (m_dwKeyState[iKey] == KEY_PUSH || m_dwKeyState[iKey] == KEY_HOLD)
                {
                    m_dwKeyState[iKey] = KEY_UP;
                }
                else
                {
                    m_dwKeyState[iKey] = KEY_FREE;
                }
            }
        }
    }
    //마우스 버튼 VK_LBUTTON, VK_RBUTTON, VK_MBUTTON (LEFT, RIGHT, MIDDLE)
    m_dwMouseState[0] = m_dwKeyState[VK_LBUTTON];
    m_dwMouseState[1] = m_dwKeyState[VK_MBUTTON];
    m_dwMouseState[2] = m_dwKeyState[VK_RBUTTON];
    return true;
}
bool AInput::Render() { return true; }
bool AInput::Release() { return true; }
DWORD AInput::GetKey(DWORD dwKey) { return m_dwKeyState[dwKey]; }
AInput::AInput() {}
AInput::~AInput() {}

