#include "Object.h"

AObject::AObject()
{
	m_NodeIndex = -1;
	m_Mass = 1.0f;
	m_Pos = { 20.0f, 20, -20 };
	m_Velocity = { 0.0f, 0.0f, 0.0f };
	m_Acceleration = {0.0f, 0.0f, 0.0f};
	m_Forces = {0.0f, 0.0f, 0.0f};

	m_Rect.vSize = { 4.0f, 4.0f, 4.0f };
	AVector3 vHalf = m_Rect.vSize / 2.0f;
	m_Rect.vPivot = { m_Pos.x - vHalf.x, m_Pos.y - vHalf.y, m_Pos.z + vHalf.z };
	m_Rect.vMin = { m_Pos.x - vHalf.x, m_Pos.y - vHalf.y, m_Pos.z - vHalf.z };
	m_Rect.vMax = { m_Pos.x +- vHalf.x, m_Pos.y + vHalf.y, m_Pos.z + vHalf.z };
}
AObject::AObject(AVector3 Pos, AVector3 vSize)
{
	m_NodeIndex = -1;
	m_Mass = 1.0f;
	m_Pos = Pos;
	m_Velocity = { 0.0f, 0.0f, 0.0f };
	m_Acceleration = { 0.0f, 0.0f, 0.0f };
	m_Forces = { 0.0f, 0.0f, 0.0f };

	AVector3 vHalf = vSize / 2.0f;
	m_Rect.vPivot = { m_Pos.x - vHalf.x, m_Pos.y - vHalf.y, m_Pos.z + vHalf.z };
	m_Rect.vMin = { m_Pos.x - vHalf.x, m_Pos.y - vHalf.y, m_Pos.z - vHalf.z };
	m_Rect.vMax = { m_Pos.x + -vHalf.x, m_Pos.y + vHalf.y, m_Pos.z + vHalf.z };
	m_Rect.vSize = vSize;
}