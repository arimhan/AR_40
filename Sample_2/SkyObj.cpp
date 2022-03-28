#include "SkyObj.h"


bool ASkyObj::SetVertexData() 
{
	m_VertexList.resize(24); //Box 면 6개, 정점 4개 6*4 =24
	//차례대로 정점위치, 노멀값, 컬러값, UV : 라이트 방향에 따라 세팅
	
	m_VertexList[0] = AVertex(T::TVector3(-1.0f, 1.0f, -1.0f), T::TVector3(0.0f, 0.0f, -1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	m_VertexList[1] = AVertex(T::TVector3(1.0f, 1.0f, -1.0f), T::TVector3(0.0f, 0.0f, -1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(1.0f, 0.0f));
	m_VertexList[2] = AVertex(T::TVector3(1.0f, -1.0f, -1.0f), T::TVector3(0.0f, 0.0f, -1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(1.0f, 1.0f));
	m_VertexList[3] = AVertex(T::TVector3(-1.0f, -1.0f, -1.0f), T::TVector3(0.0f, 0.0f, -1.0f), T::TVector4(1.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 1.0f));
	// 뒷면
	m_VertexList[4] = AVertex(T::TVector3(1.0f, 1.0f, 1.0f), T::TVector3(0.0f, 0.0f, 1.0f), T::TVector4(0.0f, 0.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	m_VertexList[5] = AVertex(T::TVector3(-1.0f, 1.0f, 1.0f), T::TVector3(0.0f, 0.0f, 1.0f), T::TVector4(0.0f, 1.0f, 0.0f, 1.0f), T::TVector2(1.0f, 0.0f));
	m_VertexList[6] = AVertex(T::TVector3(-1.0f, -1.0f, 1.0f), T::TVector3(0.0f, 0.0f, 1.0f), T::TVector4(0.0f, 1.0f, 0.0f, 1.0f), T::TVector2(1.0f, 1.0f));
	m_VertexList[7] = AVertex(T::TVector3(1.0f, -1.0f, 1.0f), T::TVector3(0.0f, 0.0f, 1.0f), T::TVector4(0.0f, 1.0f, 0.0f, 1.0f), T::TVector2(0.0f, 1.0f));

	// 오른쪽
	m_VertexList[8] = AVertex(T::TVector3(1.0f, 1.0f, -1.0f), T::TVector3(1.0f, 0.0f, 0.0f), T::TVector4(0.0f, 0.0f, 1.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	m_VertexList[9] = AVertex(T::TVector3(1.0f, 1.0f, 1.0f), T::TVector3(1.0f, 0.0f, 0.0f), T::TVector4(0.0f, 0.0f, 1.0f, 1.0f), T::TVector2(1.0f, 0.0f));
	m_VertexList[10] = AVertex(T::TVector3(1.0f, -1.0f, 1.0f), T::TVector3(1.0f, 0.0f, 0.0f), T::TVector4(0.0f, 0.0f, 1.0f, 1.0f), T::TVector2(1.0f, 1.0f));
	m_VertexList[11] = AVertex(T::TVector3(1.0f, -1.0f, -1.0f), T::TVector3(1.0f, 0.0f, 0.0f), T::TVector4(0.0f, 0.0f, 1.0f, 1.0f), T::TVector2(0.0f, 1.0f));

	// 왼쪽
	m_VertexList[12] = AVertex(T::TVector3(-1.0f, 1.0f, 1.0f), T::TVector3(-1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 1.0f, 0.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	m_VertexList[13] = AVertex(T::TVector3(-1.0f, 1.0f, -1.0f), T::TVector3(-1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 1.0f, 0.0f, 1.0f), T::TVector2(1.0f, 0.0f));
	m_VertexList[14] = AVertex(T::TVector3(-1.0f, -1.0f, -1.0f), T::TVector3(-1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 1.0f, 0.0f, 1.0f), T::TVector2(1.0f, 1.0f));
	m_VertexList[15] = AVertex(T::TVector3(-1.0f, -1.0f, 1.0f), T::TVector3(-1.0f, 0.0f, 0.0f), T::TVector4(1.0f, 1.0f, 0.0f, 1.0f), T::TVector2(0.0f, 1.0f));

	// 윗면
	m_VertexList[16] = AVertex(T::TVector3(-1.0f, 1.0f, 1.0f), T::TVector3(0.0f, 1.0f, 0.0f), T::TVector4(1.0f, 0.5f, 1.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	m_VertexList[17] = AVertex(T::TVector3(1.0f, 1.0f, 1.0f), T::TVector3(0.0f, 1.0f, 0.0f), T::TVector4(1.0f, 0.5f, 1.0f, 1.0f), T::TVector2(1.0f, 0.0f));
	m_VertexList[18] = AVertex(T::TVector3(1.0f, 1.0f, -1.0f), T::TVector3(0.0f, 1.0f, 0.0f), T::TVector4(1.0f, 0.5f, 1.0f, 1.0f), T::TVector2(1.0f, 1.0f));
	m_VertexList[19] = AVertex(T::TVector3(-1.0f, 1.0f, -1.0f), T::TVector3(0.0f, 1.0f, 0.0f), T::TVector4(1.0f, 0.5f, 1.0f, 1.0f), T::TVector2(0.0f, 1.0f));

	// 아랫면
	m_VertexList[20] = AVertex(T::TVector3(-1.0f, -1.0f, -1.0f), T::TVector3(0.0f, -1.0f, 0.0f), T::TVector4(0.0f, 1.0f, 1.0f, 1.0f), T::TVector2(0.0f, 0.0f));
	m_VertexList[21] = AVertex(T::TVector3(1.0f, -1.0f, -1.0f), T::TVector3(0.0f, -1.0f, 0.0f), T::TVector4(0.0f, 1.0f, 1.0f, 1.0f), T::TVector2(1.0f, 0.0f));
	m_VertexList[22] = AVertex(T::TVector3(1.0f, -1.0f, 1.0f), T::TVector3(0.0f, -1.0f, 0.0f), T::TVector4(0.0f, 1.0f, 1.0f, 1.0f), T::TVector2(1.0f, 1.0f));
	m_VertexList[23] = AVertex(T::TVector3(-1.0f, -1.0f, 1.0f), T::TVector3(0.0f, -1.0f, 0.0f), T::TVector4(0.0f, 1.0f, 1.0f, 1.0f), T::TVector2(0.0f, 1.0f));

	return true;
}
bool ASkyObj::SetIndexData()
{
	m_IndexList.resize(36);	 //Box 면 6개 당 VB 6개 = 6*6= 36
	int iIndex = 0;

	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;


	//VB랑 동일한 순서로 구성
	/*
	m_IndexList[0] = 0;		m_IndexList[6]	= 4;	  m_IndexList[12] = 8;		m_IndexList[18] = 12;	 m_IndexList[24] = 16;		m_IndexList[30] = 20;
	m_IndexList[1] = 1;		m_IndexList[7]	= 5;	  m_IndexList[13] = 9;		m_IndexList[19] = 13;	 m_IndexList[25] = 17;		m_IndexList[31] = 21;
	m_IndexList[2] = 3;		m_IndexList[8]	= 7;	  m_IndexList[14] = 11;		m_IndexList[20] = 15;	 m_IndexList[26] = 19;		m_IndexList[32] = 23;
	m_IndexList[3] = 1;		m_IndexList[9]	= 5;	  m_IndexList[15] = 9;		m_IndexList[21] = 13;	 m_IndexList[27] = 17;		m_IndexList[33] = 21;
	m_IndexList[4] = 2;		m_IndexList[10] = 6;	  m_IndexList[16] = 10;		m_IndexList[22] = 14;	 m_IndexList[28] = 18;		m_IndexList[34] = 22;
	m_IndexList[5] = 3;		m_IndexList[11] = 7;	  m_IndexList[17] = 11;		m_IndexList[23] = 15;	 m_IndexList[29] = 19;		m_IndexList[35] = 23;
	//앞						//뒤						  //왼						//오						 //위						//아래*/
	return true;
}
bool ASkyObj::LoadTexture(const TCHAR* szColorFileName, const TCHAR* szMaskFileName)
{
	m_pTexArray[0] = I_Texture.Load(L"../../data/sky/sky_1/Sky_00.bmp");	//up
	m_pTexArray[1] = I_Texture.Load(L"../../data/sky/sky_1/Sky_01.bmp");	//right
	m_pTexArray[2] = I_Texture.Load(L"../../data/sky/sky_1/Sky_02.bmp");	//down
	m_pTexArray[3] = I_Texture.Load(L"../../data/sky/sky_1/Sky_03.bmp");	//left
	m_pTexArray[4] = I_Texture.Load(L"../../data/sky/sky_1/Sky_04.bmp");	//back
	m_pTexArray[5] = I_Texture.Load(L"../../data/sky/sky_1/Sky_05.bmp");	//front

	m_pSRVArray[0] = m_pTexArray[0]->m_pSRV;
	m_pSRVArray[1] = m_pTexArray[1]->m_pSRV;
	m_pSRVArray[2] = m_pTexArray[2]->m_pSRV;
	m_pSRVArray[3] = m_pTexArray[3]->m_pSRV;
	m_pSRVArray[4] = m_pTexArray[4]->m_pSRV;
	m_pSRVArray[5] = m_pTexArray[5]->m_pSRV;

	m_pTexCube = I_Texture.Load(L"../../data/sky/skycubemap.dds");

	m_TextureDesc = m_pTexArray[0]->m_TextureDesc;
	return true;
}
bool ASkyObj::PostRender() 
{
	//기본 방법. m_pTexArray에 이미지를 저장해 출력한다.
	//for (int iTex = 0; iTex < 6; iTex++)
	//{
	//	m_pContext->PSSetShaderResources(0, 1, m_pTexArray[iTex]->m_pSRV.GetAddressOf());
	//	m_pContext->DrawIndexed(6, 6 * iTex, 0);
	//}

	//1번 
	/*m_pContext->PSSetShaderResources(2, 6, m_pSRVArray[0].GetAddressOf());
	m_pContext->DrawIndexed(36, 0, 0);*/
	
	//2번
	m_pContext->PSSetShaderResources(3, 1, m_pTexCube->m_pSRV.GetAddressOf());
	m_pContext->DrawIndexed(36, 0, 0);

	return true;
}
ASkyObj::ASkyObj() {}
ASkyObj::~ASkyObj() {}