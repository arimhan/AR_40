#include "Quadtree.h"
int AQuadtree::g_iCount = 0;


void AQuadtree::Build(int iWidth, int iHeight, int iMaxDepth)
{
	m_iLeafDepth = iMaxDepth;
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	m_pRootNode = CreateNode(nullptr, 0, 0, m_iWidth, m_iHeight);
	BuildTree(m_pRootNode);
}

void AQuadtree::Build(AMap* pMap, int iMaxDepth)
{

	HRESULT hr;
	m_pMap = pMap;
	m_IndexList.resize(m_pMap->m_IndexList.size());

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	if (FAILED(hr = m_pMap->m_pd3dDevice->CreateBuffer(&bd, NULL,
		m_pIndexBuffer.GetAddressOf()))) { return; }


	m_iLeafDepth = iMaxDepth;
	m_iWidth = pMap->m_iNumCols;
	m_iHeight = pMap->m_iNumRows;

	m_pRootNode = CreateNode(nullptr, 0, m_iWidth - 1, m_iWidth * (m_iHeight - 1), m_iWidth * m_iHeight - 1);
	BuildTree(m_pRootNode);
	FindNeighborNode();

	for (auto node : g_pLeafNodes)
	{
		SetIndexData(node, m_iNumLOD);	//�� �� *16��
		CreateIndexBuffer(node, m_iNumLOD);
	}
}

ANode* AQuadtree::CreateNode(ANode* pParent, float x, float y, float w, float h)
{
	//0, 4, 20, 24 ������ ����
	ANode* pNode = new ANode(x, y, w, h);
	pNode->m_iIndex = g_iCount++;
	if (pParent != nullptr)
	{
		pNode->m_iDepth = pParent->m_iDepth + 1;
	}
	GenBoundingBox(pNode);
	return pNode;
}

void AQuadtree::BuildTree(ANode* pParent)
{
	if (pParent == nullptr) { return; }

	if ((pParent->m_CornerList[1] - pParent->m_CornerList[0]) == 1)
	{
		m_iMaxDepth = pParent->m_iDepth;
		m_iNumLOD = (m_iMaxDepth - m_iLeafLOD) + 1;
		return;
	}

	if (pParent->m_iDepth == m_iLeafDepth)
	{
		m_iLeafLOD = pParent->m_iDepth;
		pParent->m_bLeaf = true;

		g_pLeafNodes.push_back(pParent);
	}

	//(0)   1   (2)   3   (4)
	// 5    6    7    8    9
	//(10)  11  (12)  13  (14)
	// 15   16   17   18   19
	//(20)  21  (22)  23  (24)
	// ���η� 2,7,12,17,22, ���η� 10 ~ 14 �̷��� ���ڰ� ������� �̿� ������ �����ϴ� ���Ͱ��̶�� ���� �ȴ�.
	//�׷��� �ϴܿ��� ���ʴ��
	//�� map���� ������� 
	// 0	1
	//
	// 2	3
	//�� �������� ���� ������, �Ʒ����� iT (2)�� ���Ϸ��� 0��+1���� ���� �� /2�� ���� �߰����� 2�� ���� �� �ִ�.

	int iT = (pParent->m_CornerList[0] + pParent->m_CornerList[1]) / 2;	//Top 2
	int iB = (pParent->m_CornerList[2] + pParent->m_CornerList[3]) / 2;	//Bottom 22
	int iL = (pParent->m_CornerList[0] + pParent->m_CornerList[2]) / 2;	//Left 10
	int iR = (pParent->m_CornerList[1] + pParent->m_CornerList[3]) / 2;	//Right 14
	int iC = (pParent->m_CornerList[0] + pParent->m_CornerList[3]) / 2;	//Center 12

	//0��-> 0,2,10,12 
	pParent->m_pChild[0] = CreateNode(pParent, pParent->m_CornerList[0], iT, iL, iC);
	//1��-> 2,4,12,14
	pParent->m_pChild[1] = CreateNode(pParent, iT, pParent->m_CornerList[1], iC, iR);
	//2��-> 10,12,20,22 
	pParent->m_pChild[2] = CreateNode(pParent, iL, iC, pParent->m_CornerList[2], iB);
	//3��-> 12,14,22,24 
	pParent->m_pChild[3] = CreateNode(pParent, iC, iR, iB, pParent->m_CornerList[3]);

	for (int iChild = 0; iChild < pParent->m_pChild.size(); iChild++)
	{
		BuildTree(pParent->m_pChild[iChild]);
	}

}

ABox AQuadtree::GenBoundingBox(ANode* pNode)
{
	//Box�� �� ������ ǥ��. 0���� �ڳʸ���Ʈ 0��, 24���� �ڳʸ���Ʈ 3������ �� �� min, max�� ��� ���������ϴ�.
	TVector3 v0, v4;
	v0 = m_pMap->m_VertexList[pNode->m_CornerList[0]].p;	//0
	v4 = m_pMap->m_VertexList[pNode->m_CornerList[3]].p;	//24

	pNode->m_Box.vMin.x = v0.x;
	pNode->m_Box.vMin.z = v4.z;
	pNode->m_Box.vMax.x = v4.x;
	pNode->m_Box.vMax.z = v0.z;

	TVector2 vHeight = GetHeightFromNode(	pNode->m_CornerList[0], 
											pNode->m_CornerList[1], 
											pNode->m_CornerList[2], 
											pNode->m_CornerList[3]);
	pNode->m_Box.vMin.y = vHeight.y;
	pNode->m_Box.vMax.y = vHeight.x;
	pNode->m_Box.vAxis[0] = TVector3(1, 0, 0);
	pNode->m_Box.vAxis[1] = TVector3(0, 1, 0);
	pNode->m_Box.vAxis[2] = TVector3(0, 0, 1);

	pNode->m_Box.size.x = (pNode->m_Box.vMax.x - pNode->m_Box.vMin.x) / 2.0f;
	pNode->m_Box.size.y = (pNode->m_Box.vMax.y - pNode->m_Box.vMin.y) / 2.0f;
	pNode->m_Box.size.z = (pNode->m_Box.vMax.z - pNode->m_Box.vMin.z) / 2.0f;

	pNode->m_Box.vMiddle = (pNode->m_Box.vMax + pNode->m_Box.vMin);
	pNode->m_Box.vMiddle /= 2.0f;

	return pNode->m_Box;
}

TVector2 AQuadtree::GetHeightFromNode(DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR)
{
	assert(m_pMap);

	DWORD dwStartRow = dwTL / m_iWidth;
	DWORD dwEndRow = dwBL / m_iWidth;
	//������ ������ dwTL�� dwBL�� �ٲ� �� ����....


	DWORD dwStartCol = dwTL % m_iWidth;
	DWORD dwEndCol = dwTR % m_iWidth;

	TVector2 vHeight;
	vHeight.x = -999999.0f;
	vHeight.y = 999999.0f;


	//DWORD dwCellWidth = (dwEndCol - dwStartCol);
	//DWORD dwCellHeight = (dwEndRow - dwStartRow);
	
	for (DWORD dwRow = dwStartRow; dwRow < dwEndRow; dwRow++)
	{
		for (DWORD dwCol = dwStartCol; dwCol < dwEndCol; dwCol++)
		{
			if (m_pMap->m_VertexList[dwRow * m_iWidth + dwCol].p.y > vHeight.x)
			{
				vHeight.x = m_pMap->m_VertexList[dwRow * m_iWidth + dwCol].p.y;
			}
			if (m_pMap->m_VertexList[dwRow * m_iWidth + dwCol].p.y < vHeight.y)
			{
				vHeight.y = m_pMap->m_VertexList[dwRow * m_iWidth + dwCol].p.y;
			}
		}
	}

	return vHeight;
}

bool AQuadtree::AddObject(AMapObj* pObj)
{
	//Rootnode���� ���� map�� �ش��ϴ� ��带 ã��, ��尡 ������� pObj�� �־��ش�.
	ANode* pFindNode = FindNode(m_pRootNode, pObj->box);
	if (pFindNode != nullptr)
	{
		pFindNode->AddObject(pObj);
		return true;
	}
	return false;
}

bool AQuadtree::AddDynamicObject(AMapObj* pObj)
{
	ANode* pFindNode = FindNode(m_pRootNode, pObj->box);
	if (pFindNode != nullptr)
	{
		pFindNode->AddDynamicObject(pObj);
		return true;
	}
	return false;
}

void AQuadtree::DelDynamicObject(ANode* pNode)
{
	if (pNode == nullptr) return;
	pNode->m_pDynamicObjList.clear();
	for (int iNode = 0; iNode < 4; iNode++)
	{
		DelDynamicObject(pNode->m_pChild[iNode]);
	}
}

ANode* AQuadtree::FindNode(ANode* pNode, ABox& box)
{
	//pNode �� ���� �� ���� Node �� ������ŭ ���鼭 �ڽĳ�带 ã�´�
	do 
	{
		for (int iNode = 0; iNode < 4; iNode++)
		{
			if (pNode->m_pChild[iNode] != nullptr)
			{
				if (CheckBox(pNode->m_pChild[iNode]->m_Box, box))
				{
					g_pQueue.push(pNode->m_pChild[iNode]);
					break;
				}
			}
		}
		if (g_pQueue.empty()) break;
		pNode = g_pQueue.front();
		g_pQueue.pop();
	} while (pNode);
	return pNode;
}

bool AQuadtree::CheckBox(ABox& abox, ABox& bbox)
{
	//abox�� bbox�� �浹üũ�� �Ѵ�. AABB abox�� bbox�� ��ĥ��� return true�� �Ѵ�.
	if (abox.vMin.x <= bbox.vMin.x && abox.vMin.y <= bbox.vMin.y 
		&& abox.vMin.z <= bbox.vMin.z)
	{
		if (abox.vMax.x >= bbox.vMax.x 
			&& abox.vMax.y >= bbox.vMax.y && abox.vMax.z >= bbox.vMax.z)
		{
			return true;
		}
	}
	return false;
}

void AQuadtree::SetIndexData(ANode* pNode, int iLodLevel)
{
	//m_pMap�� ������ ������ ����ǵ���? ����� ��忡���� �ߵ��ϴ� ���� ����� �ڵ�
	assert(m_pMap);
	pNode->m_IndexList.resize(iLodLevel);

	for (int iLod = 0; iLod < iLodLevel; iLod++)
	{ 
		int iOffset = pow(2, iLod); // 0->1, 1->2, 2->4
		//Row : �� (����)
		//Col : �� (����)
		DWORD dwStartRow = pNode->m_CornerList[0] / m_iWidth;
		DWORD dwEndRow = pNode->m_CornerList[2] / m_iWidth;

		DWORD dwStartCol = pNode->m_CornerList[0] % m_iWidth;
		DWORD dwEndCol = pNode->m_CornerList[1] % m_iWidth;

		DWORD dwCellWidth = (dwEndCol - dwStartCol);
		DWORD dwCellHeight = (dwEndRow - dwStartRow);

		int iNumFace = (dwCellWidth * dwCellHeight * 2) / pow(4, iLod); //�ﰢ��2���ϱ� 2��

		pNode->m_IndexList[iLod].resize(iNumFace * 3);	//Index�� �ﰢ�� �׸� �� 3���� �ʿ��ϹǷ� 3��
		UINT iIndex = 0;
		for (DWORD iRow = dwStartRow; iRow < dwEndRow; iRow += iOffset)
		{
			for (DWORD iCol = dwStartCol; iCol < dwEndCol; iCol += iOffset)
			{
				pNode->m_IndexList[iLod][iIndex + 0] = iRow * m_iWidth + iCol;
				pNode->m_IndexList[iLod][iIndex + 1] = (iRow * m_iWidth + iCol) + iOffset;
				pNode->m_IndexList[iLod][iIndex + 2] = (iRow + iOffset) * m_iWidth + iCol;

				pNode->m_IndexList[iLod][iIndex + 3] = pNode->m_IndexList[iLod][iIndex + 2];
				pNode->m_IndexList[iLod][iIndex + 4] = pNode->m_IndexList[iLod][iIndex + 1];
				pNode->m_IndexList[iLod][iIndex + 5] = pNode->m_IndexList[iLod][iIndex + 2] + iOffset;
				iIndex += 6;
			}			
		}
	}
}

bool AQuadtree::CreateIndexBuffer(ANode* pNode, int iLodLevel)
{

	HRESULT hr;
	pNode->m_pIndexBuffer.resize(iLodLevel);
	for(int iLod = 0; iLod < iLodLevel; iLod++)
	{ 
		if (pNode->m_IndexList[iLod].size() <= 0) return true;

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(DWORD) *pNode->m_IndexList[iLod].size();
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
		sd.pSysMem = &pNode->m_IndexList[iLod].at(0);

		if(FAILED(hr = m_pMap->m_pd3dDevice->CreateBuffer(&bd, &sd, 
			pNode->m_pIndexBuffer[iLod].GetAddressOf())))
		{
			return false;
		}
	}
	return true;
}

void AQuadtree::Update(ACamera* pCamera)
{
	g_pDrawLeafNodes.clear();
	m_pObjList.clear();
	RenderTile(m_pRootNode);

	//��ü ����� LOD ������ �����Ѵ�
	for (auto node : g_pLeafNodes)
	{
		GetRatio(node);
	}
	//���̴� ������ LOD Type ( 0~15) �� �����Ѵ�
	m_iNumFace = 0;
	for (auto node : g_pDrawLeafNodes)
	{
		GetLodType(node);
		//��ü �ε��� ���۸� 1���� ���, LOD ���۸� ����
		m_iNumFace += UpdateIndexList(node, m_iNumFace * 3, node->m_iCurrentLod);
	}

}
bool AQuadtree::PreRender() 
{
	if (m_pMap)
	{
		m_pMap->PreRender();
		m_pMap->Draw();

		m_pMap->m_pContext->UpdateSubresource(m_pIndexBuffer.Get(),
			0, NULL, &m_IndexList.at(0), 0, 0);

		m_pMap->m_pContext->IASetIndexBuffer(
			m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	}
	return true;
}

bool AQuadtree::Render()
{
	PreRender();
	PostRender();
	return true;
}

bool AQuadtree::PostRender() 
{
	if (m_pMap)
	{
		m_pMap->m_pContext->DrawIndexed(m_iNumFace * 3, 0, 0);
	}
	for (auto obj : m_pObjList)
	{
		obj->pObject->SetMatrix(&obj->matWorld, 
			&m_pMap->m_matView, &m_pMap->m_matProj);
		obj->pObject->m_ConstantList.Color = T::TVector4(1, 1, 1, 1);
		obj->pObject->Render();
	}
	return true;
}

void AQuadtree::RenderObject(ANode* pNode)
{
	if (pNode == nullptr) return;
	if (m_pCamera->ClassifyOBB(&pNode->m_Box) == TRUE)
	{
		for (auto obj : pNode->m_pStaticObjList)
		{
			m_pObjList.push_back(obj);
		}
		for (int iNode = 0; iNode < pNode->m_pChild.size(); iNode++)
		{
			RenderObject(pNode->m_pChild[iNode]);
		}
	}
}

void AQuadtree::RenderTile(ANode* pNode)
{
	if (pNode == nullptr) return;
	if (m_pCamera->ClassifyOBB(&pNode->m_Box) == TRUE)
	{
		for (auto obj : pNode->m_pStaticObjList)
		{
			if (m_pCamera->ClassifyOBB(&obj->box) == TRUE)
			{
				m_pObjList.push_back(obj);
			}
		}
		if (pNode->m_bLeaf == true)
		{
			g_pDrawLeafNodes.push_back(pNode);
			return;
		}
		for (int iNode = 0; iNode < pNode->m_pChild.size(); iNode++)
		{
			RenderTile(pNode->m_pChild[iNode]);
		}
	}
}

//void AQuadtree::PrintObjList(ANode* pNode)
//{
//	if (pNode == nullptr) return;
//	for (list<AMapObj*>::iterator iter = pNode->m_pDynamicObjList.begin();
//		iter != pNode->m_pDynamicObjList.end(); iter++)
//	{
//		AMapObj* pObj = *iter;
//		cout << "[" << pNode->m_iIndex << "]" << (int)pObj->vPos.x << ":" << (int)pObj->vPos.y << " ";
//	}
//	cout << endl;
//	for (int iNode = 0; iNode << 4; iNode++)
//	{
//		PrintObjList(pNode->m_pChild[iNode]);
//	}
//}


void AQuadtree::FindNeighborNode()
{
	for (auto node : g_pLeafNodes)
	{
		node->m_pNeighborList.resize(4);
		T::TVector3 p;
		p.x = node->m_Box.vMiddle.x;
		p.y = 0.0f;
		p.z = node->m_Box.vMax.z + node->m_Box.size.z;
		node->m_pNeighborList[0] = CheckBoxtoPoint(p); //��

		p.z = node->m_Box.vMin.z - node->m_Box.size.z;
		node->m_pNeighborList[1] = CheckBoxtoPoint(p); //��

		p.z = node->m_Box.vMiddle.z;
		p.x = node->m_Box.vMin.x - node->m_Box.size.x;
		node->m_pNeighborList[2] = CheckBoxtoPoint(p); //��

		p.x = node->m_Box.vMax.x + node->m_Box.size.x;
		node->m_pNeighborList[3] = CheckBoxtoPoint(p); //��
	}
}

ANode* AQuadtree::CheckBoxtoPoint(T::TVector3 p) 
{
	for (auto node : g_pLeafNodes)
	{
		if(node->m_Box.vMin.x <= p.x && node->m_Box.vMax.x >= p.x && 
			node->m_Box.vMin.z <= p.z && node->m_Box.vMax.z >= p.z)
		{
			return node;
		}
	}
	return nullptr;
}

void AQuadtree::GetRatio(ANode* pNode)
{
	T::TVector3 v = m_pCamera->m_vCamera - pNode->m_Box.vMiddle;
	float fDistance = T::D3DXVec3Length(&v);
	float fRatio = fDistance / m_pCamera->m_fFarDistance;
	//lod level -> 0 ~ 1 : 0~ 0.25, 0.25 ~ 0.5 : 0.5 ~ 1
	pNode->m_iCurrentLod = fRatio * m_iNumLOD;	//0, 1, 2
	if(pNode->m_iCurrentLod >= m_iNumLOD)
	{
		pNode->m_iCurrentLod = m_iNumLOD - 1;
	}
}

int	AQuadtree::GetLodType(ANode* pNode) 
{
	if (pNode->m_pNeighborList.size() <= 0) return 0;
	int dwType = 0;
	if (pNode->m_pNeighborList[0] && pNode->m_pNeighborList[0]->m_iCurrentLod 
		< pNode->m_iCurrentLod) dwType += 1;
	if (pNode->m_pNeighborList[1] && pNode->m_pNeighborList[1]->m_iCurrentLod
		< pNode->m_iCurrentLod) dwType += 4;
	if (pNode->m_pNeighborList[2] && pNode->m_pNeighborList[2]->m_iCurrentLod
		< pNode->m_iCurrentLod) dwType += 8;
	if (pNode->m_pNeighborList[3] && pNode->m_pNeighborList[3]->m_iCurrentLod
		< pNode->m_iCurrentLod) dwType += 2;

	pNode->m_dwLodType = dwType;
	return dwType;

}

int	 AQuadtree::UpdateIndexList(ANode* pNode, DWORD dwCurentIndex, DWORD dwNumLevel) 
{
	if (m_IndexList.size() <= 0) return false;
	int iNumFaces = 0;

	DWORD dwTL = pNode->m_CornerList[0];
	DWORD dwTR = pNode->m_CornerList[1];
	DWORD dwBL = pNode->m_CornerList[2];
	DWORD dwBR = pNode->m_CornerList[3];

	DWORD dwStartRow = dwTL / m_iWidth;
	DWORD dwEndRow = dwBL / m_iWidth;

	DWORD dwStartCol = dwTL % m_iWidth;
	DWORD dwEndCol = dwTR % m_iWidth;

	DWORD dwOffset = (DWORD)(pow(2.0f, (float)dwNumLevel));
	DWORD dwCountX = ((dwEndCol - dwStartCol) / dwOffset) - 1;
	DWORD dwCountY = ((dwEndRow - dwStartRow) / dwOffset) - 1;

	DWORD dwYCell = 0; 
	for (DWORD dwRow = dwStartRow; dwRow < dwEndRow; dwRow += dwOffset, dwYCell++)
	{
		DWORD dwXCell = 0;
		for (DWORD dwCol = dwStartCol; dwCol < dwEndCol; dwCol += dwOffset, dwXCell++)
		{
			DWORD dwNextRow = dwRow + dwOffset;
			DWORD dwNextCol = dwCol + dwOffset;

			DWORD i0 = dwNextRow * m_iWidth + dwCol;	//2
			DWORD i1 = dwRow * m_iWidth + dwCol;		//0
			DWORD i2 = dwRow * m_iWidth + dwNextCol;	//1

			//����, ���
			if ((dwXCell == 0 && dwYCell == 0))
			{
				DWORD dwType = (pNode->m_dwLodType & 8) + (pNode->m_dwLodType & 1);
				iNumFaces += SetLodIndexBuffer(pNode, dwCurentIndex,
					i0, i1, i2, dwType);
			}
			else if ((dwYCell == 0) && (pNode->m_dwLodType & 8))
			{
				iNumFaces += SetLodIndexBuffer(pNode, dwCurentIndex,
					i0, i1, i2, 8);
			}
			else if ((dwYCell == 0) && (pNode->m_dwLodType & 1))
			{
				iNumFaces += SetLodIndexBuffer(pNode, dwCurentIndex,
					i0, i1, i2, 1);
			}
			else
			{
				m_IndexList[dwCurentIndex + 0] = i0;
				m_IndexList[dwCurentIndex + 1] = i1;
				m_IndexList[dwCurentIndex + 2] = i2;
				iNumFaces += 1;
				dwCurentIndex += 3;
			}
			DWORD j0 = dwRow * m_iWidth + dwNextCol;		//2
			DWORD j1 = dwNextRow * m_iWidth + dwNextCol;	//3
			DWORD j2 = dwNextRow * m_iWidth + dwCol;		//0

			if ((dwXCell == dwCountX && dwYCell == dwCountY))
			{
				DWORD dwType = (pNode->m_dwLodType & 2) + (pNode->m_dwLodType & 4);
				iNumFaces += SetLodIndexBuffer(pNode, dwCurentIndex,
					j0, j1, j2, dwType);
			}
			else if ((dwXCell == dwCountX) && (pNode->m_dwLodType & 2))
			{
				iNumFaces += SetLodIndexBuffer(pNode, dwCurentIndex,
					j0, j1, j2, 2);
			}
			else if ((dwYCell == dwCountY) && (pNode->m_dwLodType & 4))
			{
				iNumFaces += SetLodIndexBuffer(pNode, dwCurentIndex,
					j0, j1, j2, 4);
			}
			else
			{
				m_IndexList[dwCurentIndex + 0] = j0;
				m_IndexList[dwCurentIndex + 1] = j1;
				m_IndexList[dwCurentIndex + 2] = j2;
				iNumFaces += 1;
				dwCurentIndex += 3;
			}
		}
	}
	return iNumFaces;
}

int	 AQuadtree::SetLodIndexBuffer(ANode* pNode, DWORD& dwCurentIndex,
	DWORD dwA, DWORD dwB, DWORD dwC, DWORD dwType) 
{

	int iNumFaces = 0;
	if (dwType == 0)
	{
		m_IndexList[dwCurentIndex + 0] = dwA;
		m_IndexList[dwCurentIndex + 1] = dwB;
		m_IndexList[dwCurentIndex + 2] = dwC;
		iNumFaces += 1;
		dwCurentIndex += 3;
		return iNumFaces;
	}
	if (dwType == 8 || dwType == 2) //�¿�
	{
		DWORD dwCenter = (dwA + dwB) / 2;
		m_IndexList[dwCurentIndex + 0] = dwC;
		m_IndexList[dwCurentIndex + 1] = dwA;
		m_IndexList[dwCurentIndex + 2] = dwCenter;
		m_IndexList[dwCurentIndex + 3] = dwC;
		m_IndexList[dwCurentIndex + 4] = dwCenter;
		m_IndexList[dwCurentIndex + 5] = dwB;
		iNumFaces += 2;
		dwCurentIndex += 6;
		return iNumFaces;
	}
	if (dwType == 1 || dwType == 4) //����
	{
		DWORD dwCenter = (dwB + dwC) / 2;
		m_IndexList[dwCurentIndex + 0] = dwA;
		m_IndexList[dwCurentIndex + 1] = dwB;
		m_IndexList[dwCurentIndex + 2] = dwCenter;
		m_IndexList[dwCurentIndex + 3] = dwA;
		m_IndexList[dwCurentIndex + 4] = dwCenter;
		m_IndexList[dwCurentIndex + 5] = dwC;
		iNumFaces += 2;
		dwCurentIndex += 6;
		return iNumFaces;
	}
	if (dwType == 9 || dwType == 6) //�»�, ����
	{
		DWORD dwTopCenter = (dwB + dwC) / 2;
		DWORD dwLeftCenter = (dwA + dwB) / 2;

		m_IndexList[dwCurentIndex + 0] = dwLeftCenter;
		m_IndexList[dwCurentIndex + 1] = dwB;
		m_IndexList[dwCurentIndex + 2] = dwTopCenter;
		m_IndexList[dwCurentIndex + 3] = dwLeftCenter;
		m_IndexList[dwCurentIndex + 4] = dwTopCenter;
		m_IndexList[dwCurentIndex + 5] = dwA;

		m_IndexList[dwCurentIndex + 6] = dwA;
		m_IndexList[dwCurentIndex + 7] = dwTopCenter;
		m_IndexList[dwCurentIndex + 8] = dwC;
		iNumFaces += 3;
		dwCurentIndex += 9;
		return iNumFaces;
	}
	return iNumFaces;
}

//����� ����϶��� �����.
void AQuadtree::DrawDebugInit(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext) 
{
	m_BoxDebug.m_pColorTex = I_Texture.Load(L"../../data/charport.bmp");
	m_BoxDebug.m_pVShader = I_Shader.CreateVertexShader(pd3dDevice, L"Box.hlsl", "VSColor");
	m_BoxDebug.m_pPShader = I_Shader.CreatePixelShader(pd3dDevice, L"Box.hlsl", "PSColor");
	m_BoxDebug.SetPosition(T::TVector3(0.0f, 1.0f, 0.0f));
	if (!m_BoxDebug.Create(pd3dDevice, pContext)) { return; }
}

//����� ����϶��� �����.
void AQuadtree::DrawDebugRender(ABox* pBox) 
{
	// 0	1
	// 2	3
	// 4	5
	// 6	7
	//������ ���ƾ� ��.
	pBox->vList[0] = T::TVector3(pBox->vMin.x, pBox->vMax.y, pBox->vMin.z);
	pBox->vList[1] = T::TVector3(pBox->vMax.x, pBox->vMax.y, pBox->vMin.z);
	pBox->vList[2] = T::TVector3(pBox->vMin.x, pBox->vMin.y, pBox->vMin.z);
	pBox->vList[3] = T::TVector3(pBox->vMax.x, pBox->vMin.y, pBox->vMin.z);

	pBox->vList[4] = T::TVector3(pBox->vMin.x, pBox->vMax.y, pBox->vMax.z);
	pBox->vList[5] = T::TVector3(pBox->vMax.x, pBox->vMax.y, pBox->vMax.z);
	pBox->vList[6] = T::TVector3(pBox->vMin.x, pBox->vMin.y, pBox->vMax.z);
	pBox->vList[7] = T::TVector3(pBox->vMax.x, pBox->vMin.y, pBox->vMax.z);

	int index = 0;

	//Box���� ���� VB ����~
	// +Z plane
	m_BoxDebug.m_VertexList[index].p = pBox->vList[5];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 0.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[4];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 0.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[7];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 0.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[6];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 0.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// -Z plane
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[0];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 0.0f, -1.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[1];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 0.0f, -1.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[2];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 0.0f, -1.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[3];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 0.0f, -1.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// +X plane
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[1];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(1.0f, 0.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[5];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(1.0f, 0.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[3];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(1.0f, 0.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[7];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(1.0f, 0.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// -X plane
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[4];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(-1.0f, 0.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[0];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(-1.0f, 0.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[6];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(-1.0f, 0.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[2];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(-1.0f, 0.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// -y plane
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[2];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, -1.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[3];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, -1.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[6];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, -1.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[7];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, -1.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 1.0f);
	// +y plane
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[4];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 1.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[5];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 1.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 0.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[0];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 1.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(0.0f, 1.0f);
	m_BoxDebug.m_VertexList[++index].p = pBox->vList[1];
	m_BoxDebug.m_VertexList[index].n = T::TVector3(0.0f, 1.0f, 0.0f);
	m_BoxDebug.m_VertexList[index].c = T::TVector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_BoxDebug.m_VertexList[index].t = T::TVector2(1.0f, 1.0f);

	m_BoxDebug.SetMatrix(NULL, &m_pCamera->m_matView, &m_pCamera->m_matProj);
	m_BoxDebug.PreRender();
	m_BoxDebug.Draw();
	m_BoxDebug.m_pContext->UpdateSubresource(m_BoxDebug.m_pVertexBuffer, 
		0, NULL, &m_BoxDebug.m_VertexList.at(0), 0, 0);
	m_BoxDebug.PostRender();
}

AQuadtree::AQuadtree() {}

AQuadtree::~AQuadtree() 
{ 
#ifdef _DEBUG
	m_BoxDebug.Release();
#endif 
	delete m_pRootNode; 
}