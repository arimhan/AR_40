#include "ZoneWorld.h"
#include "Input.h"

bool AZoneWorld::Init() { return true; }
bool AZoneWorld::Load(wstring file)
{
	ASound* pSound = I_Sound.Load("../../data/Sound/Munn.MP3");
	pSound = I_Sound.Load("../../data/Sound/JoelAdams.MP3");
	m_pBackGroundMusic = I_Sound.Load("../../data/Sound/NewHopeClub.mp3");//JoelAdams.MP3");
	pSound = I_Sound.Load("../../data/Sound/Gun1.wav");
	m_pBackGroundMusic->Play(true);

	m_PlayerObj.Init();
	m_PlayerObj.SetPosition(AVector2(400, 500));
	m_PlayerObj.SetRectSource({ 91,1,42,56 });
	m_PlayerObj.SetRectDraw({ 0,0,42,56 });
	if (!m_PlayerObj.Create(m_pd3dDevice, m_pContext, L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp"))
	{	return false;	}

	for (int iNpc = 0; iNpc < 7; iNpc++)
	{
		AObjectNpc2D* npc = new AObjectNpc2D;
		npc->Init();
		if (iNpc % 2 == 0)
		{
			npc->SetRectSource({46,63,69,79});
			npc->SetRectDraw({0,0,69,79});
		}
		else
		{
			npc->SetRectSource({ 1,63,42,76 });
			npc->SetRectDraw({ 0,0,42,76 });
		}
		npc->SetPosition(AVector2(50 + iNpc * 150, 50));
		if (!npc->Create(m_pd3dDevice, m_pContext, L"../../data/bitmap1.bmp", L"../../data/bitmap2.bmp"))
		{ return false; }
		 
		m_NpcList.push_back(npc);
	}
	return true;
}
bool AZoneWorld::Frame() 
{ 
	if (AInput::Get().GetKey(VK_F1) == KEY_PUSH)
	{
		ASound* pSound = I_Sound.GetPtr(L"Gun1.wav");
		if (pSound != nullptr)
		{
			pSound->PlayEffect();
		}
	}
	m_pBackGroundMusic->Frame();

	if (AInput::Get().GetKey(VK_UP) == KEY_HOLD)
	{
		m_pBackGroundMusic->VolumeUP(g_fSecPerFrame);
	}
	if (AInput::Get().GetKey(VK_DOWN) == KEY_HOLD)
	{
		m_pBackGroundMusic->VolumeDown(g_fSecPerFrame);
	}

	m_PlayerObj.Frame();
	for (int iObj = 0; iObj < m_NpcList.size(); iObj++)
	{
		m_NpcList[iObj]->Frame();
	}
	return true; 
}
bool AZoneWorld::Render() 
{
	for (int iObj = 0; iObj < m_NpcList.size(); iObj++)
	{
		if (m_NpcList[iObj]->m_bDead == false)
		{
			m_NpcList[iObj]->Render();
		}
	}
	m_PlayerObj.Render();
	return true; 
}
bool AZoneWorld::Release() 
{ 
	for (int iObj = 0; iObj < m_NpcList.size(); iObj++)
	{
		m_NpcList[iObj]->Release();
		delete m_NpcList[iObj];
	}
	m_PlayerObj.Release();
	m_NpcList.clear();
	return true; 
}

