#pragma once
#include "Std.h"

class Node
{
public:
	static int g_Counter;
	int m_Index;
	Box m_Rect;
	vector<int> m_ObjectList;
	Node* m_Child[8];
	int m_Depth;
	Node* m_Parent;

	bool AddObject(int index);
	bool IsRect(Vector3 pos);

	Node() {};
	Node(float x, float y, float z, float w, float h, float t);
	Node(Vector3 vPivot, Vector3 vSize);
	~Node();
};

