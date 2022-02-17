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
        //ȭ��(��ũ��)��ǥ��
        GetCursorPos(&m_ptMouse);
        //Ŭ���̾�Ʈ(������)��ǥ��
        ScreenToClient(g_hWnd, &m_ptMouse);
        g_ptMouse = m_ptMouse;

        for (int iKey = 0; iKey < 256; iKey++)
        {
            SHORT sKey = GetAsyncKeyState(iKey);
            //GetAsyncKeyState�Լ� ��ȯ�� SHORT��, KEY ������ 0000 16��Ʈ  �ֻ��� ��Ʈ�� 1�� ����.

            //GetAsyncKeyState �Լ��� ���� key�� ���� ���¸� üũ�Ѵ�. 0x8000�� ��� (������ ���� ��� ���� üũ)
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
            else // �����ְų� �ѹ��̶� ������ ����� ���� üũ
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
    //���콺 ��ư VK_LBUTTON, VK_RBUTTON, VK_MBUTTON (LEFT, RIGHT, MIDDLE)
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

