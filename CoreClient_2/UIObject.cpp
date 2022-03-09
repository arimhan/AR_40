#include "UIObject.h"
#include "World.h"
#include "SoundMgr.h"

bool AUIObject::Frame()
{
    AObject2D::Frame();
    return true;
}
bool AUIObject::Render()
{
    AObject2D::Render();
    return true;
}
bool AUIObject::SetVertexData()
{
    //ConvertIndex(m_vPos, m_fWidth, m_fHeight, m_VertexList);
    //  0  a   1      2   b   3
    //  c  lt             rt
    //  4      5      6       7
    //
    //  8      9      10      11
    //  d  lb             rb
    //  12    13      14      15

    //사각형을 이등분한다.
    AVector2 vLT = { (float)m_rtOffset.left, (float)m_rtOffset.top };
    AVector2 vRT = { (float)m_rtOffset.right, (float)m_rtOffset.top };
    AVector2 vLB = { (float)m_rtOffset.left, (float)m_rtOffset.bottom };
    AVector2 vRB = { (float)m_rtOffset.right, (float)m_rtOffset.bottom };

    float fWidth = m_fWidth;
    float fHeight = m_fHeight;
    if (m_pColorTex != nullptr)
    {
        fWidth = m_pColorTex->m_TextureDesc.Width;
        fHeight = m_pColorTex->m_TextureDesc.Height;
    }

    AVector2 tLT = { vLT.x / fWidth, vLT.y / fHeight };
    AVector2 tRT = { vRT.x / fWidth, vRT.y / fHeight };
    AVector2 tLB = { vLB.x / fWidth, vLB.y / fHeight };
    AVector2 tRB = { vRT.x / fWidth, vRT.y / fHeight };

    vector<ASimplevertex> list(16);
    float halfWidth = m_fWidth / 2.0f;
    float halfHeight = m_fHeight / 2.0f;
    //0번부터 차례대로 위치계산공식 구현. t는 0~1값이므로 좌측 x좌표쪽은 0, 우측 x좌표쪽은 1으로 설정된다.
    //기준점이 되는 정점 4가지를 먼저 세팅한다.
    list[0].v = { m_vPos.x - halfWidth, m_vPos.y - halfHeight };
    list[0].t = { (float)m_rtOffsetTex.left, (float)m_rtOffsetTex.top };
    //3번은 m_vPos.x좌표를 기준으로 증가이며, t값은 1.0이다.
    list[3].v = { m_vPos.x + halfWidth, m_vPos.y - halfHeight };
    list[3].t = { (float)m_rtOffsetTex.right, (float)m_rtOffsetTex.top };
    list[12].v = { m_vPos.x - halfWidth, m_vPos.y + halfHeight };
    list[12].t = { (float)m_rtOffsetTex.left, (float)m_rtOffsetTex.bottom };
    list[15].v = { m_vPos.x + halfWidth, m_vPos.y + halfHeight };
    list[15].t = { (float)m_rtOffsetTex.right, (float)m_rtOffsetTex.bottom };
    //5번은 list0번을 기준으로 x,y값이 모두 증가된다.

    //그다음 내부 5, 6, 9, 10 정점을 세팅한다. (UI상 픽셀이 늘어나도 되는 부분)
    list[5].v = { list[0].v.x + vLT.x, list[0].v.y + vLT.y };
    list[5].t = { list[0].t.x + tLT.x, list[0].t.y + tLT.y };
    list[6].v = { list[3].v.x - vRT.x, list[3].v.y + vRT.y };
    list[6].t = { list[3].t.x - tRT.x, list[3].t.y + tRT.y };
    list[9].v = { list[12].v.x + vLB.x, list[12].v.y - vLB.y };
    list[9].t = { list[12].t.x + tLB.x, list[12].t.y - tLB.y };
    list[10].v = { list[15].v.x - vRB.x, list[15].v.y - vRB.y };
    list[10].t = { list[15].t.x - tRB.x, list[15].t.y - tRB.y };

    //나머지 정점들을 세팅한다. 해당하는 x,y위치의 구현된 정점을 활용한다.
    list[1].v = { list[5].v.x , list[0].v.y };
    list[1].t = { list[5].t.x , list[0].t.y };

    list[2].v = { list[6].v.x , list[3].v.y };
    list[2].t = { list[6].t.x , list[3].t.y };

    list[4].v = { list[0].v.x , list[5].v.y };
    list[4].t = { list[0].t.x , list[5].t.y };

    list[7].v = { list[3].v.x , list[6].v.y };
    list[7].t = { list[3].t.x , list[6].t.y };

    list[8].v = { list[12].v.x , list[9].v.y };
    list[8].t = { list[12].t.x , list[9].t.y };

    list[11].v = { list[15].v.x , list[10].v.y };
    list[11].t = { list[15].t.x , list[10].t.y };

    list[13].v = { list[9].v.x , list[12].v.y };
    list[13].t = { list[9].t.x , list[12].t.y };

    list[14].v = { list[10].v.x , list[15].v.y };
    list[14].t = { list[10].t.x , list[15].t.y };

    for (int i = 0; i < list.size(); i++)
    {
        list[i].v.x = list[i].v.x / g_rtClient.right;
        list[i].v.y = list[i].v.y / g_rtClient.bottom;

        list[i].v.x = list[i].v.x * 2.0f - 1.0f;
        list[i].v.y = -1.0f * (list[i].v.y * 2.0f - 1.0f);
    }
    m_VertexList = list;
    return true;
}
bool AUIObject::SetIndexData()
{
    m_IndexList.clear();

    //정점을 시계방향 순서대로 1: 0,1,4   2: 4,1,5...로 push_back 한다.
    m_IndexList.push_back(0);   m_IndexList.push_back(1);   m_IndexList.push_back(4);
    m_IndexList.push_back(4);   m_IndexList.push_back(1);   m_IndexList.push_back(5);
    m_IndexList.push_back(1);   m_IndexList.push_back(2);   m_IndexList.push_back(5);
    m_IndexList.push_back(5);   m_IndexList.push_back(2);   m_IndexList.push_back(6);
    m_IndexList.push_back(2);   m_IndexList.push_back(3);   m_IndexList.push_back(6);
    m_IndexList.push_back(6);   m_IndexList.push_back(3);   m_IndexList.push_back(7);

    m_IndexList.push_back(4);   m_IndexList.push_back(5);   m_IndexList.push_back(8);
    m_IndexList.push_back(8);   m_IndexList.push_back(5);   m_IndexList.push_back(9);
    m_IndexList.push_back(5);   m_IndexList.push_back(6);   m_IndexList.push_back(9);
    m_IndexList.push_back(9);   m_IndexList.push_back(6);   m_IndexList.push_back(10);
    m_IndexList.push_back(6);   m_IndexList.push_back(7);   m_IndexList.push_back(10);
    m_IndexList.push_back(10);   m_IndexList.push_back(7);   m_IndexList.push_back(11);

    m_IndexList.push_back(8);   m_IndexList.push_back(9);   m_IndexList.push_back(12);
    m_IndexList.push_back(12);   m_IndexList.push_back(9);   m_IndexList.push_back(13);
    m_IndexList.push_back(9);   m_IndexList.push_back(10);   m_IndexList.push_back(13);
    m_IndexList.push_back(13);   m_IndexList.push_back(10);   m_IndexList.push_back(14);
    m_IndexList.push_back(10);   m_IndexList.push_back(11);   m_IndexList.push_back(14);
    m_IndexList.push_back(14);   m_IndexList.push_back(11);   m_IndexList.push_back(15);

    return true;
}
bool AImageObject::Init()
{
    m_bFadeIn = true;
    return true;
}
bool AImageObject::Frame()
{
    m_vColor.x = m_fAlpha;
    m_vColor.y = m_fAlpha;
    m_vColor.z = m_fAlpha;
    m_vColor.w = 1.0f;
    AObject2D::Frame();
    return true;
}
bool AImageObject::Render()
{
    AObject2D::Render();
    return true;
}
void AButtonObject::HitSelect(ABaseObject* pObj, DWORD dwState)
{
    string state;

    if (m_dwPreSelectState == m_dwSelectState) { return; }
    if (m_pStatePlayList.size() <= 0) return;

    switch (m_dwSelectState)
    {

        case ASelectState::M_DEFAULT:
        {
            if (m_pStatePlayList[0].pTex == nullptr) break;
            m_pColorTex = m_pStatePlayList[0].pTex;
            state += "M_DEFAULT\n";
        }break;
        case ASelectState::M_SELECTED:
        {
            //버튼 M_SELECTED상태일 경우 존 이동처리
            if (m_pStatePlayList[3].pTex == nullptr) break;
            m_pColorTex = m_pStatePlayList[3].pTex;
            m_pStatePlayList[3].pSound->PlayEffect();
            AWorld::m_pCurWorld->m_bLoadWorld = true;
            state += "M_SELECTED\n";
        }break;
        case ASelectState::M_HOVER:
        { 
            //버튼 M_HOVER상태일 경우 존 이동처리
            if (m_pStatePlayList[1].pTex == nullptr) break;
            m_pColorTex = m_pStatePlayList[1].pTex;
            m_pStatePlayList[1].pSound->PlayEffect();
            //state += "M_HOVER\n";
        }break;
        case ASelectState::M_ACTIVE:
        {
            if (m_pStatePlayList[2].pTex == nullptr) break;
            m_pColorTex = m_pStatePlayList[2].pTex;
            m_pStatePlayList[2].pSound->PlayEffect();
            state += "M_ACTIVE\n";
        }break;
        case ASelectState::M_FOCUS:
        {
            if (m_pStatePlayList[2].pTex == nullptr) break;
            m_pColorTex = m_pStatePlayList[2].pTex;
            m_pStatePlayList[2].pSound->PlayEffect();
            //state += "M_FOCUS\n";
        }break;
        default: { state += to_string(m_dwSelectState); }
    }
    m_dwPreSelectState = m_dwSelectState;
    //DisplayText(state.c_str());
}
bool AButtonObject::Init() { return true; }
bool AButtonObject::Frame()
{
    AObject2D::Frame();
    //if (m_dwSelectState == M_DEFAULT)
    //{
    //    //m_pColorTex = m_pStatePlayList[0].pTex;
    //    //m_dwPreSelectState = m_dwSelectState;
    //}

    return true;
}
bool AButtonObject::Render()
{
    AObject2D::Render();
    return true;
}

bool AListCtrlObject::Create(int xCount, int yCount)
{

    UpdateData();

    int iHalfWidth = m_fWidth / xCount;
    int iHalfHeight = m_fHeight / yCount;
    AVector2 pStart = { (float)m_rtDraw.left, (float)m_rtDraw.top };
    pStart.x += m_fWidth / xCount / 2.0f;
    pStart.y += m_fHeight / yCount / 2.0f;
    for (int iCol = 0; iCol < xCount; iCol++)
    {
        for (int iRow = 0; iRow < yCount; iRow++)
        {
            AUIModel* pNewBtn = I_UI.GetPtr(L"btnStart")->Clone();
            pNewBtn->m_pParent = this;
            pNewBtn->m_csName = L"Btn";
            pNewBtn->m_csName += std::to_wstring(iRow * yCount + iCol);
            pNewBtn->SetRectDraw({ 0,0, iHalfWidth,iHalfHeight });
            pNewBtn->SetPosition(AVector2(
                pStart.x + iHalfWidth * iCol,
                pStart.y + iHalfHeight * iRow));
            pNewBtn->UpdateData();
            Add(pNewBtn);
        }
    }
    return true;
}

void AListCtrlObject::HitSelect(ABaseObject* pObj, DWORD dwState)
{
    string state = "\n";
    if (m_dwPreSelectState == m_dwSelectState)
    {
        return;
    }
    m_dwPreSelectState = m_dwSelectState;
    state = std::to_string(m_dwSelectState);
    DisplayText(state.c_str());
}
