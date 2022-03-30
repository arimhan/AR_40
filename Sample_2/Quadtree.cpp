#include "Quadtree.h"

//#include "Object3D.h"

int AQuadtree::g_iCount = 0;

void AQuadtree::Build(int iWidth, int iHeight, int iMaxDepth)
{
	m_iMaxDepth = iMaxDepth;
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	m_pRootNode = CreateNode(nullptr, 0, 0, m_iWidth, m_iHeight);
	BuildTree(m_pRootNode);
}

void AQuadtree::Build(AMap* pMap, int iMaxDepth)
{
	m_pMap = pMap;
	m_iMaxDepth = iMaxDepth;
	m_iWidth = pMap->m_iNumCols;
	m_iHeight = pMap->m_iNumRows;

	m_pRootNode = CreateNode(nullptr, 0, m_iWidth - 1, m_iWidth * (m_iHeight - 1), m_iWidth * m_iHeight - 1);
	BuildTree(m_pRootNode);
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
	if (pParent != nullptr) { return; }
	if (pParent->m_iDepth == m_iMaxDepth)
	{
		pParent->m_bLeaf = true;
		SetIndexData(pParent);
		CreateIndexBuffer(pParent);
		g_pLeafNodes.push_back(pParent);
		return;
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
	//AddDynamicObject ���� �ٸ���..?
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
		for(int iNode =0; iNode<4; iNode++)
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
	if (abox.vMin.x <= bbox.vMin.x && abox.vMin.y <= bbox.vMin.y && abox.vMin.z <= bbox.vMin.z)
	{
		if (abox.vMax.x >= bbox.vMax.x && abox.vMax.y >= bbox.vMax.y && abox.vMax.z >= bbox.vMax.z)
		{
			return true;
		}
	}
	return false;
}

void AQuadtree::SetIndexData(ANode* pNode)
{
	//m_pMap�� ������ ������ ����ǵ���? ����� ��忡���� �ߵ��ϴ� ���� ����� �ڵ�
	assert(m_pMap);

	//Row : �� (����)
	//Col : �� (����)
	DWORD dwStartRow = pNode->m_CornerList[0] / m_iWidth;
	DWORD dwEndRow = pNode->m_CornerList[2] / m_iWidth;

	DWORD dwStartCol = pNode->m_CornerList[0] % m_iWidth;
	DWORD dwEndCol = pNode->m_CornerList[1] % m_iWidth;

	DWORD dwCellWidth = (dwEndCol - dwStartCol);
	DWORD dwCellHeight = (dwEndRow - dwStartRow);

	int iNumFace = dwCellWidth * dwCellHeight * 2; //�ﰢ��2���ϱ� 2��
	pNode->m_IndexList.resize(iNumFace * 3);	//Index�� �ﰢ�� �׸� �� 3���� �ʿ��ϹǷ� 3��
	UINT iIndex = 0;
	for (DWORD iRow = dwStartRow; iRow < dwStartRow; iRow++)
	{
		for (DWORD iCol = dwStartCol; iCol < dwStartCol; iCol++)
		{
			pNode->m_IndexList[iIndex + 0] = iRow * m_iWidth + iCol;
			pNode->m_IndexList[iIndex + 1] = (iRow * m_iWidth + iCol) + 1;
			pNode->m_IndexList[iIndex + 2] = (iRow + 1) * m_iWidth + iCol;

			pNode->m_IndexList[iIndex + 3] = pNode->m_IndexList[iIndex + 2];
			pNode->m_IndexList[iIndex + 4] = pNode->m_IndexList[iIndex + 1];
			pNode->m_IndexList[iIndex + 5] = pNode->m_IndexList[iIndex + 2] + 1;
			iIndex += 6;
		}			
	}
}

bool AQuadtree::CreateIndexBuffer(ANode* pNode)
{

	HRESULT hr;
	if (pNode->m_IndexList.size() <= 0) return true;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(DWORD) *pNode->m_IndexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &pNode->m_IndexList.at(0);

	if(FAILED(hr = m_pMap->m_pd3dDevice->CreateBuffer(&bd, &sd, 
		pNode->m_pIndexBuffer.GetAddressOf())))
	{
		return false;
	}
	return true;
}

void AQuadtree::Update(ACamera* pCamera)
{
	g_pDrawLeafNodes.clear();
	m_pObjList.clear();
	RenderTile(m_pRootNode);
}

bool AQuadtree::Render()
{
	m_pMap->PreRender();
	m_pMap->Draw();

	for (int iNode = 0; iNode < g_pDrawLeafNodes.size(); iNode++)
	{
		m_pMap->m_ConstantList.Color = T::TVector4(1, 1, 0, 1);
		m_pMap->m_pContext->UpdateSubresource(m_pMap->m_pConstantBuffer, 
			0, NULL, &m_pMap->m_ConstantList, 0, 0);
		
		m_pMap->m_pContext->IASetIndexBuffer(g_pDrawLeafNodes[iNode]->
			m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		m_pMap->m_pContext->DrawIndexed(g_pDrawLeafNodes[iNode]->m_IndexList.size(), 0, 0);
	}
	for (auto obj : m_pObjList)
	{
		obj->pObject->SetMatrix(&obj->matWorld, &m_pMap->m_matView, &m_pMap->m_matProj);
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

void AQuadtree::PrintObjList(ANode* pNode)
{
	if (pNode == nullptr) return;
	for (list<AMapObj*>::iterator iter = pNode->m_pDynamicObjList.begin(); 
		iter != pNode->m_pDynamicObjList.end(); iter++)
	{
		AMapObj* pObj = *iter;
		cout << "[" << pNode->m_iIndex << "]" << (int)pObj->vPos.x << ":" << (int)pObj->vPos.y << " ";
	}
	cout << endl;
	for (int iNode = 0; iNode << 4; iNode++)
	{
		PrintObjList(pNode->m_pChild[iNode]);
	}
}


AQuadtree::AQuadtree() {}
AQuadtree::~AQuadtree() { delete m_pRootNode; }