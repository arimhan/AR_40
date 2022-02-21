#include "IntroWorld.h"
#include "Input.h"
bool AIntroWorld::Init() 
{
	//m_pBackGroundMusic->Play(true);
	return true; 
}
bool AIntroWorld::Frame() 
{
	m_pBackGroundMusic->Frame();
	for (auto obj : m_UIObj)
	{
		AObject2D* pObj = obj.second;
		if (pObj != nullptr)
		{
			pObj->m_ConstantList.Color = AVector4(
				cosf(g_fGameTimer) * 0.5f + 0.5f,
				cosf(g_fGameTimer) * 0.5f + 0.5f,
				cosf(g_fGameTimer) * 0.5f + 0.5f, 1.0f);
			pObj->m_ConstantList.Timer = AVector4(
				g_fGameTimer, 0, 0, 1.0f);
			m_pContext->UpdateSubresource(
				pObj->m_pConstantBuffer, 0, NULL, &pObj->m_ConstantList, 0, 0);
		}
	}
	return true; 
}
bool AIntroWorld::Render() 
{
	for (auto obj : m_UIObj)
	{
		AObject2D* pObj = obj.second;
		if (pObj != nullptr)
		{
			pObj->Render();
		}
	}
	return true; 
}
bool AIntroWorld::Release() 
{ 
	AWorld::Release();
	return true; 
}
bool AIntroWorld::Load(wstring file)
{
	//시작화면에서는 이 음악이 나오도록 ~
	m_pBackGroundMusic = I_Sound.Load("../../data/Sound/NewHopeClub.MP3");
	AObject2D* Obj = new AObject2D;
	Obj->Init();
	Obj->SetRectDraw({ 0,0 ,g_rtClient.right, g_rtClient.bottom });
	Obj->SetPosition(AVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	if (!Obj->Create(m_pd3dDevice, m_pContext, L"../../data/KGCABK.bmp")) { return false; }
	m_UIObj.insert(make_pair(L"bk", Obj));
	return true;
}
