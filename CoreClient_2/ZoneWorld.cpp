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
	m_PlayerObj.SetPosition(AVector2(300, 400));
	m_PlayerObj.SetRectSource({ 91,1,42,56 });
	m_PlayerObj.SetRectDraw({ 0,0,42,56 });
	m_PlayerObj.m_csName = L"PlayerUser";
	if (!m_PlayerObj.Create(m_pd3dDevice, m_pContext, 
		L"Shader.txt", L"../../data/Img/bitmap1.bmp", L"../../data/Img/bitmap2.bmp"))
	{	return false;	}

	for (int iNpc = 0; iNpc < 3; iNpc++)
	{
		//AObjectNpc2D* npc = new AObjectNpc2D;
		shared_ptr<AObjectNpc2D> npc = make_shared<AObjectNpc2D>();
		npc->m_csName = L"NPC_";
		npc->m_csName += to_wstring(iNpc);
		npc->Init();
		npc->SetPosition(AVector2(50 + iNpc * 150, 50));
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

		if (!npc->Create(m_pd3dDevice, m_pContext, 
			L"Shader.txt", L"../../data/Img/bitmap1.bmp",L"../../data/Img/bitmap2.bmp"))
		{ return false; }
		 
		m_NpcObj.push_back(npc);
	}
	return true;
}
bool AZoneWorld::Frame() 
{ 
	//F1 -> 이펙트 사운드
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
	AWorld::Frame();
	return true; 
}
bool AZoneWorld::Render() 
{
	AWorld::Render();
	m_PlayerObj.Render();
	return true; 
}
bool AZoneWorld::Release() 
{ 
	m_PlayerObj.Release();
	return true; 
}

