#include "BoxObj.h"


bool ABoxObj::SetVertexData() 
{
	m_VertexList.resize(24); 
	//Box 면 6개, 정점 4개 6*4 =24
	//차례대로 정점위치, 노멀값, 컬러값, UV : 라이트 방향에 따라 세팅
	int index = 0;
	// +Z plane
	m_VertexList[index].p = T::TVector3(1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 0.0f, 1.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// -Z plane
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 0.0f, -1.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// +X plane
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// -X plane
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(-1.0f, 0.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// -y plane
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, -1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, -1.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// +y plane
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, 1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_VertexList[++index].p = T::TVector3(-1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_VertexList[++index].p = T::TVector3(1.0f, 1.0f, -1.0f);
	m_VertexList[index].n = T::TVector3(0.0f, 1.0f, 0.0f);
	m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexList[index].t = T::TVector2(1.0f, 1.0f);

	GenAABB();
	//아림Ver 수정 필요.
	////앞면 Front
	//m_VertexList[0] = AVertex(T::TVector3(-1.0f, 1.0f, -1.0f), T::TVector3(0.0f, 0.0f, -1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[1] = AVertex(T::TVector3(1.0f, 1.0f, -1.0f), T::TVector3(0.0f, 0.0f, -1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[2] = AVertex(T::TVector3(1.0f, -1.0f, -1.0f), T::TVector3(0.0f, 0.0f, -1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[3] = AVertex(T::TVector3(-1.0f, -1.0f, -1.0f), T::TVector3(0.0f, 0.0f, -1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));

	////뒷면 Back
	//m_VertexList[4] = AVertex(T::TVector3(-1.0f, 1.0f, 1.0f), T::TVector3(0.0f, 0.0f, 1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[5] = AVertex(T::TVector3(1.0f, 1.0f, 1.0f), T::TVector3(0.0f, 0.0f, 1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[6] = AVertex(T::TVector3(1.0f, -1.0f, 1.0f), T::TVector3(0.0f, 0.0f, 1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[7] = AVertex(T::TVector3(-1.0f, -1.0f, 1.0f), T::TVector3(0.0f, 0.0f, 1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));

	////왼쪽 Left
	//m_VertexList[8] = AVertex(T::TVector3(-1.0f, 1.0f, 1.0f), T::TVector3(-1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[9] = AVertex(T::TVector3(-1.0f, 1.0f, 1.0f), T::TVector3(-1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[10] = AVertex(T::TVector3(-1.0f, -1.0f, -1.0f), T::TVector3(-1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[11] = AVertex(T::TVector3(-1.0f, -1.0f, 1.0f), T::TVector3(-1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));

	////오른쪽 Right
	//m_VertexList[12] = AVertex(T::TVector3(1.0f, 1.0f, -1.0f), T::TVector3(1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[13] = AVertex(T::TVector3(1.0f, 1.0f, 1.0f), T::TVector3(1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[14] = AVertex(T::TVector3(1.0f, -1.0f, 1.0f), T::TVector3(1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[15] = AVertex(T::TVector3(1.0f, -1.0f, -1.0f), T::TVector3(1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));

	////위 Up
	//m_VertexList[16] = AVertex(T::TVector3(-1.0f, 1.0f, 1.0f), T::TVector3(0.0f, 1.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[17] = AVertex(T::TVector3(1.0f, 1.0f, 1.0f), T::TVector3(0.0f, 1.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[18] = AVertex(T::TVector3(1.0f, 1.0f, -1.0f), T::TVector3(0.0f, 1.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[19] = AVertex(T::TVector3(-1.0f, 1.0f, -1.0f), T::TVector3(0.0f, 1.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));

	////아래 Down
	//m_VertexList[20] = AVertex(T::TVector3(-1.0f, -1.0f, 1.0f), T::TVector3(0.0f, -1.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[21] = AVertex(T::TVector3(1.0f, -1.0f, 1.0f), T::TVector3(0.0f, -1.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[22] = AVertex(T::TVector3(1.0f, -1.0f, -1.0f), T::TVector3(0.0f, -1.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//m_VertexList[23] = AVertex(T::TVector3(-1.0f, -1.0f, -1.0f), T::TVector3(0.0f, -1.0f, 0.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	//


	//m_pTexCube = I_Texture.Load(L"../../data/sky/LobbyCube.dds");
	
	return true;
}
bool ABoxObj::SetIndexData()
{

	m_IndexList.push_back(0); m_IndexList.push_back(1); m_IndexList.push_back(2);
	m_IndexList.push_back(2); m_IndexList.push_back(1); m_IndexList.push_back(3);
	m_IndexList.push_back(4); m_IndexList.push_back(5); m_IndexList.push_back(6);
	m_IndexList.push_back(6); m_IndexList.push_back(5); m_IndexList.push_back(7);
	m_IndexList.push_back(8); m_IndexList.push_back(9); m_IndexList.push_back(10);
	m_IndexList.push_back(10); m_IndexList.push_back(9); m_IndexList.push_back(11);
	m_IndexList.push_back(12); m_IndexList.push_back(13); m_IndexList.push_back(14);
	m_IndexList.push_back(14); m_IndexList.push_back(13); m_IndexList.push_back(15);
	m_IndexList.push_back(16); m_IndexList.push_back(17); m_IndexList.push_back(18);
	m_IndexList.push_back(18); m_IndexList.push_back(17); m_IndexList.push_back(19);
	m_IndexList.push_back(20); m_IndexList.push_back(21); m_IndexList.push_back(22);
	m_IndexList.push_back(22); m_IndexList.push_back(21); m_IndexList.push_back(23);

	//아림ver 수정필요
	/*m_IndexList.resize(36);	 //Box 면 6개 당 VB 6개 = 6*6= 36
	//int index = 0;
	//VB랑 동일한 순서로 구성
	m_IndexList[1] = 0;		m_IndexList[7] = 4;		  m_IndexList[13] = 8;		m_IndexList[19] = 12;	 m_IndexList[25] = 16;		m_IndexList[31] = 20;
	m_IndexList[2] = 1;		m_IndexList[8] = 5;		  m_IndexList[14] = 9;		m_IndexList[20] = 13;	 m_IndexList[26] = 17;		m_IndexList[32] = 21;
	m_IndexList[3] = 3;		m_IndexList[9] = 7;		  m_IndexList[15] = 11;		m_IndexList[21] = 15;	 m_IndexList[27] = 19;		m_IndexList[33] = 23;
	m_IndexList[4] = 1;		m_IndexList[10] = 5;	  m_IndexList[16] = 9;		m_IndexList[22] = 13;	 m_IndexList[28] = 17;		m_IndexList[34] = 21;
	m_IndexList[5] = 2;		m_IndexList[11] = 6;	  m_IndexList[17] = 10;		m_IndexList[23] = 14;	 m_IndexList[29] = 18;		m_IndexList[35] = 22;
	m_IndexList[6] = 3;		m_IndexList[12] = 7;	  m_IndexList[18] = 11;		m_IndexList[24] = 15;	 m_IndexList[30] = 19;		m_IndexList[36] = 23;
	//앞						//뒤						  //왼						//오						 //위						//아래*/

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
		//m_pContext->PSSetShaderResources(3, 1, m_pTexCube->m_pSRV.GetAddressOf());
		m_pContext->DrawIndexed(m_IndexList.size(), 0, 0); //DirextXTK -> DirextTexture가 지원함..
	}
	return true;
}

ABoxObj::ABoxObj() {}
ABoxObj::~ABoxObj() {}