#include "Zone.h"

bool AZone::Load(wstring file)
{
    ASound* pSound = I_Sound.Load("../../data/Sound/LovingUGirl.mp3");
	pSound = I_Sound.Load("../../data/Sound/GunShot.mp3");
    m_pBGMusic = I_Sound.Load("../../data/Sound/LovingUGirl.mp3");
    m_pBGMusic->Play(true);

	m_PlayerObj.Init();
	m_PlayerObj.SetPosition(AVector2(400, 500));
	m_PlayerObj.SetRectSource({ 91,1,42,56 });
	//m_PlayerObj.SetRectSouce({ 46,63,69,79 });
	m_PlayerObj.SetRectDraw({ 0,0, 42,56 });
	m_PlayerObj.m_csName = L"PlayerUser";
	if (!m_PlayerObj.Create(m_pd3dDevice, m_pContext,
		L"Shader.txt",
		L"../../data/Img/bitmap1.bmp",
		L"../../data/Img/bitmap2.bmp"))
	{
		return false;
	}

	for (int iNpc = 0; iNpc < 10; iNpc++)
	{
		std::shared_ptr<AObjectNPC2D> npc =
			std::make_shared<AObjectNPC2D>();
		npc->m_csName = L"NPC_";
		npc->m_csName += std::to_wstring(iNpc);
		npc->Init();
		npc->SetPosition(AVector2(50 + iNpc * 150, 50));
		if (iNpc % 2 == 0)
		{
			npc->SetRectSource({ 46,63,69,79 });
			npc->SetRectDraw({ 0,0, 69,79 });
		}
		else
		{
			npc->SetRectSource({ 1,63,42,76 });
			npc->SetRectDraw({ 0,0, 42,76 });
		}


		if (!npc->Create(m_pd3dDevice, m_pContext,
			L"Shader.txt",
			L"../../data/Img/bitmap1.bmp",
			L"../../data/Img/bitmap2.bmp"))
		{
			return false;
		}
		m_CharactorObj.push_back(npc);
	}
    return true;
}

bool AZone::Init()
{
    return true;
}

bool AZone::Frame()
{
    if (AInput::Get().GetKey(VK_F1) == KEY_PUSH)
    {
		ASound* pSound = I_Sound.GetPtr(L"GunShot.mp3");
		{
			if (pSound != nullptr)
			{
				pSound->PlayEffect();
			}
		}
    }
    m_pBGMusic->Frame();
    if (AInput::Get().GetKey(VK_UP) == KEY_HOLD)
    {
        m_pBGMusic->VolumeUP(g_fSecPerFrame);
    }
    if (AInput::Get().GetKey(VK_DOWN) == KEY_HOLD)
    {
        m_pBGMusic->VolumeDown(g_fSecPerFrame);
    }
	m_PlayerObj.Frame();
    AWorld::Frame();
    return true;
}

bool AZone::Render()
{
    AWorld::Render();
	m_PlayerObj.Render();
    return true;
}

bool AZone::Release()
{
    m_PlayerObj.Release();
    return true;
}
