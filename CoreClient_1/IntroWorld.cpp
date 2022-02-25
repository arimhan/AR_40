#include "IntroWorld.h"
#include "Input.h"
#include "ObjectMgr.h"
#include <string>

bool AIntroWorld::Init() 
{
	AWorld::Init();
	//m_pBackGroundMusic->Play(true);
	return true; 
}
bool AIntroWorld::Frame() 
{
	if (m_bLoadWorld && m_pNextWorld != nullptr)
	{
		I_ObjectMgr.Release();
		m_pNextWorld->Load(L"zone.txt");
		AWorld::m_pCurWorld = m_pNextWorld;
	}
	m_pBackGroundMusic->Frame();

	//static int iIndex = 0;
	//if (AInput::Get().GetKey(VK_F2) == KEY_PUSH)
	//{
	//	iIndex++;
	//	auto data = m_UIObj.find(L"bk");
	//	if (data != m_UIObj.end())
	//	{
	//		data->second->m_pColorTex = m_pChangeColorTex[iIndex];
	//	}
	//	//if (iIndex >= 10) { iIndex = 0; }
	//}


	//if (AInput::Get().GetKey(VK_F3) == KEY_PUSH)
	//{
	//	iIndex++;
	//	if (iIndex >= m_ExplosionObj.m_pSprite->m_rtArray.size())
	//	{
	//		iIndex = 0;
	//	}
	//	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[iIndex]);
	//	m_ExplosionObj.SetRectDraw({ 0,0, m_ExplosionObj.m_pSprite->m_rtArray[iIndex].right,
	//									  m_ExplosionObj.m_pSprite->m_rtArray[iIndex].bottom });
	//}

	////rtExplosion Effect
	//if (AInput::Get().GetKey(VK_F4) == KEY_PUSH)
	//{
	//	m_ExplosionObj.Release();
	//	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");
	//	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	//	m_ExplosionObj.SetRectDraw({ 0,0, m_ExplosionObj.m_pSprite->m_rtArray[iIndex].right,
	//									  m_ExplosionObj.m_pSprite->m_rtArray[iIndex].bottom });
	//}
	////rtBomb Effect
	//if (AInput::Get().GetKey(VK_F6) == KEY_PUSH)
	//{
	//	m_ExplosionObj.Release();
	//	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtBomb");
	//	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	//	m_ExplosionObj.SetRectDraw({ 0,0, m_ExplosionObj.m_pSprite->m_rtArray[iIndex].right,
	//									  m_ExplosionObj.m_pSprite->m_rtArray[iIndex].bottom });
	//}
	////rtClash Effect
	//if (AInput::Get().GetKey(VK_F7) == KEY_PUSH)
	//{
	//	m_ExplosionObj.Release();
	//	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtClash");
	//	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	//	m_ExplosionObj.SetRectDraw({ 0,0, m_ExplosionObj.m_pSprite->m_rtArray[iIndex].right,
	//									  m_ExplosionObj.m_pSprite->m_rtArray[iIndex].bottom });
	//}
	//m_ExplosionObj.Frame();
	AWorld::Frame();
	return true; 
}
bool AIntroWorld::Render() 
{
	AWorld::Render();
	//m_ExplosionObj.Render();
	return true; 
}
bool AIntroWorld::Release() 
{ 
	AWorld::Release();
	m_ExplosionObj.Release();
	return true; 
}
bool AIntroWorld::Load(wstring file)
{
	//시작화면에서는 이 음악이 나오도록 ~
	m_pBackGroundMusic = I_Sound.Load("../../data/Sound/NewHopeClub.MP3");
	m_pColorTex = I_Texture.Load(L"../../data/KGCABK.bmp");

	for (int i = 0; i < 10; i++) //카운트다운
	{
		wstring name = L"../../data/";
		name += to_wstring(i);
		name += L".bmp";
		m_pChangeColorTex[i] = I_Texture.Load(name);
	}
	ATexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	AShader* pVSShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
	AShader* pPSShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");
	/*AImageIObject* Obj = new AImageIObject;
	Obj->Init();
	Obj->SetRectDraw({ 0,0 ,g_rtClient.right, g_rtClient.bottom });
	Obj->SetPosition(AVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	Obj->m_pColorTex = m_pColorTex;
	Obj->m_pMaskTex = nullptr;
	Obj->m_pVSShader = pVSShader;
	Obj->m_pPSShader = pPSShader;

	if (!Obj->Create(m_pd3dDevice, m_pContext)) { return false; }

	Obj->SetCollisionType(Ignore, Select_Ignore);
	m_UIObj.insert(make_pair(L"bk", Obj));

	AImageIObject* btnObj = new AImageIObject;
	btnObj->Init();
	btnObj->SetRectDraw({0,0, 334, 82});
	btnObj->SetPosition(AVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	if (!btnObj->Create(m_pd3dDevice, m_pContext,	L"../../data/shader/DefaultUI.txt", 
													L"../../data/main_start_nor.png")) 
	{ return false; }
	btnObj->SetCollisionType(Ignore, Select_Overlap);
	m_UIObj.insert(make_pair(L"btnStart", btnObj));

	I_Sprite.Load(L"SpriteData.txt");
	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");

	m_ExplosionObj.Init();
	m_ExplosionObj.SetPosition(AVector2(400, 500));
	ASprite* pSprite = I_Sprite.GetPtr(L"rtExplosion");
	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	m_ExplosionObj.SetRectDraw({ 0,0,34,46 });

	if (!m_ExplosionObj.Create(m_pd3dDevice, m_pContext, 
		L"Shader.txt",
		L"../../data/bitmap1.bmp",
		L"../../data/bitmap1.bmp"))
	{
		return false;
	}*/

	AButtonObject* btnDlg = new AButtonObject;
	btnDlg->Init();
	btnDlg->SetRectDraw({ 0,0,g_rtClient.right, g_rtClient.bottom });
	btnDlg->SetPosition(AVector2(g_rtClient.right / 2, g_rtClient.bottom / 2));
	if (!btnDlg->Create(m_pd3dDevice, m_pContext, L"../../data/shader/DefaultUI.txt," 
													L"../../data/ui/popup_normal.png"))
	{
		return false;
	}
	btnDlg->SetCollisionType(Ignore, Select_Overlap);
	m_UIObj.insert(make_pair(L"btnStart", btnDlg));

	I_Sprite.Load(L"SpriteData.txt");
	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");

	m_ExplosionObj.Init();
	m_ExplosionObj.SetPosition(AVector2(400, 500));
	ASprite* pSprite = I_Sprite.GetPtr(L"rtExplosion");
	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	m_ExplosionObj.SetRectDraw({ 0,0,34,46 });
	if (!m_ExplosionObj.Create(m_pd3dDevice, m_pContext, L"Shader.txt", 
										L"../../data/bitmap.bmp", L"../../data/bitmap2.bmp"))
	{
		return false;
	}
	return true;
}
