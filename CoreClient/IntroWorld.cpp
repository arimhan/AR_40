#include "IntroWorld.h"
#include "Input.h"

bool AIntroWorld::Init() 
{
	AWorld::Init();
	//m_pBackGroundMusic->Play(true);
	return true; 
}
bool AIntroWorld::Frame() 
{
	m_pBackGroundMusic->Frame();
	static int iIndex = 0;
	if (AInput::Get().GetKey(VK_F2) == KEY_PUSH)
	{
		iIndex++;
		auto data = m_UIObj.find(L"bk");
		if (data != m_UIObj.end())
		{
			data->second->m_pColorTex = m_pChangeColorTex[iIndex];
		}
		if (iIndex >= 10) { iIndex = 0; }
	}
	AWorld::Frame();
	return true; 
}
bool AIntroWorld::Render() 
{
	AWorld::Render();
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
	AImageIObject* Obj = new AImageIObject;
	Obj->Init();
	Obj->SetRectDraw({ 0,0 ,g_rtClient.right, g_rtClient.bottom });
	Obj->SetPosition(AVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	Obj->m_pColorTex = m_pColorTex;
	Obj->m_pMaskTex = nullptr;
	Obj->m_pVSShader = pVSShader;
	Obj->m_pPSShader = pPSShader;

	if (!Obj->Create(m_pd3dDevice, m_pContext)) { return false; }
	m_UIObj.insert(make_pair(L"bk", Obj));

	AImageIObject* btnObj = new AImageIObject;
	btnObj->Init();
	btnObj->SetRectDraw({0,0, 334, 82});
	btnObj->SetPosition(AVector2(g_rtClient.right / 2.0f, g_rtClient.bottom / 2.0f));
	if (!btnObj->Create(m_pd3dDevice, m_pContext,	L"../../data/shader/DefaultUI.txt", 
													L"../../data/main_start_nor.png")) 
	{ return false; }
	m_UIObj.insert(make_pair(L"btnStart", btnObj));

	return true;
}
