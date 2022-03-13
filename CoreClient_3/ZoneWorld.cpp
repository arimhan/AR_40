#include "ZoneWorld.h"
#include "UIObject.h"
#include "DxObject.h"

bool	AZoneWorld::Init()
{
	return true;
}
bool	AZoneWorld::Load(std::wstring file)
{
	I_Texture.Load(L"../../data/Img/stage1_1.png");

	//배경 출력
	AObject2D* pNewBK = I_UI.GetPtr(L"bk")->Clone();
	pNewBK->m_csName = L"AImageObjectClock:bk";
	pNewBK->SetPosition(AVector2(g_rtClient.right / 2, g_rtClient.bottom / 2)); 
	//배경이미지 그대로 출력하기 위해 Intro와 동일하게 두번 출력
	pNewBK->UpdateData();
	m_UIObj.push_back(shared_ptr<AObject2D>(pNewBK));

	ASound* pSound = I_Sound.Load("../../data/Sound/LovingUGirl.mp3");
	//pSound = I_Sound.Load("../../data/Sound/MyLove.MP3");
	m_pBackGroundMusic = I_Sound.Load("../../data/Sound/LovingUGirl.mp3");
	pSound = I_Sound.Load("../../data/Sound/00_Menu.MP3");
	pSound = I_Sound.Load("../../data/Sound/Gun1.wav");
	pSound = I_Sound.Load("../../data/Sound/abel_leaf.asf");
	pSound = I_Sound.Load("../../data/Sound/GunShot.mp3");
	m_pBackGroundMusic->Play(true);

	//for (int i = 0; i < 10; i++) //카운트다운
	//{
	//	wstring name = L"../../data/Img/";
	//	name += to_wstring(i);
	//	name += L".bmp";
	//	m_pChangeColorTex[i] = I_Texture.Load(name);
	//}

	//플레이어, NPC 이미지 로드 및 배치
	m_PlayerObj.Init();
	m_PlayerObj.SetPosition(AVector2(400, 500));
	m_PlayerObj.SetRectSource({ 0,0,32,32 });//({ 91,1,42,56 });
	m_PlayerObj.SetRectDraw({ 0,0, 32,32 });//({ 0,0, 42,56 }); // 30,32
	m_PlayerObj.m_csName = L"PlayerUser";	
	if (!m_PlayerObj.Create(m_pd3dDevice, m_pContext,
		L"Shader.txt",
		L"../../data/Img/ship.png",
		L"../../data/Img/ship2.png"))
	{
		return false;
	}

	for (int iNpc = 0; iNpc < 5; iNpc++)
	{
		shared_ptr<AObjectNpc2D> npc = make_shared<AObjectNpc2D>();
		npc->m_csName = L"NPC_";
		npc->m_csName += std::to_wstring(iNpc);
		npc->Init();
		npc->SetPosition(AVector2(50 + iNpc * 150, 50));
		if (iNpc % 2 == 0)
		{
			npc->SetRectSource({ 0,0,0,0 });
			npc->SetRectDraw({ 0,0,48,48 });
		}
		else
		{
			npc->SetRectSource({ 0,0,0,0 });
			npc->SetRectDraw({ 0,0,48,48 });
		}
		if (!npc->Create(m_pd3dDevice, m_pContext,
			L"Shader.txt",
			L"../../data/Img/enemy.png",
			L"../../data/Img/enemy2.png"))
		{
			return false;
		}
		m_NpcObj.push_back(npc);
	}
	return true;
}
bool	AZoneWorld::Frame()
{
	//if (AInput::Get().GetKey(VK_F1) == KEY_PUSH)
	//{
	//	ASound* pSound = I_Sound.GetPtr(L"GunShot.mp3");
	//	if (pSound != nullptr)
	//	{
	//		pSound->PlayEffect();
	//	}
	//}
	m_pBackGroundMusic->Frame();

	if (AInput::Get().GetKey(VK_UP) == KEY_HOLD)
	{
		m_pBackGroundMusic->VolumeUp(g_fSecPerFrame);
	}
	if (AInput::Get().GetKey(VK_DOWN) == KEY_HOLD)
	{
		m_pBackGroundMusic->VolumeDown(g_fSecPerFrame);
	}

	m_PlayerObj.Frame();
	AWorld::Frame();
	return true;
}
bool	AZoneWorld::Render()
{
	AWorld::Render();
	m_PlayerObj.Render();
	return true;
}
bool	AZoneWorld::Release()
{
	m_PlayerObj.Release();
	return true;
}