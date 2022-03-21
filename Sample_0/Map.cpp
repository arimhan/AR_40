#include "Map.h"
#include "WICTextureLoader.h"


bool AMap::CreateHeightMap(const TCHAR* strHeightMapTex)
{
	HRESULT hr;
	ID3D11ShaderResourceView* pSRV = nullptr;
	ComPtr<ID3D11Resource> pTexture;
	size_t maxsize = 0;

	if(FAILED(hr = CreateWICTextureFromFileEx(
		m_pd3dDevice, strHeightMapTex, maxsize, D3D11_USAGE_STAGING, 0,
		D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ, 0, 
		DirectX::WIC_LOADER_DEFAULT, pTexture.GetAddressOf(), nullptr))) 
	{	return false; }
	ID3D11Texture2D* pTexture2D = NULL;
	if(FAILED(pTexture->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D)))
	{	return false;	}

	D3D11_TEXTURE2D_DESC desc;
	pTexture2D->GetDesc(&desc);

	m_fHeightList.resize(desc.Height * desc.Width);

	if (pTexture2D)
	{
		D3D11_MAPPED_SUBRESOURCE MappedFaceDest;
		if (SUCCEEDED(m_pContext->Map((ID3D11Resource*)pTexture2D, 
			D3D11CalcSubresource(0, 0, 1),D3D11_MAP_READ, 0, &MappedFaceDest)))
		{
			UCHAR* pTexels = (UCHAR*)MappedFaceDest.pData;
			AVertex v;
			for (UINT row = 0; row < desc.Height; row++)
			{
				UINT rowStart = row * MappedFaceDest.RowPitch;
				for (UINT col = 0; col < desc.Width; col++)
				{
					UINT colStart = col * 4;
					UINT uRed = pTexels[rowStart + colStart + 0];
					m_fHeightList[row * desc.Width + col] = (float)uRed; // DWORD 이므로  pitch / 4
				}
			}
			m_pContext->Unmap(pTexture2D, D3D11CalcSubresource(0, 0, 1));
		}
	}
	m_iNumRows = desc.Height;
	m_iNumCols = desc.Width;

	if (pTexture2D) pTexture2D->Release();
	return true;
}
bool AMap::CreateMap(UINT width, UINT height, float fDistance) 
{
	//맵 만들때 필요한 애들 설정
	m_iNumCols = width;
	m_iNumRows = height;
	m_iCellDistance = fDistance;
	m_iNumVertices = m_iNumCols * m_iNumRows;
	m_iNumCellCols = m_iNumCols - 1;
	m_iNumCellRows = m_iNumRows - 1;
	m_iNumFaces = m_iNumCellCols * m_iNumCellRows * 2;

	return true;
}
bool AMap::SetVertexData() 
{
	m_VertexList.resize(m_iNumVertices);
	//VertexData를 세팅한다. 
	float hHalfCol = (m_iNumCols - 1) / 2.0f;
	float hHalfRow = (m_iNumRows - 1) / 2.0f;
	float ftxOffsetU = 1.0f / (m_iNumCols - 1);
	float ftxOffsetV = 1.0f / (m_iNumRows - 1);

	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int index = iRow * m_iNumCols + iCol;
			//정점리스트 내 pnct 값 세팅
			m_VertexList[index].p.x = (iCol - hHalfCol) * m_iCellDistance;
			m_VertexList[index].p.y = m_fHeightList[index];
			m_VertexList[index].p.z = -((iRow - hHalfRow)* m_iCellDistance); // 음수값이라 +로 변환
			m_VertexList[index].n = AVector3( 0, 1, 0);	//노멀값이 Y축으로 1값을 향하고 있음.
			m_VertexList[index].c =
				AVector4(randstep(0.0f, 1.0f), randstep(0.0f, 1.0f), randstep(0.0f, 1.0f), 1);
				//컬러(조명)을 랜덤으로 지정
			m_VertexList[index].t = AVector2(ftxOffsetU * iCol, ftxOffsetV * iRow);
			//원래는 1,1인데, 텍스쳐 1장을 전체에 바르기 때문에 위와 같이 행, 열의 사이즈대로 입힌다.
		}
	}
	return true;
}
bool AMap::SetIndexData() 
{
	//IndexData를 세팅한다.
	m_IndexList.resize(m_iNumFaces * 3); //Face는 index가 3개씩 들어가는데....잘 이해가 안감.
	UINT iIndex = 0;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			m_IndexList[iIndex + 0] = iRow * m_iNumCols + iCol;
			m_IndexList[iIndex + 1] = (iRow * m_iNumCols + iCol) + 1;
			m_IndexList[iIndex + 2] = (iRow + 1) * m_iNumCols + iCol;

			m_IndexList[iIndex + 3] = m_IndexList[iIndex + 2];
			m_IndexList[iIndex + 4] = m_IndexList[iIndex + 1];
			m_IndexList[iIndex + 5] = m_IndexList[iIndex + 2] + 1;

			iIndex += 6;
		}
	}

	//다시 iIndex를 초기화 한 뒤 이번엔 vLight를 세팅해준다.
	iIndex = 0;
	AVector3 vLight(100, 100, 0);
	vLight = vLight.Normal() * 1.0f;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			//0 Face부터 세팅
			AFace face;
			face.v0 = m_IndexList[iIndex + 0];
			face.v1 = m_IndexList[iIndex + 1];
			face.v2 = m_IndexList[iIndex + 2];

			AVector3 vNormal;
			//노말벡터 vE0과 E1 2개가 있을 때, E0은 디렉션 1-0, E1는 디렉션 2-0을 빼면 노말벡터를 구할 수 있다.
			AVector3 vE0 = (m_VertexList[face.v1].p - m_VertexList[face.v0].p).Normal();
			AVector3 vE1 = (m_VertexList[face.v2].p - m_VertexList[face.v0].p).Normal();
			//위에서 구한 vE0과 vE1를 외적 후 정규화 한다.
			face.vNormal = (vE0 ^ vE1).Normal();

			m_VertexList[face.v0].n += face.vNormal;
			m_VertexList[face.v1].n += face.vNormal;
			m_VertexList[face.v2].n += face.vNormal;

			float fDot = max(0.0f, vLight | face.vNormal);
			m_VertexList[face.v0].c = AVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v1].c = AVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = AVector4(fDot, fDot, fDot, 1);
			m_vFaceList.push_back(face);

			// 1Face
			face.v0 = m_IndexList[iIndex + 3];
			face.v1 = m_IndexList[iIndex + 4];
			face.v2 = m_IndexList[iIndex + 5];
			vE0 = (m_VertexList[face.v1].p - m_VertexList[face.v0].p).Normal();
			vE1 = (m_VertexList[face.v2].p - m_VertexList[face.v0].p).Normal();
			face.vNormal = (vE0 ^ vE1).Normal();

			m_VertexList[face.v0].n += face.vNormal;
			m_VertexList[face.v1].n += face.vNormal;
			m_VertexList[face.v2].n += face.vNormal;

			fDot = max(0.0f, vLight | face.vNormal);
			m_VertexList[face.v0].c = AVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v1].c = AVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = AVector4(fDot, fDot, fDot, 1);
			m_vFaceList.push_back(face);

			iIndex += 6;
		}
	}
	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			//정점의 iRow * m_iNumCols + iCol의 노멀성분을 정규화 한다.
			m_VertexList[iRow * m_iNumCols + iCol].n.Normalize();
			float fDot = max(0.0f, vLight | m_VertexList[iRow * m_iNumCols + iCol].n);
			m_VertexList[iRow * m_iNumCols + iCol].c = AVector4(fDot, fDot, fDot, 1);
		}
	}
	return true;

}
bool AMap::Frame() 
{
	//깊이맵 만들때 필요한 vLight 지정
	AVector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);
	vLight = vLight.Normal() * -1.0f;

	//이름만 Color. 실제론 vLight의 값이 들어가있다. Light가 g_fGameTimer에 따라 움직인다.
	m_ConstantList.Color.x = vLight.x;
	m_ConstantList.Color.y = vLight.y;
	m_ConstantList.Color.z = vLight.z;
	m_ConstantList.Color.w = 1.0f;
	
	return true;
}

AMap::AMap() {}
AMap::~AMap() {}
