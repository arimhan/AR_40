#include "Node.h"

int Node::g_Counter = 0;

bool Node::AddObject(int Index)
{
	m_ObjectList.push_back(Index);
	return true;
}
bool Node::IsRect(Vector3 pos)
{
	if (this->m_Rect.vMin.x <= pos.x && this->m_Rect.vMax.x >= pos.x &&
		this->m_Rect.vMin.y <= pos.y && this->m_Rect.vMax.y >= pos.y &&
		this->m_Rect.vMin.z <= pos.z && this->m_Rect.vMax.z >= pos.z)
	{
		return true;
	}
	return false;
}
Node::Node(float x, float y, float z, float w, float h, float t)
{
	m_Parent = nullptr;
	m_Depth = 0;
	this->m_Rect.vPivot = Vector3(x, y, z);
	this->m_Rect.vMin = Vector3(x, y, z - t);
	this->m_Rect.vMax = Vector3(x +w, y+h, z);
	this->m_Rect.vSize = Vector3(w, h, t);
}
Node::Node(Vector3 vPivot, Vector3 vSize)
{
	m_Parent = nullptr;
	m_Depth = 0;
	this->m_Rect.vPivot = vPivot;
	this->m_Rect.vMin = Vector3(vPivot.x, vPivot.y, vPivot.z-vSize.z);
	this->m_Rect.vMax = Vector3(vPivot.x+ vSize.x, vPivot.y + vSize.y, vPivot.z);
	this->m_Rect.vSize = vSize;
}
Node::~Node()
{
	for (int Child = 0; Child < 4; Child++)
	{
		if (m_Child[Child] != nullptr)
		{
			delete m_Child[Child];
			m_Child[Child] = nullptr;
			Node::g_Counter--;
		}
	}
}