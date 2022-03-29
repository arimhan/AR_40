#include "Quadtree.h"
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
	//0, 4, 20, 24 식으로 생성
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
	// 세로로 2,7,12,17,22, 가로로 10 ~ 14 이렇게 십자가 모양으로 이웃 노드들을 연결하는 센터값이라고 보면 된다.
	//그래서 하단에서 차례대로
	//위 map에서 순서대로 
	// 0	1
	//
	// 2	3
	//을 기준으로 돌기 때문에, 아래에서 iT (2)를 구하려면 0번+1번을 더한 뒤 /2로 나눠 중간값인 2를 구할 수 있다.

	int iT = (pParent->m_CornerList[0] + pParent->m_CornerList[1]) / 2;	//Top 2
	int iB = (pParent->m_CornerList[2] + pParent->m_CornerList[3]) / 2;	//Bottom 22
	int iL = (pParent->m_CornerList[0] + pParent->m_CornerList[2]) / 2;	//Left 10
	int iR = (pParent->m_CornerList[1] + pParent->m_CornerList[3]) / 2;	//Right 14
	int iC = (pParent->m_CornerList[0] + pParent->m_CornerList[3]) / 2;	//Center 12

	//0번-> 0,2,10,12 
	pParent->m_pChild[0] = CreateNode(pParent, pParent->m_CornerList[0], iT, iL, iC);
	//1번-> 2,4,12,14
	pParent->m_pChild[1] = CreateNode(pParent, iT, pParent->m_CornerList[1], iC, iR);
	//2번-> 10,12,20,22 
	pParent->m_pChild[2] = CreateNode(pParent, iL, iC, pParent->m_CornerList[2], iB);
	//3번-> 12,14,22,24 
	pParent->m_pChild[3] = CreateNode(pParent, iC, iR, iB, pParent->m_CornerList[3]);

	for (int iChild = 0; iChild < pParent->m_pChild.size(); iChild++)
	{
		BuildTree(pParent->m_pChild[iChild]);
	}

}

ABox AQuadtree::GenBoundingBox(ANode* pNode)
{
	return ABox();
}

TVector2 AQuadtree::GetHeightFromNode(DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR)
{
	return TVector2();
}

bool AQuadtree::AddObject(AMapObj* pObj)
{
	//Rootnode에서 현재 map의 해당하는 노드를 찾아, 노드가 있을경우 pObj를 넣어준다.
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
	//AddDynamicObject 뭐가 다른겨..?
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
	return nullptr;
}

bool AQuadtree::CheckBox(ABox& abox, ABox& bbox)
{
	return true;
}

void AQuadtree::SetIndexData(ANode* pNode)
{
}

bool AQuadtree::CreateIndexBuffer(ANode* pNode)
{
	return true;
}

void AQuadtree::Update(ACamera* pCamera)
{
}

void AQuadtree::Render()
{
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
}

void AQuadtree::PrintObjList(ANode* pNode)
{
}


AQuadtree::AQuadtree() {}
AQuadtree::~AQuadtree() { delete m_pRootNode; }