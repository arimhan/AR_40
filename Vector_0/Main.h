#pragma once
#include <iostream>
#include <windows.h>
#include "Vector.h"
#include <d3d11.h>
using namespace std;


struct ASimpleVertex
{
	AVector3 p;
	AVector4 c;
};
class AMain
{
public:
	ASimpleVertex	m_VertexList[9];	// 0¹ø~8¹ø ÃÑ 9°³
	DWORD			m_IndexList[24];
	UINT			m_iNumVertex;
	UINT			m_iNumIndex;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

	AMain() {};
	virtual ~AMain() {};
};

