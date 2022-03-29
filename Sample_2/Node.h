#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <vector>	//�迭 (���Ҵ� ����)
#include <list>
#include "Object3D.h"
using namespace std;

struct AMapObj
{
	//struct�� ��������� ANode�� ������� �̸��� ��ġ�°��� �Ϻ� ����.
	wstring			name;
	T::TMatrix		matWorld;
	T::TVector3		vPos;
	ABox			box;
	AObject3D*		pObject;

	//Camera
	T::TVector3		m_vRight;
	T::TVector3		m_vUp;
	T::TVector3		m_vLook;

public:
	void UpdateData();
	void UpdateCollision();
};

class ANode
{
public:
	int			m_iIndex;
	ANode*		m_pParent;
	ABox		m_Box;
	int			m_iDepth;
	bool		m_bLeaf = false;
public:
	vector<ANode*>	 m_pChild;
	vector<int>		 m_CornerList;	//�����ε���
	list<AMapObj*>	 m_pStaticObjList;
	list<AMapObj*>	 m_pDynamicObjList;
	vector<DWORD>	 m_IndexList;
	ComPtr<ID3D11Buffer> m_pIndexBuffer = nullptr;
public:
	void AddObject(AMapObj* pObj);
	void AddDynamicObject(AMapObj* pObj);
	void DelDynamicObject(AMapObj* pObj);
public:
	ANode();
	ANode(float x, float y, float w, float h);
	~ANode();
};

