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
	A::AMatrix		matWorld;
	A::AVector3		vPos;
	ABox			box;
	AObject3D*		pObject;

	//Camera
	A::AVector3		m_vRight;
	A::AVector3		m_vUp;
	A::AVector3		m_vLook;

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
	int			m_iCurrentLod = 0;
	int			m_dwLodType; // 0 ~ 16
	bool		m_bLeaf = false;
public:
	vector<ANode*>	 m_pChild;
	vector<ANode*>	 m_pNeighborList;	//��0��1��2��3
	vector<int>		 m_CornerList;	//�����ε���
	list<AMapObj*>	 m_pStaticObjList;
	list<AMapObj*>	 m_pDynamicObjList;


	//vector<DWORD> m_IndexList;
	//ComPtr<ID3D11Buffer> m_pIndexBuffer;
	using INDEXLIST = vector<DWORD>; //m_IndexList;
	using INDEXBUFFER = ComPtr<ID3D11Buffer>; //m_pIndexBuffer0;
	vector<INDEXLIST>	 m_IndexList;
	vector<INDEXBUFFER> m_pIndexBuffer;
public:
	void AddObject(AMapObj* pObj);
	void AddDynamicObject(AMapObj* pObj);
	void DelDynamicObject(AMapObj* pObj);
public:
	ANode();
	ANode(float x, float y, float w, float h);
	~ANode();
};

