#include "IntroWorld.h"
#include "Input.h"
#include "ObjectMgr.h"
#include <string>
#include "UIModelMgr.h"

bool AIntroWorld::Init() 
{
	AWorld::Init();
	return true; 
}
bool AIntroWorld::Frame() 
{
	if (m_bLoadWorld && m_pNextWorld != nullptr)
	{
		I_ObjectMgr.Release();
		m_pNextWorld->Load(L"ZONE.txt");
		AWorld::m_pCurWorld = m_pNextWorld;
	}
	m_pBackGroundMusic->Frame();
	static int iIndex = 0;
	/*if (AInput::Get().GetKey(VK_F2) == KEY_PUSH)
	{
		iIndex++;
		if (iIndex >= 10) { iIndex = 0; }
		auto data = m_UIObj.find(L"bk");
		if (data != m_UIObj.end())
		{
			data->second->m_pColorTex = m_pChangeColorTex[iIndex];
		}
	}*/
	if (AInput::Get().GetKey(VK_F3) == KEY_PUSH)
	{
		iIndex++;
		if (iIndex >= m_ExplosionObj.m_pSprite->m_rtArray.size())
		{
			iIndex = 0;
		}
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[iIndex]);
		m_ExplosionObj.SetRectDraw({ 0,0, m_ExplosionObj.m_pSprite->m_rtArray[iIndex].right,
										  m_ExplosionObj.m_pSprite->m_rtArray[iIndex].bottom });
	}
	//rtExplosion Effect
	if (AInput::Get().GetKey(VK_F4) == KEY_PUSH)
	{

		m_ExplosionObj.Reset();
		m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
		m_ExplosionObj.SetRectDraw({ 50,50, m_ExplosionObj.m_pSprite->m_rtArray[0].right,
										  m_ExplosionObj.m_pSprite->m_rtArray[0].bottom });
	}
	//rtBomb Effect
	if (AInput::Get().GetKey(VK_F6) == KEY_PUSH)
	{
		m_ExplosionObj.Reset();
		m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtBomb");
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
		m_ExplosionObj.SetRectDraw({ 0,0, m_ExplosionObj.m_pSprite->m_rtArray[0].right,
										  m_ExplosionObj.m_pSprite->m_rtArray[0].bottom });
	}
	//rtClash Effect
	if (AInput::Get().GetKey(VK_F7) == KEY_PUSH)
	{
		m_ExplosionObj.Reset();
		m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtClash");
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
		m_ExplosionObj.SetRectDraw({ 0,0, m_ExplosionObj.m_pSprite->m_rtArray[0].right,
										  m_ExplosionObj.m_pSprite->m_rtArray[0].bottom });
	}
	m_ExplosionObj.Frame();
	AWorld::Frame();
	return true; 
}
bool AIntroWorld::Render() 
{
	AWorld::Render();
	m_ExplosionObj.Render();
	return true; 
}
bool AIntroWorld::Release() 
{ 
	AWorld::Release();
	m_ExplosionObj.Release();
	return true; 
}
bool AIntroWorld::CreateModelType()
{
	//배경 (kgcabk)
	AShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
	AShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");
	shared_ptr<AImageObject> Obj(new AImageObject);
	Obj->m_csName = L"AImageObject:bk";
	Obj->Init();
	Obj->SetRectDraw({ 0,0 ,g_rtClient.right, g_rtClient.bottom });
	Obj->SetPosition(AVector2(0, 0));
	Obj->m_pColorTex = m_pColorTex;
	Obj->m_pMaskTex = nullptr;
	Obj->m_pVShader = pVShader;
	Obj->m_pPShader = pPShader;

	if (!Obj->Create(m_pd3dDevice, m_pContext)) { return false; }

	Obj->SetCollisionType(ACollisionType::Ignore, ASelectType::Select_Ignore);
	I_UI.m_list.insert(make_pair(L"bk", Obj));

	////버튼
	//shared_ptr<AButtonObject> btnObj(new AButtonObject);
	//btnObj->m_csName = L"AButtonObject:btnStart";
	//btnObj->Init();
	//btnObj->m_rtOffset = { 110, 50 ,0, 0 };		//(,0,) ~ 출력끝점 (x,y) 
	////btnObj->SetRectDraw({ 0,0, 0,0 });			//여러개 출력할경우에만
	//btnObj->SetPosition(AVector2(0, 0));
	//ATexture* pTex = I_Texture.Load(L"../../data/ui/btnStart.bmp");
	//ASound* pSound = I_Sound.Load("../../data/Sound/00_Menu.MP3");
	//btnObj->m_pStatePlayList.emplace_back(pTex, pSound);

	//if (!btnObj->Create(m_pd3dDevice, m_pContext,
	//	L"../../data/shader/DefaultUI.txt",	L"../../data/ui/btnStart.bmp"))
	//{
	//	return false;
	//}
	//btnObj->SetCollisionType(ACollisionType::Ignore, ASelectType::Select_Overlap);
	//I_UI.m_list.insert(std::make_pair(L"btnStart", btnObj));


	std::shared_ptr<AButtonObject> btnObj(new AButtonObject);
	btnObj->m_csName = L"AButtonObject:btnStart";
	btnObj->Init();
	btnObj->m_rtOffset = { 0, 0, 0, 0 };
	btnObj->SetRectDraw({ 0,0, 222, 57}); //334,82
	btnObj->SetPosition(AVector2(0, 0));
	ATexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	ASound* pSound = I_Sound.Load("../../data/Sound/00_Menu.MP3");
	// 가변인자를 통해서 생성자 직접 호출
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	pTex = I_Texture.Load(L"../../data/ui/main_start_pus.png");
	pSound = I_Sound.Load("../../data/Sound/FootStepSound.wav");
	// 가변인자를 통해서 생성자 직접 호출
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	pTex = I_Texture.Load(L"../../data/ui/main_start_sel.png");
	pSound = I_Sound.Load("../../data/Sound/FootStepSound_2.wav");
	// 가변인자를 통해서 생성자 직접 호출
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	pTex = I_Texture.Load(L"../../data/ui/main_start_dis.png");
	pSound = I_Sound.Load("../../data/Sound/PianoSound_00.mp3");
	// 가변인자를 통해서 생성자 직접 호출
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);

	if (!btnObj->Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",
		L"../../data/ui/main_start_nor.png"))
	{
		return false;
	}
	btnObj->SetCollisionType(ACollisionType::Ignore, ASelectType::Select_Overlap);
	I_UI.m_list.insert(std::make_pair(L"btnStart", btnObj));

	//팝업창에 start btn띄우기
	shared_ptr<AUIModelComposed> pComposedObj(new AUIModelComposed);
	pComposedObj->m_csName = L"AUIModelComposed";
	AUIModel* pNewDlgBtn = I_UI.GetPtr(L"btnStart")->Clone();
	pNewDlgBtn->m_csName = L"btnStartClone_com";
	pNewDlgBtn->SetRectDraw({ 0,0, 100,50 });
	pNewDlgBtn->SetPosition(AVector2(0, 0));
	pComposedObj->Add(pNewDlgBtn);
	//pNewDlgBtn->SetPosition(pDlgWindow->m_vPos + AVector2(0, 0));	//팝업창 중앙에 start btn올림
	//pComposedObj->Add(pNewDlgBtn);
	I_UI.m_list.insert(std::make_pair(L"btnStartClone_Composed", pComposedObj));

	return true;
}

bool AIntroWorld::Load(wstring file)
{
	//시작화면에서는 이 음악이 나오도록 ~
	m_pBackGroundMusic = I_Sound.Load("../../data/Sound/Munn.mp3");
	m_pColorTex = I_Texture.Load(L"../../data/Img/stage1_1.png");

	//for (int i = 0; i < 10; i++) //카운트다운
	//{
	//	wstring name = L"../../data/Img/";
	//	name += to_wstring(i);
	//	name += L".bmp";
	//	m_pChangeColorTex[i] = I_Texture.Load(name);
	//}
	CreateModelType();
	
	//intro 배경
	AObject2D* pNewBK = I_UI.GetPtr(L"bk")->Clone();
	pNewBK->m_csName = L"AImageObject:bk";
	pNewBK->SetPosition(AVector2(g_rtClient.right/2, g_rtClient.bottom / 2));
	pNewBK->UpdateData();
	m_UIObj.push_back(shared_ptr<AObject2D>(pNewBK));
	// 프로토타입 디자인 패턴-> 복제를 통해서 객체 생성/ + 컴포짓(Composite패턴)

	////Start버튼2
	//AObject2D* pNewBtn1 =
	//	I_UI.GetPtr(L"btnStart")->Clone();
	//pNewBtn1->m_csName = L"btnStartClone1";
	//pNewBtn1->SetRectDraw({ 0,0, 110,50 });			//UI 출력 사이즈 w,h
	//pNewBtn1->SetPosition(AVector2((g_rtClient.right / 2), (g_rtClient.bottom / 1.35)));
	//pNewBtn1->UpdateData();
	//m_UIObj.push_back(shared_ptr<AObject2D>(pNewBtn1));


	// 프로토타입 디자인 패턴-> 복제를 통해서 객체 생성/ + 컴포짓(Composite패턴)
	/*AObject2D* pNewBtn1 =
		I_UI.GetPtr(L"btnStart")->Clone();
	pNewBtn1->m_csName = L"btnStartClone1";
	pNewBtn1->SetRectDraw({ 0,0, 100,50 });
	pNewBtn1->SetPosition(AVector2(100, 100));
	pNewBtn1->UpdateData();
	m_UIObj.push_back(std::shared_ptr<AObject2D>(pNewBtn1));*/
	//AUIModel* pNewBtn2 = I_UI.GetPtr(L"btnStart")->Clone();
	//pNewBtn2->m_csName = L"btnStartClone2";
	//pNewBtn2->SetRectDraw({ 0,0, 75,45 });
	//pNewBtn2->SetPosition(AVector2(300, 200));
	//pNewBtn2->UpdateData();
	//m_UIObj.push_back(std::shared_ptr<AObject2D>(pNewBtn2));
	//AUIModel* pNewBtn3 = I_UI.GetPtr(L"btnStart")->Clone();
	//pNewBtn3->m_csName = L"btnStartClone3";
	//pNewBtn3->SetRectDraw({ 0,0, 100,50 });
	//pNewBtn3->SetPosition(AVector2(500, 200));
	//pNewBtn3->UpdateData();
	//m_UIObj.push_back(std::shared_ptr<AObject2D>(pNewBtn3));

	AObject2D* pNewBtn1 = I_UI.GetPtr(L"btnStart")->Clone();
	pNewBtn1->m_csName = L"btnStartClone1";
	//pNewBtn1->SetRectDraw({ 0,0, 100,50 });
	pNewBtn1->SetPosition(AVector2(g_rtClient.right/2, g_rtClient.bottom / 1.5));
	pNewBtn1->UpdateData();
	m_UIObj.push_back(shared_ptr<AObject2D>(pNewBtn1));

	//AUIModel* pNewDlgBtnClone = I_UI.GetPtr(L"dlgWindow")->Clone();
	//pNewDlgBtnClone->m_csName = L"AUIModelComposedClone";
	//pNewDlgBtnClone->m_pParent = nullptr;
	//pNewDlgBtnClone->SetPosition(AVector2(0, 0));
	//pNewDlgBtnClone->UpdateData();
	//m_UIObj.push_back(shared_ptr<AObject2D>(pNewDlgBtnClone));




	//이펙트
	I_Sprite.Load(L"SpriteData.txt");
	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");

	m_ExplosionObj.Init();
	m_ExplosionObj.SetPosition(AVector2(0, 0));
	ASprite* pSprite = I_Sprite.GetPtr(L"rtExplosion");
	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	m_ExplosionObj.SetRectDraw({ 50,50, 34, 46 });

	if (!m_ExplosionObj.Create(m_pd3dDevice, m_pContext,
		L"Shader.txt",
		L"../../data/Img/bitmap1.bmp",
		L"../../data/Img/bitmap2.bmp"))
	{
		return false;
	}

	return true;
}
