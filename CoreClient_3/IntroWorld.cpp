#include "IntroWorld.h"
#include "Input.h"
#include "ObjectMgr.h"
#include "UIModelMgr.h"


bool	AIntroWorld::CreateModelType()
{
	// INTRO ���
	AShader* pVShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
	AShader* pPShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");
	shared_ptr<AImageObject> obj(new AImageObject);
	obj->m_csName = L"AImageObject:bk";
	obj->Init();
	obj->SetRectDraw({ 0,0, g_rtClient.right,g_rtClient.bottom });
	obj->SetPosition(AVector2(0, 0));
	obj->m_pColorTex = m_pColorTex;
	obj->m_pMaskTex = nullptr;
	obj->m_pVShader = pVShader;
	obj->m_pPShader = pPShader;
	if (!obj->Create(m_pd3dDevice, m_pContext))
	{
		return false;
	}
	obj->SetCollisionType(ACollisionType::Ignore, ASelectType::Select_Ignore);
	I_UI.m_list.insert(make_pair(L"bk", obj));


	//START ��ư (�⺻/����/����/��Ȱ��ȭ)
	shared_ptr<AButtonObject> btnObj(new AButtonObject);
	btnObj->m_csName = L"TButtonObject:btnStart";
	btnObj->Init();
	btnObj->m_rtOffset = { 50, 50, 50, 50 };
	btnObj->SetRectDraw({ 0,0, 0, 0 });//334,82 });
	btnObj->SetPosition(AVector2(0, 0));

	////�⺻
	//ATexture* pTex = I_Texture.Load(L"../../data/ui/main_start_nor.png");
	//ASound* pSound = I_Sound.Load("../../data/Sound/00_Menu.MP3");

	//�⺻
	ATexture* pTex = I_Texture.Load(L"../../data/ui/btnStart.bmp");
	ASound* pSound = I_Sound.Load("../../data/Sound/FootStepSound.wav");
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);

	//���콺 �÷�����
	pTex = I_Texture.Load(L"../../data/ui/btnStart.bmp");
	pSound = I_Sound.Load("../../data/Sound/FootStepSound.wav");
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);

	//����
	pTex = I_Texture.Load(L"../../data/ui/btnStart.bmp");
	pSound = I_Sound.Load("../../data/Sound/FootStepSound.wav");
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	
	//���ÿϷ�(��Ȱ��ȭ)
	pTex = I_Texture.Load(L"../../data/ui/btnStart.bmp");
	pSound = I_Sound.Load("../../data/Sound/FootStepSound.wav");
	btnObj->m_pStatePlayList.emplace_back(pTex, pSound);


	////���콺 �÷�����
	//btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	//pTex = I_Texture.Load(L"../../data/ui/main_start_pus.png");
	//pSound = I_Sound.Load("../../data/Sound/FootStepSound.wav");

	////����
	//btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	//pTex = I_Texture.Load(L"../../data/ui/main_start_sel.png");
	//pSound = I_Sound.Load("../../data/Sound/FootStepSound_2.wav");

	////���ÿϷ�(��Ȱ��ȭ)
	//btnObj->m_pStatePlayList.emplace_back(pTex, pSound);
	//pTex = I_Texture.Load(L"../../data/ui/main_start_dis.png");
	//pSound = I_Sound.Load("../../data/Sound/PianoSound_00.mp3");
	//btnObj->m_pStatePlayList.emplace_back(pTex, pSound);

	if (!btnObj->Create(m_pd3dDevice, m_pContext,
		L"../../data/shader/DefaultUI.txt",
		L"../../data/btnStart.bmp"))
	{
		return false;
	}
	btnObj->SetCollisionType(ACollisionType::Ignore, ASelectType::Select_Overlap);
	I_UI.m_list.insert(make_pair(L"btnStart", btnObj));

	// ���ο� ���� �����ؼ� ����Ѵ�.
	shared_ptr<AUIModelComposed> pComposedObj(new AUIModelComposed);
	pComposedObj->m_csName = L"AUIModelComposed";


	//START ��ư �����ؼ� ����ϰ� �г� �߾ӿ� ��ġ�ϵ��� ����
	AUIModel* pNewDlgBtn = I_UI.GetPtr(L"btnStart")->Clone();
	pNewDlgBtn->m_csName = L"btnStartClone_ComposedList";
	pNewDlgBtn->SetRectDraw({ 0,0, 0,0 });
	pNewDlgBtn->SetPosition(AVector2(0, 0));
	pComposedObj->Add(pNewDlgBtn);
	I_UI.m_list.insert(make_pair(L"dlgWindow", pComposedObj)); 

	return true;
}
bool	AIntroWorld::Init()
{
	AWorld::Init();
	return true;
}
bool	AIntroWorld::Load(std::wstring file)
{	
	m_pColorTex = I_Texture.Load(L"../../data/Img/stage1_1.png");
	CreateModelType();
	
	//��� ���
	AObject2D* pNewBK =	I_UI.GetPtr(L"bk")->Clone();
		pNewBK->m_csName = L"AImageObjectClock:bk";
		pNewBK->SetPosition(AVector2(g_rtClient.right/2, g_rtClient.bottom/2));	//Ŭ���̾�Ʈ ���߾�
		pNewBK->UpdateData();
	m_UIObj.push_back(shared_ptr<AObject2D>(pNewBK));

	// ������Ÿ�� ������ ����-> ������ ���ؼ� ��ü ����/ + ������(Composite����)
	//START ��ư �������� 
	AObject2D* pNewBtn1 =
		I_UI.GetPtr(L"btnStart")->Clone();
		pNewBtn1->m_csName = L"btnStartClone1";

		//pNewBtn1->SetRectSource({ 0,0,0,0 });
		pNewBtn1->SetRectDraw({ 0,0,110,50 });
		pNewBtn1->SetPosition(AVector2(g_rtClient.right / 2, g_rtClient.bottom / 1.3));

		pNewBtn1->UpdateData();
	m_UIObj.push_back(shared_ptr<AObject2D>(pNewBtn1));


	//����Ʈ �ε�
	I_Sprite.Load(L"SpriteData.txt");
	m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");
	m_ExplosionObj.Init();
	m_ExplosionObj.SetPosition(AVector2(400, 500));
	ASprite* pSprite = I_Sprite.GetPtr(L"rtExplosion");
	m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
	m_ExplosionObj.SetRectDraw({ 0,0, 34, 46 });

	if (!m_ExplosionObj.Create(m_pd3dDevice, m_pContext,
		L"Shader.txt",
		L"../../data/Img/bitmap1.bmp",
		L"../../data/Img/bitmap2.bmp"))
	{
		return false;
	}
	return true;
}
bool	AIntroWorld::Frame()
{	
	if (m_bLoadWorld && m_pNextWorld!=nullptr)
	{
		I_ObjectMgr.Release();
		m_pNextWorld->Load(L"ZONE.txt");
		AWorld::m_pCurWorld = m_pNextWorld;
	}
	//m_pBackGroundMusic->Frame();


	//�����ʹ� ���� �浹 �� ��µǵ��� ó���ʿ�
	static int iIndex = 0;

	if (AInput::Get().GetKey(VK_F3) == KEY_PUSH)
	{
		iIndex++;
		if (iIndex >= m_ExplosionObj.m_pSprite->m_rtArray.size())
		{
			iIndex = 0;
		}
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[iIndex]);
			m_ExplosionObj.SetRectDraw({ 0,0,
				m_ExplosionObj.m_pSprite->m_rtArray[iIndex].right,
				m_ExplosionObj.m_pSprite->m_rtArray[iIndex].bottom });
	}
	if (AInput::Get().GetKey(VK_F4) == KEY_PUSH)
	{
		m_ExplosionObj.Reset();
		m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtExplosion");
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
		m_ExplosionObj.SetRectDraw({ 0,0,
			m_ExplosionObj.m_pSprite->m_rtArray[0].right,
			m_ExplosionObj.m_pSprite->m_rtArray[0].bottom });
	}
	if (AInput::Get().GetKey(VK_F6) == KEY_PUSH)
	{
		m_ExplosionObj.Reset();
		m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtBomb");
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
		m_ExplosionObj.SetRectDraw({ 0,0,
			m_ExplosionObj.m_pSprite->m_rtArray[0].right,
			m_ExplosionObj.m_pSprite->m_rtArray[0].bottom });
	}
	if (AInput::Get().GetKey(VK_F7) == KEY_PUSH)
	{
		m_ExplosionObj.Reset();
		m_ExplosionObj.m_pSprite = I_Sprite.GetPtr(L"rtClash");
		m_ExplosionObj.SetRectSource(m_ExplosionObj.m_pSprite->m_rtArray[0]);
		m_ExplosionObj.SetRectDraw({ 0,0,
			m_ExplosionObj.m_pSprite->m_rtArray[0].right,
			m_ExplosionObj.m_pSprite->m_rtArray[0].bottom });
	}
	//m_ExplosionObj.Frame();
	AWorld::Frame();
	return true;
}
bool	AIntroWorld::Render()
{	
	AWorld::Render();
	//m_ExplosionObj.Render();
	return true;
}
bool	AIntroWorld::Release()
{	
	AWorld::Release();
	//m_ExplosionObj.Release();
	return true;
}