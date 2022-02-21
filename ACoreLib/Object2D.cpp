#include "Object2D.h"

void AObject2D::SetRectSource(RECT rt) { m_rtSource = rt; }
void AObject2D::SetRectDraw(RECT rt)
{
	m_rtDraw = rt;
	m_fWidth = rt.right;
	m_fHeight = rt.bottom;
}
void AObject2D::AddPosition(AVector2 vPos)
{
	m_vPos += vPos;
	m_rtCollision = ARect(m_vPos, m_fWidth, m_fHeight);
	Convert(m_vPos, m_fWidth, m_fHeight, m_VertexList);
	m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
}
void AObject2D::SetPosition(AVector2 vPos)
{
	m_vPos = vPos;
}
void AObject2D::UpDateRectDraw(RECT rt)
{
	m_fWidth = rt.right;
	m_fHeight = rt.bottom;
}
void AObject2D::Convert(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList)
{
	//화면좌표 위치를 중심으로 NDC 변환
	//(0,0)부터 시계방향으로 0,1,2
	//2번부터 3,4,5
	vector<ASimplevertex> list(6);
	float halfWidth = fWidth / 2.0f;
	float halfHeight = fHeight / 2.0f;

	list[0].v = { center.x - halfWidth, center.y - halfHeight };
	list[1].v = { center.x + halfWidth, center.y - halfHeight };
	list[2].v = { center.x - halfWidth, center.y + halfHeight };

	list[3].v = list[2].v;
	list[4].v = list[1].v;
	//(0,0)을 기준으로
	list[5].v = { center.x + halfWidth, center.y + halfHeight };
	Convert(list, retList);
}
void AObject2D::ConvertIndex(AVector2 center, float fWidth, float fHeight, vector<ASimplevertex>& retList)
{
	//사각형, 정점버퍼4개
	vector<ASimplevertex> list(4);
	float halfWidth = fWidth / 2.0f;
	float halfHeight = fHeight / 2.0f;

	list[0].v = { center.x - halfWidth, center.y - halfHeight };
	list[1].v = { center.x + halfWidth, center.y - halfHeight };
	list[2].v = { center.x - halfWidth, center.y + halfHeight };
	list[3].v = { center.x + halfWidth, center.y + halfHeight };
	ConvertIndex(list, retList);
}
void AObject2D::Convert(vector<ASimplevertex>& list, vector<ASimplevertex>& retList)
{
	//화면좌표계를 NDC로 변환
	retList.resize(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		// 0~ 800 -> 0~1 -> -1 ~ +1
		retList[i].v.x = list[i].v.x / g_rtClient.right;
		retList[i].v.y = list[i].v.y / g_rtClient.bottom;

		// 0 ~ 1 -> -1 ~ +1 .... -1 ~ +1 -> 0 ~ 1
		// x = x * 2 + -1  .... x = x * 0.5f + 0.5f
		retList[i].v.x = retList[i].v.x * 2.0f - 1.0f;
		retList[i].v.y = -1.0f * (retList[i].v.y * 2.0f - 1.0f);
	}
	m_rtSource.left = 0;		m_rtSource.right = 0;
	m_rtSource.top = 0;			m_rtSource.bottom = 0;
	if (m_rtSource.left == 0 && m_rtSource.right == 0 && m_rtSource.top == 0 && m_rtSource.bottom == 0)
		//m_rtSource의 상하좌우 값이 0일때
	{
		retList[0].t.x = 0.0f;			retList[0].t.y = 0.0f;	//v0
		retList[1].t.x = 1.0f;			retList[1].t.y = 0.0f;	//v1
		retList[2].t.x = 0.0f;			retList[2].t.y = 1.0f;
		retList[3].t = retList[2].t;	
		retList[4].t = retList[1].t;	
		retList[5].t.x = 1.0f;			retList[5].t.y = 1.0f;
	}
	else
	{
		float u = m_rtSource.left / (float)m_TextureDesc.Width;
		float v = m_rtSource.top / (float)m_TextureDesc.Height;
		float w = m_rtSource.right / (float)m_TextureDesc.Width;
		float h = m_rtSource.bottom / (float)m_TextureDesc.Height;
		retList[0].t.x = u;				retList[0].t.y = v;		//v0
		retList[1].t.x = u + w;			retList[1].t.y = v;		//v1
		retList[2].t.x = u;				retList[2].t.y = v + h;
		retList[3].t = retList[2].t;
		retList[4].t = retList[1].t;
		retList[5].t.x = u + w;			retList[5].t.y = v + h;
	}
}
void AObject2D::ConvertIndex(vector<ASimplevertex>& list, vector<ASimplevertex>& retList)
{
	retList.resize(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		// 0 ~ 800 -> 0 ~ 1 -> -1 ~ +1
		retList[i].v.x = list[i].v.x / g_rtClient.right;
		retList[i].v.y = list[i].v.y / g_rtClient.bottom;

		// 0 ~ 1 -> -1 ~ +1 :::: -1 ~ +1 -> 0 ~ 1
		// x = x * 2 + -1 ; :::: x = x * 0.5f + 0.5f
		retList[i].v.x = retList[i].v.x * 2.0f - 1.0f;
		retList[i].v.y = -1.0f * (retList[i].v.y * 2.0f - 1.0f);
	}
	// 91, 1, 42, 56 => 0 ~ 1
	m_rtSource.left = 0;		m_rtSource.right = 0;
	m_rtSource.top = 0;			m_rtSource.bottom = 0;

	if (m_rtSource.left == 0 && m_rtSource.right == 0 && m_rtSource.top == 0 && m_rtSource.bottom == 0)
		//m_rtSource의 상하좌우 값이 0일때
	{
		retList[0].t.x = 0.0f;		retList[0].t.y = 0.0f;	//v0
		retList[1].t.x = 1.0f;		retList[1].t.y = 0.0f;	//v1
		retList[2].t.x = 0.0f;		retList[2].t.y = 1.0f;	
		retList[3].t.x = 1.0f;		retList[3].t.y = 1.0f;	
	}
	else
	{
		float u = m_rtSource.left	/ (float)m_TextureDesc.Width;
		float v = m_rtSource.top	/ (float)m_TextureDesc.Height;
		float w = m_rtSource.right	/ (float)m_TextureDesc.Width;
		float h = m_rtSource.bottom	/ (float)m_TextureDesc.Width;
		retList[0].t.x = u;			retList[0].t.y = v; //v0
		retList[1].t.x = u + w;		retList[1].t.y = v; //v1
		retList[2].t.x = u;			retList[2].t.y = v + h; 
		retList[3].t.x = u + w;		retList[3].t.y = v + h; 
	}
}
bool AObject2D::SetVertexData()
{
	Convert(m_vPos, m_fWidth, m_fHeight, m_VertexList);
	return true;
}

bool AObject2D::SetIndexData()
{
	m_IndexList.push_back(0);	m_IndexList.push_back(1);	 m_IndexList.push_back(2);
	m_IndexList.push_back(2);	m_IndexList.push_back(1);	 m_IndexList.push_back(3);
	return true;
}
