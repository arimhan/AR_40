#include "Map.h"
#include "WICTextureLoader.h"

float AMap::GetHeight(float fPosX, float fPosZ) 
{
	//ObJ와 Map의 높이값을 얻어오는 함수, 선형보간 함수기능을 구현한다.
	//fPosX / fPosZ 의 위치에 해당하는 높이맵셀을 찾는다.
	//m_iNumCols와 m_iNumRows은 가로/세로의 실제 크기값이다.

	float fCellX = (float)(m_iNumCellCols * m_iCellDistance / 2.0f + fPosX);
	float fCellZ = (float)(m_iNumCellRows * m_iCellDistance / 2.0f - fPosZ);

	//셀의 크기로 나누어 0~1 단위의 값으로 바꾸어 높이맵 배열에 접근한다.
	fCellX /= (float)m_iCellDistance;		fCellZ /= (float)m_iCellDistance;

	//fCellX, fCellZ 값보다 작거나 같은 최대 정수(소수부분) 을 잘라낸다.
	float fVertexCol = ::floorf(fCellX);	float fVertexRow = ::floorf(fCellZ);

	//높이맵 범위를 벗어나면 강제로 초기화 한다.
	if (fVertexCol < 0.0f) fVertexCol = 0.0f;
	if (fVertexRow < 0.0f) fVertexRow = 0.0f;
	if ((float)(m_iNumCols - 2) < fVertexCol) fVertexCol = (float)(m_iNumCols - 2);
	if ((float)(m_iNumRows - 2) < fVertexRow) fVertexRow = (float)(m_iNumRows - 2);


	//계산된 셀의 플랜을 구성하는 4개 정점의 높이값을 찾는다.
	//A가 원점이 되어 좌측 상단, 시계방향으로 A->B->D->C 순으로 구성
	//  A   B
	//  *---*
	//  | / |
	//  *---*  
	//  C   D

	float A = GetHeightMap((int)fVertexRow,		(int)fVertexCol);
	float B = GetHeightMap((int)fVertexRow,		(int)fVertexCol + 1);
	float C = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol);
	float D = GetHeightMap((int)fVertexRow + 1, (int)fVertexCol + 1);

	//A정점의 위치에서 떨어진 값(변위값)을 계산한다. 0 ~ 1.0f
	float fDeltaX = fCellX - fVertexCol;
	float fDeltaZ = fCellZ - fVertexRow;

	//보간작업을 위한 기준 Face를 찾는다.
	float fHeight = 0.0f;
	//위 Face를 기준으로 보간한다.  ABD
	//fDeltaZ + fDeltaX < 1.0f;
	if (fDeltaZ < (1.0f - fDeltaX))
	{
		float uy = B - A;	//A->B
		float vy = C - A;	//A->C
		//두 정점의 높이값의 차이를 비교하여 델타X의 값에 따라 보간값을 찾는다.
		fHeight = A + Lerp(0.0f, uy, fDeltaX) + Lerp(0.0f, vy, fDeltaZ);
	}
	//아래페이스를 기준으로 보간한다. DCB
	else
	{
		float uy = C - D;
		float vy = B - D;
		fHeight = D + Lerp(0.0f, uy, 1.0f - fDeltaX) + Lerp(0.0f, vy, 1.0f - fDeltaZ);
	}
	return fHeight;
}
float AMap::GetHeight(int index) { return m_fHeightList[index]; }

float AMap::GetHeightMap(int row, int col) 
{
	return m_VertexList[row * m_iNumRows + col].p.y;
}
//Linear Interpolation 선형보간함수
float AMap::Lerp(float fStart, float fEnd, float fTangent) 
{
	return fStart - (fStart * fTangent) + (fEnd * fTangent);
}

//--------------------------HeightMap 기능 구현

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

	m_BoxCollision.vMax.x = (m_iNumCols / 2 * m_iCellDistance);
	m_BoxCollision.vMin.x = -m_BoxCollision.vMax.x;
	m_BoxCollision.vMax.z = (m_iNumRows / 2 * m_iCellDistance);
	m_BoxCollision.vMin.z = -m_BoxCollision.vMax.z;

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
			m_VertexList[index].n = T::TVector3( 0, 1, 0);	//노멀값이 Y축으로 1값을 향하고 있음.
			m_VertexList[index].c =
				T::TVector4(randstep(0.0f, 1.0f), randstep(0.0f, 1.0f), randstep(0.0f, 1.0f), 1);
				//컬러(조명)을 랜덤으로 지정
			m_VertexList[index].t = T::TVector2(ftxOffsetU * iCol, ftxOffsetV * iRow);
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
	T::TVector3 vLight(100, 100, 0);
	T::D3DXVec3Normalize(&vLight, &vLight);
	vLight = vLight * 1.0f;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			//0 Face부터 세팅
			AFace face;
			face.v0 = m_IndexList[iIndex + 0];
			face.v1 = m_IndexList[iIndex + 1];
			face.v2 = m_IndexList[iIndex + 2];

			T::TVector3 vNormal;
			//노말벡터 vE0과 E1 2개가 있을 때, E0은 디렉션 1-0, E1는 디렉션 2-0을 빼면 노말벡터를 구할 수 있다.
			T::TVector3 vE0 = (m_VertexList[face.v1].p - m_VertexList[face.v0].p);
			T::D3DXVec3Normalize(&vE0, &vE0);
			T::TVector3 vE1 = (m_VertexList[face.v2].p - m_VertexList[face.v0].p);
			//위에서 구한 vE0과 vE1를 외적 후 정규화 한다.
			T::D3DXVec3Normalize(&vE0, &vE1);
			//face.vNormal = (vE0 ^ vE1).Normal(); 아래 함수를 이용하여 구현
			T::D3DXVec3Cross(&face.vNormal, &vE0, &vE1);
			T::D3DXVec3Normalize(&face.vNormal, &face.vNormal);

			m_VertexList[face.v0].n += face.vNormal;
			m_VertexList[face.v1].n += face.vNormal;
			m_VertexList[face.v2].n += face.vNormal;

			float fDot = max(0.0f, T::D3DXVec3Dot(&vLight , &face.vNormal));
			m_VertexList[face.v0].c = T::TVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v1].c = T::TVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = T::TVector4(fDot, fDot, fDot, 1);
			m_vFaceList.push_back(face);

			// 1Face
			face.v0 = m_IndexList[iIndex + 3];
			face.v1 = m_IndexList[iIndex + 4];
			face.v2 = m_IndexList[iIndex + 5];
			vE0 = (m_VertexList[face.v1].p - m_VertexList[face.v0].p);
			T::D3DXVec3Normalize(&vE0, &vE0);
			vE1 = (m_VertexList[face.v2].p - m_VertexList[face.v0].p);
			T::D3DXVec3Normalize(&vE1, &vE1);
			T::D3DXVec3Cross(&face.vNormal, &vE0, &vE1);
			T::D3DXVec3Normalize(&face.vNormal, &face.vNormal);

			m_VertexList[face.v0].n += face.vNormal;
			m_VertexList[face.v1].n += face.vNormal;
			m_VertexList[face.v2].n += face.vNormal;

			fDot = max(0.0f, T::D3DXVec3Dot(&vLight, &face.vNormal));
			m_VertexList[face.v0].c = T::TVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v1].c = T::TVector4(fDot, fDot, fDot, 1);
			m_VertexList[face.v2].c = T::TVector4(fDot, fDot, fDot, 1);
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
			float fDot = max(0.0f, T::D3DXVec3Dot(&vLight, &m_VertexList[iRow * m_iNumCols + iCol].n));
			m_VertexList[iRow * m_iNumCols + iCol].c = T::TVector4(fDot, fDot, fDot, 1);
		}
	}
	return true;

}
bool AMap::Frame() 
{
	//깊이맵 만들때 필요한 vLight 지정
	T::TVector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);
	T::D3DXVec3Normalize(&vLight, &vLight);
	vLight = vLight * -1.0f;

	//이름만 Color. 실제론 vLight의 값이 들어가있다. Light가 g_fGameTimer에 따라 움직인다.
	//ConstantList -> LightConstantList로 변경
	m_LightConstantList.vLightDir.x = vLight.x;
	m_LightConstantList.vLightDir.y = vLight.y;
	m_LightConstantList.vLightDir.z = vLight.z;
	m_LightConstantList.vLightDir.w = 1.0f;
	/*m_ConstantList.Color.x = vLight.x;
	m_ConstantList.Color.y = vLight.y;
	m_ConstantList.Color.z = vLight.z;
	m_ConstantList.Color.w = 1.0f;*/
	
	return true;
}

AMap::AMap() {}
AMap::~AMap() {}
