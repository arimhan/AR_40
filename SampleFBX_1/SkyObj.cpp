#include "SkyObj.h"

void	ASkyObj::SetMatrix(A::AMatrix* matWorld, A::AMatrix* matView, A::AMatrix* matProj)
{
	m_ConstantList.matWorld = m_matWorld.Transpose();
	if (matWorld != nullptr)
	{
		m_ConstantList.matWorld = matWorld->Transpose();
	}
	if (matView != nullptr)
	{
		A::AMatrix matViewSky = *matView;
		matViewSky._41 = 0;
		matViewSky._42 = 0;
		matViewSky._43 = 0;
		m_ConstantList.matView = matViewSky.Transpose();
	}
	if (matProj != nullptr)
	{
		m_ConstantList.matProj = matProj->Transpose();
	}
	UpdateData();
	UpdateCollision();
}


bool ASkyObj::SetVertexData() 
{
	m_VertexList.resize(24); //Box �� 6��, ���� 4�� 6*4 =24
	//���ʴ�� ������ġ, ��ְ�, �÷���, UV : ����Ʈ ���⿡ ���� ����
	
	//m_VertexList.resize(24);
	m_VertexList[0] = AVertex(A::AVector3(-1.0f, 1.0f, -1.0f), A::AVector3(0.0f, 0.0f, -1.0f), A::AVector4(1.0f, 0.0f, 0.0f, 1.0f), A::AVector2(0.0f, 0.0f));
	m_VertexList[1] = AVertex(A::AVector3(1.0f, 1.0f, -1.0f), A::AVector3(0.0f, 0.0f, -1.0f), A::AVector4(1.0f, 0.0f, 0.0f, 1.0f), A::AVector2(1.0f, 0.0f));
	m_VertexList[2] = AVertex(A::AVector3(1.0f, -1.0f, -1.0f), A::AVector3(0.0f, 0.0f, -1.0f), A::AVector4(1.0f, 0.0f, 0.0f, 1.0f), A::AVector2(1.0f, 1.0f));
	m_VertexList[3] = AVertex(A::AVector3(-1.0f, -1.0f, -1.0f), A::AVector3(0.0f, 0.0f, -1.0f), A::AVector4(1.0f, 0.0f, 0.0f, 1.0f), A::AVector2(0.0f, 1.0f));
	// �޸�
	m_VertexList[4] = AVertex(A::AVector3(1.0f, 1.0f, 1.0f), A::AVector3(0.0f, 0.0f, 1.0f), A::AVector4(0.0f, 0.0f, 0.0f, 1.0f), A::AVector2(0.0f, 0.0f));
	m_VertexList[5] = AVertex(A::AVector3(-1.0f, 1.0f, 1.0f), A::AVector3(0.0f, 0.0f, 1.0f), A::AVector4(0.0f, 1.0f, 0.0f, 1.0f), A::AVector2(1.0f, 0.0f));
	m_VertexList[6] = AVertex(A::AVector3(-1.0f, -1.0f, 1.0f), A::AVector3(0.0f, 0.0f, 1.0f), A::AVector4(0.0f, 1.0f, 0.0f, 1.0f), A::AVector2(1.0f, 1.0f));
	m_VertexList[7] = AVertex(A::AVector3(1.0f, -1.0f, 1.0f), A::AVector3(0.0f, 0.0f, 1.0f), A::AVector4(0.0f, 1.0f, 0.0f, 1.0f), A::AVector2(0.0f, 1.0f));

	// ������
	m_VertexList[8] = AVertex(A::AVector3(1.0f, 1.0f, -1.0f), A::AVector3(1.0f, 0.0f, 0.0f), A::AVector4(0.0f, 0.0f, 1.0f, 1.0f), A::AVector2(0.0f, 0.0f));
	m_VertexList[9] = AVertex(A::AVector3(1.0f, 1.0f, 1.0f), A::AVector3(1.0f, 0.0f, 0.0f), A::AVector4(0.0f, 0.0f, 1.0f, 1.0f), A::AVector2(1.0f, 0.0f));
	m_VertexList[10] = AVertex(A::AVector3(1.0f, -1.0f, 1.0f), A::AVector3(1.0f, 0.0f, 0.0f), A::AVector4(0.0f, 0.0f, 1.0f, 1.0f), A::AVector2(1.0f, 1.0f));
	m_VertexList[11] = AVertex(A::AVector3(1.0f, -1.0f, -1.0f), A::AVector3(1.0f, 0.0f, 0.0f), A::AVector4(0.0f, 0.0f, 1.0f, 1.0f), A::AVector2(0.0f, 1.0f));

	// ����
	m_VertexList[12] = AVertex(A::AVector3(-1.0f, 1.0f, 1.0f), A::AVector3(-1.0f, 0.0f, 0.0f), A::AVector4(1.0f, 1.0f, 0.0f, 1.0f), A::AVector2(0.0f, 0.0f));
	m_VertexList[13] = AVertex(A::AVector3(-1.0f, 1.0f, -1.0f), A::AVector3(-1.0f, 0.0f, 0.0f), A::AVector4(1.0f, 1.0f, 0.0f, 1.0f), A::AVector2(1.0f, 0.0f));
	m_VertexList[14] = AVertex(A::AVector3(-1.0f, -1.0f, -1.0f), A::AVector3(-1.0f, 0.0f, 0.0f), A::AVector4(1.0f, 1.0f, 0.0f, 1.0f), A::AVector2(1.0f, 1.0f));
	m_VertexList[15] = AVertex(A::AVector3(-1.0f, -1.0f, 1.0f), A::AVector3(-1.0f, 0.0f, 0.0f), A::AVector4(1.0f, 1.0f, 0.0f, 1.0f), A::AVector2(0.0f, 1.0f));

	// ����
	m_VertexList[16] = AVertex(A::AVector3(-1.0f, 1.0f, 1.0f), A::AVector3(0.0f, 1.0f, 0.0f), A::AVector4(1.0f, 0.5f, 1.0f, 1.0f), A::AVector2(0.0f, 0.0f));
	m_VertexList[17] = AVertex(A::AVector3(1.0f, 1.0f, 1.0f), A::AVector3(0.0f, 1.0f, 0.0f), A::AVector4(1.0f, 0.5f, 1.0f, 1.0f), A::AVector2(1.0f, 0.0f));
	m_VertexList[18] = AVertex(A::AVector3(1.0f, 1.0f, -1.0f), A::AVector3(0.0f, 1.0f, 0.0f), A::AVector4(1.0f, 0.5f, 1.0f, 1.0f), A::AVector2(1.0f, 1.0f));
	m_VertexList[19] = AVertex(A::AVector3(-1.0f, 1.0f, -1.0f), A::AVector3(0.0f, 1.0f, 0.0f), A::AVector4(1.0f, 0.5f, 1.0f, 1.0f), A::AVector2(0.0f, 1.0f));

	// �Ʒ���
	m_VertexList[20] = AVertex(A::AVector3(-1.0f, -1.0f, -1.0f), A::AVector3(0.0f, -1.0f, 0.0f), A::AVector4(0.0f, 1.0f, 1.0f, 1.0f), A::AVector2(0.0f, 0.0f));
	m_VertexList[21] = AVertex(A::AVector3(1.0f, -1.0f, -1.0f), A::AVector3(0.0f, -1.0f, 0.0f), A::AVector4(0.0f, 1.0f, 1.0f, 1.0f), A::AVector2(1.0f, 0.0f));
	m_VertexList[22] = AVertex(A::AVector3(1.0f, -1.0f, 1.0f), A::AVector3(0.0f, -1.0f, 0.0f), A::AVector4(0.0f, 1.0f, 1.0f, 1.0f), A::AVector2(1.0f, 1.0f));
	m_VertexList[23] = AVertex(A::AVector3(-1.0f, -1.0f, 1.0f), A::AVector3(0.0f, -1.0f, 0.0f), A::AVector4(0.0f, 1.0f, 1.0f, 1.0f), A::AVector2(0.0f, 1.0f));

	GenAABB();
	return true;
}
bool ASkyObj::SetIndexData()
{
	m_IndexList.resize(36);	 //Box �� 6�� �� VB 6�� = 6*6= 36
	int iIndex = 0;

	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;


	//VB�� ������ ������ ����
	/*
	m_IndexList[0] = 0;		m_IndexList[6]	= 4;	  m_IndexList[12] = 8;		m_IndexList[18] = 12;	 m_IndexList[24] = 16;		m_IndexList[30] = 20;
	m_IndexList[1] = 1;		m_IndexList[7]	= 5;	  m_IndexList[13] = 9;		m_IndexList[19] = 13;	 m_IndexList[25] = 17;		m_IndexList[31] = 21;
	m_IndexList[2] = 3;		m_IndexList[8]	= 7;	  m_IndexList[14] = 11;		m_IndexList[20] = 15;	 m_IndexList[26] = 19;		m_IndexList[32] = 23;
	m_IndexList[3] = 1;		m_IndexList[9]	= 5;	  m_IndexList[15] = 9;		m_IndexList[21] = 13;	 m_IndexList[27] = 17;		m_IndexList[33] = 21;
	m_IndexList[4] = 2;		m_IndexList[10] = 6;	  m_IndexList[16] = 10;		m_IndexList[22] = 14;	 m_IndexList[28] = 18;		m_IndexList[34] = 22;
	m_IndexList[5] = 3;		m_IndexList[11] = 7;	  m_IndexList[17] = 11;		m_IndexList[23] = 15;	 m_IndexList[29] = 19;		m_IndexList[35] = 23;
	//��						//��						  //��						//��						 //��						//�Ʒ�*/
	return true;
}
bool ASkyObj::LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{
	//m_pTexArray[0] = I_Texture.Load(L"..\\..\\data\\sky\\sky_1\\Sky_00.bmp");	//up
	//m_pTexArray[1] = I_Texture.Load(L"..\\..\\data\\sky\\sky_1\\Sky_01.bmp");	//right
	//m_pTexArray[2] = I_Texture.Load(L"..\\..\\data\\sky\\sky_1\\Sky_02.bmp");	//down
	//m_pTexArray[3] = I_Texture.Load(L"..\\..\\data\\sky\\sky_1\\Sky_03.bmp");	//left
	//m_pTexArray[4] = I_Texture.Load(L"..\\..\\data\\sky\\sky_1\\Sky_04.bmp");	//back
	//m_pTexArray[5] = I_Texture.Load(L"..\\..\\data\\sky\\sky_1\\Sky_05.bmp");	//front

	m_pTexArray[0] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_front.bmp");
	m_pTexArray[1] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_back.bmp");
	m_pTexArray[2] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_right.bmp");
	m_pTexArray[3] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_left.bmp");
	m_pTexArray[4] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_up.bmp");
	m_pTexArray[5] = I_Texture.Load(L"..\\..\\data\\sky\\st00_cm_down.bmp");

	m_pSRVArray[0] = m_pTexArray[0]->m_pSRV;
	m_pSRVArray[1] = m_pTexArray[1]->m_pSRV;
	m_pSRVArray[2] = m_pTexArray[2]->m_pSRV;
	m_pSRVArray[3] = m_pTexArray[3]->m_pSRV;
	m_pSRVArray[4] = m_pTexArray[4]->m_pSRV;
	m_pSRVArray[5] = m_pTexArray[5]->m_pSRV;

	m_pTexCube = I_Texture.Load(szColorFileName);// (L"..\\..\\data\\sky\\skycubemap.dds");

	m_TextureDesc = m_pTexArray[0]->m_TextureDesc;
	return true;
}

bool ASkyObj::Render()
{
	PreRender();
	m_pContext->RSSetState(ADxState::g_pRSNoneCullSolid);
	m_pContext->PSSetSamplers(0, 1, &ADxState::m_pSSLinear);
	m_pContext->PSSetSamplers(1, 1, &ADxState::m_pSSPoint);
	Draw();
	PostRender();
	return true;
}
bool ASkyObj::PostRender() 
{
	//�⺻ ���. m_pTexArray�� �̹����� ������ ����Ѵ�.
	//for (int iTex = 0; iTex < 6; iTex++)
	//{
	//	m_pContext->PSSetShaderResources(0, 1, m_pTexArray[iTex]->m_pSRV.GetAddressOf());
	//	m_pContext->DrawIndexed(6, 6 * iTex, 0);
	//}

	//1�� 
	/*m_pContext->PSSetShaderResources(2, 6, m_pSRVArray[0].GetAddressOf());
	m_pContext->DrawIndexed(36, 0, 0);*/
	
	//2��
	m_pContext->PSSetShaderResources(3, 1, m_pTexCube->m_pSRV.GetAddressOf());
	m_pContext->DrawIndexed(36, 0, 0);

	return true;
}
ASkyObj::ASkyObj() {}
ASkyObj::~ASkyObj() {}