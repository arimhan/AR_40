#include "Intro.h"
#include "DxObject.h"
#include "World.h"
//#include "UI.h"

bool AIntro::Load(wstring file)
{
    m_pBGMusic = I_Sound.Load("../../data/Sound/EthanDufault.mp3");
    m_pColorTex = I_Texture.Load(L"../../data/Img/MAINBK.jpg");
    //intro ���

    CreateModelType();
    AObject2D* pNewBK = I_UI.GetPtr(L"bk")->Clone();
    pNewBK->m_csName = L"AImageObjectClock:bk";
    pNewBK->SetPosition(AVector2(400, 300));
    pNewBK->UpdateData();
    m_UIObj.push_back(shared_ptr<AObject2D>(pNewBK));

    //������Ÿ�� ���������� -> ������ ���� ��ü ���� / +������(composite����)
    //�Ʒ� UI���� (Start��ư...��)
    //AObject2D* pNewBtn1 =
    //    I_UI.GetPtr(L"btnStart")->Clone();
    //pNewBtn1->m_csName = L"btnStartClone1";
    //pNewBtn1->SetRectDraw({ 0,0, 100,50 });
    //pNewBtn1->SetPosition(AVector2(300, 25));
    //pNewBtn1->UpdateData();
    //m_UIObj.push_back(shared_ptr<AObject2D>(pNewBtn1));
    //AUIModel* pNewBtn2 = I_UI.GetPtr(L"btnStart")->Clone();
    //pNewBtn2->m_csName = L"btnStartClone2";
    //pNewBtn2->SetRectDraw({ 0,0, 100,100 });
    //pNewBtn2->SetPosition(AVector2(400, 150));
    //pNewBtn2->UpdateData();
    //m_UIObj.push_back(shared_ptr<AObject2D>(pNewBtn2));

    return true;
}

bool AIntro::CreateModelType()
{
    //Load���� �ҷ��� OBJ�� UI/UX�� Type�� ���� ó��
    //����̹���
    AShader* pVSShader = I_Shader.CreateVertexShader(m_pd3dDevice, L"Shader.txt", "VS");
    AShader* pPSShader = I_Shader.CreatePixelShader(m_pd3dDevice, L"Shader.txt", "PSAlphaBlend");
   // AImgObject* pObj = new AImgObject;
    shared_ptr<AImgObject> pObj(new AImgObject);
    pObj->m_csName = L"AImageObject:bk";
    pObj->Init();
    pObj->SetRectDraw({ 0, 0, g_rtClient.right, g_rtClient.bottom }); //client size��� ����� ��
    pObj->SetPosition(AVector2(0, 0)); //0,0��ġ�������� ���
    pObj->m_pColorTex = m_pColorTex;
    pObj->m_pMaskTex = nullptr;
    pObj->m_pVSShader = pVSShader;
    pObj->m_pPSShader = pPSShader;
    if (!pObj->Create(m_pd3dDevice, m_pContext)) 
    { 
        return false; 
    }
    pObj->SetCollisionType(ACollisionType::Ignore, ASelectType::Select_Ignore);
    I_UI.m_list.insert(make_pair(L"bk", pObj));
    //Load���� UI���� ��ư �߰� �� ���⿡�� �߰��� ��.
    
    return true;
}

bool AIntro::Init()
{
    AWorld::Init();
    //m_pBGMusic->Play(true);
    return true;
}

bool AIntro::Frame()
{
    if (m_bLoadZone && m_pNextWorld != nullptr)
    {
        I_ObjectMgr.Release();
        m_pNextWorld->Load(L"zone.txt");
        AWorld::m_pCurWorld = m_pNextWorld;
    }
    m_pBGMusic->Frame();
    //����ȭ���� Intro���� ����� ��� ����
    AWorld::Frame();
    //static int iIndex = 0;
    //if (AInput::Get().GetKey(VK_F2) == KEY_PUSH)
    //{
    //    auto data = m_UIObj.find(L"bk");
    //    if(data!= m_UIObj.end())
    //}

    
    return true;
}

bool AIntro::Render()
{
    AWorld::Render();
    return true;
}

bool AIntro::Release()
{
    AWorld::Release();
    return true;
}
