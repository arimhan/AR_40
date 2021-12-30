#pragma once
#include "Std.h"

class ANode
{
public:
	static int		g_Counter;
	int				m_Index;
	ABox			m_Rect;
	vector<int>		m_ObjectList;
	ANode*			m_Child[8];
	int				m_Depth;
	ANode*			m_Parent;

	bool			AddObject(int index);
	bool			IsRect(AVector3 pos);

	ANode() {};
	ANode(float x, float y, float z, float w, float h, float t);
	ANode(AVector3 vPivot, AVector3 vSize);
	~ANode();
};

