#include "Octree.h"

void Octree::Frame(float time)
{
	static float fDirection = 1.0f;
	if (m_Player->m_Pos.x > 100.0f || m_Player->m_Pos.x < 0.0f)
	{
		fDirection *= -1.0f;
	}
	m_Player->m_Velocity.x = 10.0f * fDirection;
	m_Player->m_Velocity.y = 0.0f;
	m_Player->m_Pos += m_Player -> m_Velocity * time;

	Vector3 vHalf = m_Player->m_Rect.vSize / 2.0f;
	m_Player->m_Rect.vPivot = 
	{ m_Player->m_Pos.x - vHalf.x, m_Player->m_Pos.y - vHalf.y,  m_Player->m_Pos.x + vHalf.z };
	m_Player->m_Rect.vMin =
	{ m_Player->m_Pos.x - vHalf.x, m_Player->m_Pos.y - vHalf.y,  m_Player->m_Pos.x - vHalf.z };
	m_Player->m_Rect.vMax =
	{ m_Player->m_Pos.x + vHalf.x, m_Player->m_Pos.y + vHalf.y,  m_Player->m_Pos.x + vHalf.z };

	Node* pFind = FindNode(m_RootNode, m_Player);
	if (pFind != nullptr)
	{
		cout << pFind->m_Index << " ";
	}
}

bool Octree::Init(float fMaxX, float fMaxY, float fMaxZ)
{
	m_Player = new Object();
	m_vSize = { fMaxX, fMaxY, fMaxZ };
	m_RootNode = CreateNode(nullptr, Vector3(0, 0, 0), m_vSize);
	Buildtree(m_RootNode);
	AddObject(m_Player);
	return true;
}
void Octree::Buildtree(Node* pNode)
{
	if (pNode->m_Rect.vSize.x >= 30.0f && pNode->m_Rect.vSize.y >= 30.0f && pNode->m_Rect.vSize.z >= 30.0f)
	{
		Vector3 vHalf = pNode->m_Rect.vSize / 2.0f;
		pNode->m_Child[0] = CreateNode(pNode, pNode->m_Rect.vPivot, vHalf);
		Buildtree(pNode->m_Child[0]);

		pNode->m_Child[1] = CreateNode(pNode, Vector3(pNode->m_Rect.vPivot.x + vHalf.x, 
			pNode->m_Rect.vPivot.y, pNode->m_Rect.vPivot.z), vHalf);
		Buildtree(pNode->m_Child[1]);

		pNode->m_Child[2] = CreateNode(pNode, Vector3(pNode->m_Rect.vPivot.x + vHalf.x,
			pNode->m_Rect.vPivot.y, pNode->m_Rect.vPivot.z - vHalf.z), vHalf);
		Buildtree(pNode->m_Child[2]);

		pNode->m_Child[3] = CreateNode(pNode, Vector3(pNode->m_Rect.vPivot.x,
			pNode->m_Rect.vPivot.y, pNode->m_Rect.vPivot.z - vHalf.z), vHalf);
		Buildtree(pNode->m_Child[3]);

		pNode->m_Child[4] = CreateNode(pNode, Vector3(pNode->m_Rect.vPivot.x,
			pNode->m_Rect.vPivot.y + vHalf.y, pNode->m_Rect.vPivot.z), vHalf);
		Buildtree(pNode->m_Child[4]);

		pNode->m_Child[5] = CreateNode(pNode, Vector3(pNode->m_Rect.vPivot.x + vHalf.x,
			pNode->m_Rect.vPivot.y + vHalf.y, pNode->m_Rect.vPivot.z), vHalf);
		Buildtree(pNode->m_Child[5]);

		pNode->m_Child[6] = CreateNode(pNode, Vector3(pNode->m_Rect.vPivot.x + vHalf.x,
			pNode->m_Rect.vPivot.y + vHalf.y, pNode->m_Rect.vPivot.z - vHalf.z), vHalf);
		Buildtree(pNode->m_Child[6]);

		pNode->m_Child[7] = CreateNode(pNode, Vector3(pNode->m_Rect.vPivot.x,
			pNode->m_Rect.vPivot.y + vHalf.y, pNode->m_Rect.vPivot.z - vHalf.z), vHalf);
		Buildtree(pNode->m_Child[7]);
	}
}
int Octree::CheckRect(Node* pNode, Object* Obj)
{
	if (pNode->m_Rect.vMin.x <= Obj->m_Rect.vMin.x &&
		pNode->m_Rect.vMax.x >= Obj->m_Rect.vMax.x)
	{
		if (pNode->m_Rect.vMin.y <= Obj->m_Rect.vMin.y &&
			pNode->m_Rect.vMax.y >= Obj->m_Rect.vMax.y)
		{
			if (pNode->m_Rect.vMin.z <= Obj->m_Rect.vMin.z &&
				pNode->m_Rect.vMax.z >= Obj->m_Rect.vMax.z)
			{
				return 1;
			}
		}
	}
	return 0;
}
Node* Octree::FindNode(Node* pNode, Object* pObj)
{
	do {
		for (int iNode = 0; iNode < 8; iNode++)
		{
			if (pNode->m_Child[iNode] != nullptr)
			{
				if (CheckRect(pNode->m_Child[iNode], pObj))
				{
					m_Queue.push(pNode->m_Child[iNode]);
					break;
				}
			}
		}
		if (m_Queue.empty()) break;
		pNode = m_Queue.front();
		m_Queue.pop();
	}while(pNode);
	return pNode;
}
bool Octree::AddObject(Object* pObj)
{
	Node* pFindNode = FindNode(m_RootNode, pObj);
	if (pFindNode != nullptr)
	{
		pObj->m_NodeIndex = m_ObjectList.size();
		m_ObjectList.insert(make_pair(pObj->m_NodeIndex, pObj));
		pFindNode->AddObject(pObj->m_NodeIndex);
		return true;
	}
	return false;
}
void Octree::Release()
{
	delete m_RootNode;
	m_RootNode = nullptr;
	for (auto& obj : m_ObjectList)
	{
		delete obj.second;
	}
	m_ObjectList.clear();
}
Node* Octree::CreateNode(Node* Parent, Vector3 vPivot, Vector3 vSize)
{
	Node* pNode = new Node(vPivot, vSize);
	if (Parent != nullptr)
	{
		pNode->m_Depth = Parent->m_Depth + 1;
		pNode->m_Parent = Parent;
	}
	pNode->m_Index = Node::g_Counter;
	Node::g_Counter++;
	return pNode;
}
Octree::Octree()
{
	m_RootNode = nullptr;
}
Octree::~Octree()
{}