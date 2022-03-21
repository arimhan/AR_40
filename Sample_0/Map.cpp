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
					m_fHeightList[row * desc.Width + col] = (float)uRed; // DWORD �̹Ƿ�  pitch / 4
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
	//�� ���鶧 �ʿ��� �ֵ� ����
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
	//VertexData�� �����Ѵ�. 
	float hHalfCol = (m_iNumCols - 1) / 2.0f;
	float hHalfRow = (m_iNumRows - 1) / 2.0f;
	float ftxOffsetU = 1.0f / (m_iNumCols - 1);
	float ftxOffsetV = 1.0f / (m_iNumRows - 1);

	for (int iRow = 0; iRow < m_iNumRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCols; iCol++)
		{
			int index = iRow * m_iNumCols + iCol;
			//��������Ʈ �� pnct �� ����
			m_VertexList[index].p.x = (iCol - hHalfCol) * m_iCellDistance;
			m_VertexList[index].p.y = m_fHeightList[index];
			m_VertexList[index].p.z = -((iRow - hHalfRow)* m_iCellDistance); // �������̶� +�� ��ȯ
			m_VertexList[index].n = AVector3( 0, 1, 0);	//��ְ��� Y������ 1���� ���ϰ� ����.
			m_VertexList[index].c =
				AVector4(randstep(0.0f, 1.0f), randstep(0.0f, 1.0f), randstep(0.0f, 1.0f), 1);
				//�÷�(����)�� �������� ����
			m_VertexList[index].t = AVector2(ftxOffsetU * iCol, ftxOffsetV * iRow);
			//������ 1,1�ε�, �ؽ��� 1���� ��ü�� �ٸ��� ������ ���� ���� ��, ���� �������� ������.
		}
	}
	return true;
}
bool AMap::SetIndexData() 
{
	//IndexData�� �����Ѵ�.
	m_IndexList.resize(m_iNumFaces * 3); //Face�� index�� 3���� ���µ�....�� ���ذ� �Ȱ�.
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

	//�ٽ� iIndex�� �ʱ�ȭ �� �� �̹��� vLight�� �������ش�.
	iIndex = 0;
	AVector3 vLight(100, 100, 0);
	vLight = vLight.Normal() * 1.0f;
	for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
	{
		for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
		{
			//0 Face���� ����
			AFace face;
			face.v0 = m_IndexList[iIndex + 0];
			face.v1 = m_IndexList[iIndex + 1];
			face.v2 = m_IndexList[iIndex + 2];

			AVector3 vNormal;
			//�븻���� vE0�� E1 2���� ���� ��, E0�� �𷺼� 1-0, E1�� �𷺼� 2-0�� ���� �븻���͸� ���� �� �ִ�.
			AVector3 vE0 = (m_VertexList[face.v1].p - m_VertexList[face.v0].p).Normal();
			AVector3 vE1 = (m_VertexList[face.v2].p - m_VertexList[face.v0].p).Normal();
			//������ ���� vE0�� vE1�� ���� �� ����ȭ �Ѵ�.
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
			//������ iRow * m_iNumCols + iCol�� ��ּ����� ����ȭ �Ѵ�.
			m_VertexList[iRow * m_iNumCols + iCol].n.Normalize();
			float fDot = max(0.0f, vLight | m_VertexList[iRow * m_iNumCols + iCol].n);
			m_VertexList[iRow * m_iNumCols + iCol].c = AVector4(fDot, fDot, fDot, 1);
		}
	}
	return true;

}
bool AMap::Frame() 
{
	//���̸� ���鶧 �ʿ��� vLight ����
	AVector3 vLight(cosf(g_fGameTimer) * 100.0f, 100, sinf(g_fGameTimer) * 100.0f);
	vLight = vLight.Normal() * -1.0f;

	//�̸��� Color. ������ vLight�� ���� ���ִ�. Light�� g_fGameTimer�� ���� �����δ�.
	m_ConstantList.Color.x = vLight.x;
	m_ConstantList.Color.y = vLight.y;
	m_ConstantList.Color.z = vLight.z;
	m_ConstantList.Color.w = 1.0f;
	
	return true;
}

AMap::AMap() {}
AMap::~AMap() {}
