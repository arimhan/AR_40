#include "BoxObj.h"


bool ABoxObj::SetVertexData() 
{
	m_VertexList.resize(24); 
	//Box 면 6개, 정점 4개 6*4 =24
	//차례대로 정점위치, 노멀값, 컬러값, UV : 라이트 방향에 따라 세팅
	int index = 0;
	// +Z plane
	m_VertexList[index].p = A::AVector3(1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(-1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = A::AVector3(-1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// -Z plane
	m_VertexList[++index].p = A::AVector3(-1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(-1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// +X plane
	m_VertexList[++index].p = A::AVector3(1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// -X plane
	m_VertexList[++index].p = A::AVector3(-1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(-1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(-1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = A::AVector3(-1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// -y plane
	m_VertexList[++index].p = A::AVector3(-1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(-1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// +y plane
	m_VertexList[++index].p = A::AVector3(-1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = A::AVector3(-1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = A::AVector3(1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = A::AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);

	GenAABB();
	
	return true;
}
bool ABoxObj::SetIndexData()
{

	m_IndexList.push_back(0);	m_IndexList.push_back(1);	m_IndexList.push_back(2);
	m_IndexList.push_back(2);	m_IndexList.push_back(1);	m_IndexList.push_back(3);
	m_IndexList.push_back(4);	m_IndexList.push_back(5);	m_IndexList.push_back(6);
	m_IndexList.push_back(6);	m_IndexList.push_back(5);	m_IndexList.push_back(7);
	m_IndexList.push_back(8);	m_IndexList.push_back(9);	m_IndexList.push_back(10);
	m_IndexList.push_back(10);	m_IndexList.push_back(9);	m_IndexList.push_back(11);
	m_IndexList.push_back(12);	m_IndexList.push_back(13);	m_IndexList.push_back(14);
	m_IndexList.push_back(14);	m_IndexList.push_back(13);	m_IndexList.push_back(15);
	m_IndexList.push_back(16);	m_IndexList.push_back(17);	m_IndexList.push_back(18);
	m_IndexList.push_back(18);	m_IndexList.push_back(17);	m_IndexList.push_back(19);
	m_IndexList.push_back(20);	m_IndexList.push_back(21);	m_IndexList.push_back(22);
	m_IndexList.push_back(22);	m_IndexList.push_back(21);	m_IndexList.push_back(23);

	return true;
}
bool ABoxObj::PostRender() 
{
	if (m_IndexList.size() <= 0)
	{
		m_pContext->Draw(m_VertexList.size(), 0);
	}
	else
	{
		m_pContext->DrawIndexed(m_IndexList.size(), 0, 0); //DirextXTK -> DirextTexture가 지원함..
	}
	return true;
}


void ABoxObj::DrawDebugRender(ABox* pBox)
{
	//pBox->vList[0] = A::AVector3(pBox->vMin.x, pBox->vMax.y, pBox->vMin.z);
	//pBox->vList[1] = A::AVector3(pBox->vMax.x, pBox->vMax.y, pBox->vMin.z);
	//pBox->vList[2] = A::AVector3(pBox->vMin.x, pBox->vMin.y, pBox->vMin.z);
	//pBox->vList[3] = A::AVector3(pBox->vMax.x, pBox->vMin.y, pBox->vMin.z);
	//pBox->vList[4] = A::AVector3(pBox->vMin.x, pBox->vMax.y, pBox->vMax.z);
	//pBox->vList[5] = A::AVector3(pBox->vMax.x, pBox->vMax.y, pBox->vMax.z);
	//pBox->vList[6] = A::AVector3(pBox->vMin.x, pBox->vMin.y, pBox->vMax.z);
	//pBox->vList[7] = A::AVector3(pBox->vMax.x, pBox->vMin.y, pBox->vMax.z);

	int index = 0;
	//Box에서 돌린 VB 고대로~ 
	// +Z plane 5476
	m_VertexList[index].p = pBox->vList[5];
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[4];
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[7];
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = pBox->vList[6];
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// -Z plane  0123
	m_VertexList[++index].p = pBox->vList[0];
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[1];
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[2];
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = pBox->vList[3];
	m_VertexList[index].n = A::AVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// +X plane  1537
	m_VertexList[++index].p = pBox->vList[1];
	m_VertexList[index].n = A::AVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[5];
	m_VertexList[index].n = A::AVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[3];
	m_VertexList[index].n = A::AVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = pBox->vList[7];
	m_VertexList[index].n = A::AVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// -X plane  4062
	m_VertexList[++index].p = pBox->vList[4];
	m_VertexList[index].n = A::AVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[0];
	m_VertexList[index].n = A::AVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[6];
	m_VertexList[index].n = A::AVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = pBox->vList[2];
	m_VertexList[index].n = A::AVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// -y plane    2367
	m_VertexList[++index].p = pBox->vList[2];
	m_VertexList[index].n = A::AVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[3];
	m_VertexList[index].n = A::AVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[6];
	m_VertexList[index].n = A::AVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = pBox->vList[7];
	m_VertexList[index].n = A::AVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);
	// +y plane     4501
	m_VertexList[++index].p = pBox->vList[4];
	m_VertexList[index].n = A::AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[5];
	m_VertexList[index].n = A::AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 0.0f);
	m_VertexList[++index].p = pBox->vList[0];
	m_VertexList[index].n = A::AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(0.0f, 1.0f);
	m_VertexList[++index].p = pBox->vList[1];
	m_VertexList[index].n = A::AVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = A::AVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = A::AVector2(1.0f, 1.0f);

	//SetMatrix(NULL, &m_pCamera->m_matView, &m_pCamera->m_matProj);
	PreRender();
	Draw();
	m_pContext->UpdateSubresource(
		m_pVertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	PostRender();

}

ABoxObj::ABoxObj() {}
ABoxObj::~ABoxObj() {}