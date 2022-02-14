#include "Input.h"

bool AInput::Init()
{
    ZeroMemory(&m_dwKeyState, sizeof(DWORD)*256);
    return true;
}
bool AInput::Frame()
{
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
                m_dwKeyState[iKey] == KEY_UP;
            }
            else
            {
                m_dwKeyState[iKey] == KEY_FREE;
            }
        }
    }
    return true;
}
bool AInput::Render() { return true; }
bool AInput::Release() { return true; }
DWORD AInput::GetKey(DWORD dwKey) { return m_dwKeyState[dwKey]; }
AInput::AInput() {}
AInput::~AInput() {}

